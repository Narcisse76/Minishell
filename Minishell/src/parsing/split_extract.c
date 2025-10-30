/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:12:30 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_special_len(char *str)
{
	if (str[0] && str[1])
	{
		if ((str[0] == '<' && str[1] == '<')
			|| (str[0] == '>' && str[1] == '>'))
			return (2);
		else
			return (1);
	}
	else
		return (1);
}

char	*extract_special(char *str, int *len)
{
	char	*word;
	int		special_len;
	int		i;

	special_len = get_special_len(str);
	word = malloc(sizeof(char) * (special_len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < special_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	*len = special_len;
	return (word);
}

static int	get_word_len(char *str)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = 0;
	while (str[i])
	{
		in_quotes(str[i], &quote_state);
		if (quote_state == 0)
		{
			if (is_whitespace(str[i]) == 1)
				break ;
			if (is_special_test(str, i) != 0)
				break ;
		}
		i++;
	}
	return (i);
}

char	*extract_word(char *str, int *len)
{
	int		i;
	int		j;
	char	*word;

	i = get_word_len(str);
	*len = i;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
