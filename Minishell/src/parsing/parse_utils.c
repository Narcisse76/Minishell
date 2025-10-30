/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:07:04 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:23:52 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		if (tmp->fd > 2)
			close(tmp->fd);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_redir(tmp->redirs);
		free(tmp);
	}
}

void	free_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	if (tokens->type)
		free(tokens->type);
	free(tokens);
}

void	cleanup_all(t_data *data)
{
	if (data->cmd)
		free_cmd(data->cmd);
	if (data->env)
		free_env(data->env);
}
