/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:40:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static char	*create_heredoc_file(char *file, t_redir *redir)
{
	char	*cleaned_file;

	redir->expand_heredoc = !has_quotes(file);
	cleaned_file = remove_quotes(file);
	return (cleaned_file);
}

t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;
	char	*cleaned_file;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (type == T_HEREDOC)
	{
		cleaned_file = create_heredoc_file(file, redir);
		if (!cleaned_file)
			return (free(redir), NULL);
		redir->file = cleaned_file;
	}
	else
	{
		redir->file = ft_strdup(file);
		if (!redir->file)
			return (free(redir), NULL);
		redir->expand_heredoc = 0;
	}
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*current;

	if (cmd->redirs == NULL)
	{
		cmd->redirs = new_redir;
		return ;
	}
	current = cmd->redirs;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redir;
}
