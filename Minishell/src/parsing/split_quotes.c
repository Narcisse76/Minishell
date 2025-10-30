/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:50:03 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	in_quotes(char c, int *quote_state)
{
	if (c == '\'' && *quote_state == 0)
	{
		*quote_state = 1;
		return (1);
	}
	else if (c == '\'' && *quote_state == 1)
	{
		*quote_state = 0;
		return (1);
	}
	if (c == '"' && *quote_state == 0)
	{
		*quote_state = 2;
		return (1);
	}
	else if (c == '"' && *quote_state == 2)
	{
		*quote_state = 0;
		return (1);
	}
	return (*quote_state);
}

static void	process_quotes(char *str, char *result, int *i, int *j)
{
	int		in_quote;
	char	quote_char;

	in_quote = 0;
	quote_char = 0;
	while (str[*i])
	{
		if (!in_quote && (str[*i] == '"' || str[*i] == '\''))
		{
			in_quote = 1;
			quote_char = str[*i];
			(*i)++;
			continue ;
		}
		else if (in_quote && str[*i] == quote_char)
		{
			in_quote = 0;
			quote_char = 0;
			(*i)++;
			continue ;
		}
		result[(*j)++] = str[(*i)++];
	}
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	process_quotes(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}
