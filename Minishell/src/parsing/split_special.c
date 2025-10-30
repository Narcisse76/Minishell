/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:12:30 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (str[*i] == '<' && str[*i + 1] == '<')
		{
			*i += 1;
			return (1);
		}
	}
	return (0);
}

int	is_happend(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (str[*i] == '>' && str[*i + 1] == '>')
		{
			*i += 1;
			return (1);
		}
	}
	return (0);
}

int	is_eof(char c)
{
	if (c == '\n')
		return (1);
	else
		return (0);
}

int	is_special(char *str, int *i)
{
	if (is_pipe(str[*i]) == 1)
		return (3);
	if (is_heredoc(str, i) == 1)
		return (4);
	if (is_happend(str, i) == 1)
		return (5);
	if (is_redir_out(str[*i]) == 1)
		return (1);
	if (is_redir_in(str[*i]) == 1)
		return (2);
	if (is_eof(str[*i]) == 1)
		return (6);
	else
		return (0);
}

int	is_special_test(char *str, int i)
{
	if (str[i] && str[i + 1])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (4);
		if (str[i] == '>' && str[i + 1] == '>')
			return (5);
	}
	if (str[i] == '|')
		return (3);
	if (str[i] == '>')
		return (1);
	if (str[i] == '<')
		return (2);
	if (str[i] == '\n')
		return (6);
	return (0);
}
