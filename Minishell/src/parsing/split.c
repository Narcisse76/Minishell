/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 06:57:12 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 17:54:27 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words_helper(char *str, int *i,
	int *on_word, int *quote_state)
{
	int	count;

	count = 0;
	in_quotes(str[*i], quote_state);
	if (*on_word == 0 && is_char(str[*i], *quote_state) == 1)
	{
		*on_word = 1;
		count++;
	}
	else if (*quote_state == 0 && is_special(str, i) != 0)
	{
		if (*on_word == 1)
			*on_word = 0;
		count++;
	}
	else if (*quote_state == 0 && is_whitespace(str[*i]) == 1)
		*on_word = 0;
	return (count);
}

int	count_words(char *str)
{
	int	i;
	int	count;
	int	on_word;
	int	quote_state;

	i = 0;
	count = 0;
	on_word = 0;
	quote_state = 0;
	while (str[i])
	{
		count += count_words_helper(str, &i, &on_word, &quote_state);
		i++;
	}
	return (count);
}

static char	**allocate_split_array(char *str)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (count_words(str) + 1));
	return (ret);
}

static int	process_split_word(char *str, char **ret, int *i, int *j)
{
	int	len;

	while (is_whitespace(str[*i]) == 1 && str[*i])
		(*i)++;
	if (!str[*i])
		return (0);
	if (is_special_test(str, *i) != 0)
		ret[*j] = extract_special(&str[*i], &len);
	else
		ret[*j] = extract_word(&str[*i], &len);
	if (ret[*j] == NULL)
		return (-1);
	*i += len;
	(*j)++;
	return (1);
}

char	**split(char *str)
{
	char	**ret;
	int		i;
	int		j;
	int		result;

	ret = allocate_split_array(str);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		result = process_split_word(str, ret, &i, &j);
		if (result == -1)
		{
			free_split(ret);
			return (NULL);
		}
		if (result == 0)
			break ;
	}
	ret[j] = NULL;
	return (ret);
}
