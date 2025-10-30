/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:12:30 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_exit_arg_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (255);
}

static void	cleanup_exit(t_data *data)
{
	int	i;

	if (data->cmd)
		free_cmd(data->cmd);
	if (data->env)
	{
		i = 0;
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
	}
	free(data);
}

int	builtin_exit(char **args, t_data *data)
{
	int		exit_code;
	long	tmp;

	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		if (!is_valid_number(args[1]))
			exit_code = handle_exit_arg_error(args[1]);
		else
		{
			if (args[2])
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				return (1);
			}
			tmp = ft_atoi(args[1]);
			exit_code = (unsigned char)tmp;
		}
	}
	else
		exit_code = data->exit_code;
	cleanup_exit(data);
	exit(exit_code);
}
