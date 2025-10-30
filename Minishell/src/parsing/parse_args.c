/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:40:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_token *tokens, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (i < tokens->size && tokens->type[i] != T_PIPE)
	{
		if (tokens->type[i] == T_WORD)
			count++;
		else if (tokens->type[i] >= T_REDIR_OUT
			&& tokens->type[i] <= T_APPEND)
			i++;
		i++;
	}
	return (count);
}

static int	add_arg_to_array(t_token *tokens, int *i, char **args, int *j)
{
	args[*j] = ft_strdup(tokens->words[*i]);
	if (!args[*j])
		return (0);
	(*j)++;
	return (1);
}

char	**extract_args(t_token *tokens, int *i)
{
	char	**args;
	int		j;
	int		count;

	count = count_args(tokens, *i);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	j = 0;
	while (*i < tokens->size && tokens->type[*i] != T_PIPE)
	{
		if (tokens->type[*i] == T_WORD)
		{
			if (!add_arg_to_array(tokens, i, args, &j))
				return (free_split(args), NULL);
		}
		else if (tokens->type[*i] >= T_REDIR_OUT
			&& tokens->type[*i] <= T_APPEND)
			(*i)++;
		(*i)++;
	}
	args[j] = NULL;
	return (args);
}
