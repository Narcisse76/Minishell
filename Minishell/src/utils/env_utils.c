/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:57:03 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increment_shlvl(t_data *data)
{
	char	*shlvl_value;
	int		shlvl;
	char	*new_shlvl;
	char	*new_var;

	shlvl_value = get_env_value(data->env, "SHLVL");
	if (shlvl_value)
		shlvl = ft_atoi(shlvl_value);
	else
		shlvl = 0;
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	new_var = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	if (!new_var)
		return ;
	add_or_update_env(data, new_var);
	free(new_var);
}
