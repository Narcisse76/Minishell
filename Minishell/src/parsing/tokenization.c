/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenziation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:07:05 by abignals          #+#    #+#             */
/*   Updated: 2025/10/17 14:41:03 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokenize(char **args)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = 0;
	while (args[i])
		i++;
	tokens->size = i;
	tokens->words = args;
	tokens->type = malloc(sizeof(int) * tokens->size);
	if (tokens->type == NULL)
	{
		free(tokens);
		return (NULL);
	}
	i = 0;
	while (i < tokens->size)
	{
		tokens->type[i] = is_special_test(args[i], 0);
		i++;
	}
	return (tokens);
}
