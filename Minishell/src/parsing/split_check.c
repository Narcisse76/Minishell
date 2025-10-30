/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:12:30 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_char(char c, int quote_state)
{
	if (quote_state != 0)
		return (1);
	if (is_whitespace(c) == 0 && c != '|' && c != '>' && c != '<')
		return (1);
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	is_redir_out(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}

int	is_redir_in(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}
