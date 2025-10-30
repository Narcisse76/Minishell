/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trambure <trambure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:04:56 by trambure          #+#    #+#             */
/*   Updated: 2025/04/08 00:14:18 by trambure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static void	free_split(char **lst, int i)
{
	while (--i >= 0)
		free(lst[i]);
	free(lst);
}

static char	*extract_word(const char *s, char c, size_t *len)
{
	if (!ft_strchr(s, c))
		*len = ft_strlen(s);
	else
		*len = ft_strchr(s, c) - s;
	return (ft_substr(s, 0, *len));
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	if (!s)
		return (NULL);
	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			lst[i] = extract_word(s, c, &word_len);
			if (!lst[i])
				return (free_split(lst, i), NULL);
			i++;
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}
