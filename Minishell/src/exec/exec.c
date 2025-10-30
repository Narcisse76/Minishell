/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:52:27 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_command(t_data *data)
{
	if (!data->cmd)
		return (0);
	if (!data->cmd->args || !data->cmd->args[0])
	{
		ft_putendl_fd("minishell: syntax error: command expected", 2);
		data->exit_code = 2;
		return (0);
	}
	return (1);
}

static void	exec_single_builtin(t_data *data)
{
	data->exit_code = exec_builtin(data->cmd, data);
}

static void	exec_single_external(t_data *data)
{
	pid_t	pid;

	setup_signals_execution();
	pid = fork();
	if (pid == 0)
	{
		setup_signals_default();
		exec_cmd(data->cmd, data);
	}
	else if (pid > 0)
	{
		waitpid(pid, &data->exit_code, 0);
		if (WIFSIGNALED(data->exit_code))
			data->exit_code = 128 + WTERMSIG(data->exit_code);
		else
			data->exit_code = WEXITSTATUS(data->exit_code);
		setup_signals_interactive();
	}
	else
		perror("fork");
}

static void	exec_single_cmd(t_data *data)
{
	if (is_builtin(data->cmd->args[0]))
		exec_single_builtin(data);
	else
		exec_single_external(data);
}

void	exec(t_data *data)
{
	if (!validate_command(data))
		return ;
	if (!data->cmd->next)
		exec_single_cmd(data);
	else
	{
		setup_signals_execution();
		exec_pipeline(data);
		setup_signals_interactive();
	}
}
