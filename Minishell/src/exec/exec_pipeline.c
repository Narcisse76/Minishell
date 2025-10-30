/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:43:46 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_pipe_fds(t_cmd *current, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static pid_t	fork_and_exec(t_cmd *current, t_data *data, int prev_fd,
		int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_signals_default();
		setup_pipe_fds(current, prev_fd, pipe_fd);
		exec_cmd(current, data);
	}
	return (pid);
}

static void	wait_all_children(int cmd_count, t_data *data)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		wait(&data->exit_code);
		i++;
	}
	data->exit_code = WEXITSTATUS(data->exit_code);
}

void	exec_pipeline(t_data *data)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*current;

	current = data->cmd;
	prev_fd = -1;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
			return (perror("pipe"));
		if (fork_and_exec(current, data, prev_fd, pipe_fd) < 0)
			return (perror("fork"));
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		current = current->next;
	}
	wait_all_children(count_cmds(data->cmd), data);
}
