/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:52:42 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_one_token(char *token, int is_heredoc_delim, t_data *data)
{
	if (is_heredoc_delim)
		return (ft_strdup(token));
	return (expand_with_quotes(token, data));
}

static char	**expand_tokens(char **res, t_data *data)
{
	char	**expanded;
	int		i;
	int		count;
	int		is_heredoc_delim;

	count = 0;
	while (res[count])
		count++;
	expanded = malloc(sizeof(char *) * (count + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	is_heredoc_delim = 0;
	while (res[i])
	{
		expanded[i] = expand_one_token(res[i], is_heredoc_delim, data);
		is_heredoc_delim = (ft_strcmp(res[i], "<<") == 0);
		i++;
	}
	expanded[i] = NULL;
	return (expanded);
}

static int	validate_syntax(t_token *tokens, t_data *data,
		char **res, char **expanded)
{
	if (!check_syntax(tokens))
	{
		data->exit_code = 2;
		free_split(res);
		free_split(expanded);
		free_tokens(tokens);
		return (0);
	}
	return (1);
}

t_cmd	*parsing(char *str, t_data *data)
{
	char	**res;
	char	**expanded;
	t_token	*tokens;
	t_cmd	*cmd;

	if (!check_quotes(str))
		return (data->exit_code = 2, NULL);
	res = split(str);
	expanded = expand_tokens(res, data);
	if (!expanded)
		return (free_split(res), NULL);
	tokens = tokenize(expanded);
	if (!validate_syntax(tokens, data, res, expanded))
		return (NULL);
	cmd = parse(tokens);
	free_split(res);
	free_split(expanded);
	free_tokens(tokens);
	return (cmd);
}
