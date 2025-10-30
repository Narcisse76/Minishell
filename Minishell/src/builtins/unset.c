/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:30:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:18:56 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	find_var_index(char **env, char *key)
{
	int		i;
	int		key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	remove_env_var(t_data *data, char *key)
{
	int		index;
	char	**new_env;
	int		i;
	int		j;

	index = find_var_index(data->env, key);
	if (index == -1)
		return (0);
	new_env = malloc(sizeof(char *) * count_env_vars(data->env));
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while (data->env[i++])
	{
		if (i != index)
			new_env[j++] = data->env[i];
		else
			free(data->env[i]);
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
	return (0);
}

static int	is_valid_var_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **args, t_data *data)
{
	int	i;
	int	ret;

	if (!args[1])
		return (0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
		{
			if (remove_env_var(data, args[i]) != 0)
				return (1);
		}
		i++;
	}
	return (ret);
}
