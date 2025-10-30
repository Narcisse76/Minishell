/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:12:30 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_builtin_in_pipeline(t_cmd *cmd, t_data *data)
{
	data->exit_code = exec_builtin(cmd, data);
	exit(data->exit_code);
}

static void	exec_external_cmd(t_cmd *cmd, t_data *data, char *cmd_path)
{
	if (execve(cmd_path, cmd->args, data->env) == -1)
	{
		perror("execve");
		exit(127);
	}
}

void	exec_cmd(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	setup_redirections(cmd, data);
	if (is_builtin(cmd->args[0]))
		exec_builtin_in_pipeline(cmd, data);
	cmd_path = find_command_path(cmd->args[0], data->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exec_external_cmd(cmd, data, cmd_path);
}
