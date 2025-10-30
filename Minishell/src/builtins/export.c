/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narcisse <narcisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:30:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/30 10:10:32 by narcisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_env_index(char **env, char *key)
{
	int		i;
	int		key_len;
	char	*equals;

	equals = ft_strchr(key, '=');
	if (equals)
		key_len = equals - key;
	else
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

int	add_or_update_env(t_data *data, char *var)
{
	int		index;
	char	**new_env;
	int		i;

	index = find_env_index(data->env, var);
	if (index != -1)
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(var);
		return (0);
	}
	new_env = malloc(sizeof(char *) * (count_env(data->env) + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			ft_putchar_fd(env[i][j], 1);
			j++;
		}
		if (env[i][j] == '=')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(&env[i][j + 1], 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	builtin_export(char **args, t_data *data)
{
	int		i;
	int		ret;

	if (!args[1])
	{
		print_export(data->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			if (add_or_update_env(data, args[i]) != 0)
				return (1);
		i++;
	}
	return (ret);
}
