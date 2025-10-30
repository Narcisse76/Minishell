/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:51:53 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:53:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*gb_malloc(t_gb_collector **list, size_t size_of, int number)
{
	void			*ret;
	t_gb_collector	*new_node;

	ret = malloc(size_of * number);
	if (!ret)
		return (NULL);
	new_node = malloc(sizeof(t_gb_collector));
	if (!new_node)
		return (NULL);
	new_node->data = ret;
	new_node->next = *list;
	*list = new_node;
	return (ret);
}

void	free_gb(t_gb_collector *list)
{
	t_gb_collector	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->data);
		free(list);
		list = tmp;
	}
}

void	free_env_list(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->content);
		free(env);
		env = tmp;
	}
}
