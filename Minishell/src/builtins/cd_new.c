/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:30:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:22:04 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_env_var(t_data *data, char *var_name, char *value)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == 0
			&& data->env[i][len] == '=')
		{
			free(data->env[i]);
			tmp = ft_strjoin(var_name, value);
			data->env[i] = tmp;
			break ;
		}
		i++;
	}
}

static void	update_pwd(t_data *data, char *old_pwd)
{
	char	*new_pwd;
	char	*old_tmp;
	char	*new_tmp;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	old_tmp = ft_strjoin("=", old_pwd);
	new_tmp = ft_strjoin("=", new_pwd);
	update_env_var(data, "OLDPWD", old_tmp);
	update_env_var(data, "PWD", new_tmp);
	free(old_tmp);
	free(new_tmp);
	free(new_pwd);
}

static char	*get_cd_path(char **args, t_data *data, char **old_pwd)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value(data->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (free(*old_pwd), NULL);
		}
		return (path);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(data->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			free(*old_pwd);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
		return (path);
	}
	return (args[1]);
}

static int	do_chdir(char *path, char *old_pwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(old_pwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, t_data *data)
{
	char	*path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	path = get_cd_path(args, data, &old_pwd);
	if (!path)
		return (1);
	if (do_chdir(path, old_pwd))
		return (1);
	update_pwd(data, old_pwd);
	free(old_pwd);
	return (0);
}
