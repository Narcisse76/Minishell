/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:49:10 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_pipe_syntax(t_token *tokens)
{
	int	i;

	if (tokens->type[0] == T_PIPE)
	{
		syntax_error("|");
		return (0);
	}
	i = 0;
	while (i < tokens->size)
	{
		if (tokens->type[i] == T_PIPE && i == tokens->size - 1)
		{
			syntax_error("newline");
			return (0);
		}
		if (tokens->type[i] == T_PIPE && i + 1 < tokens->size
			&& tokens->type[i + 1] == T_PIPE)
		{
			syntax_error("|");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_redirection_syntax(t_token *tokens)
{
	int	i;

	i = 0;
	while (i < tokens->size)
	{
		if (is_redirection(tokens->type[i]))
		{
			if (i + 1 >= tokens->size || is_operator(tokens->type[i + 1]))
			{
				if (i + 1 < tokens->size)
					syntax_error(tokens->words[i + 1]);
				else
					syntax_error("newline");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	if (!tokens || tokens->size == 0)
		return (1);
	if (!check_pipe_syntax(tokens))
		return (0);
	return (check_redirection_syntax(tokens));
}

int	check_quotes(char *line)
{
	int		i;
	int		in_squote;
	int		in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	if (in_squote || in_dquote)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quotes", 2);
		return (0);
	}
	return (1);
}
