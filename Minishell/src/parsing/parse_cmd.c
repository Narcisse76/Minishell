/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narcisse <narcisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/30 10:11:58 by narcisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

static int	parse_redir_token(t_token *tokens, int *i, t_cmd *cmd)
{
	t_redir	*redir;

	if (*i + 1 >= tokens->size || tokens->type[*i + 1] != T_WORD)
		return (0);
	redir = create_redir(tokens->type[*i], tokens->words[*i + 1]);
	if (!redir)
		return (0);
	add_redir(cmd, redir);
	(*i) += 2;
	return (1);
}

t_cmd	*parse_command(t_token *tokens, int *i)
{
	t_cmd	*cmd;
	int		start;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	start = *i;
	while (*i < tokens->size && tokens->type[*i] != T_PIPE)
	{
		if (tokens->type[*i] >= T_REDIR_OUT
			&& tokens->type[*i] <= T_APPEND)
		{
			if (!parse_redir_token(tokens, i, cmd))
				return (free_cmd(cmd), NULL);
		}
		else
			(*i)++;
	}
	*i = start;
	cmd->args = extract_args(tokens, i);
	if (!cmd->args)
		return (free_cmd(cmd), NULL);
	return (cmd);
}

static void	add_cmd_to_list(t_cmd **head, t_cmd **current, t_cmd *new_cmd)
{
	if (!*head)
	{
		*head = new_cmd;
		*current = *head;
	}
	else
	{
		(*current)->next = new_cmd;
		*current = new_cmd;
	}
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	while (i < tokens->size)
	{
		new_cmd = parse_command(tokens, &i);
		if (!new_cmd)
			return (free_cmd(head), NULL);
		add_cmd_to_list(&head, &current, new_cmd);
		if (i < tokens->size && tokens->type[i] == T_PIPE)
			i++;
	}
	return (head);
}
