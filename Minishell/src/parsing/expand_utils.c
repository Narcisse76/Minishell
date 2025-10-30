/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:40:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*extract_var_name(char *str, int *len)
{
	char	*var_name;
	int		i;

	if (str[0] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	i = get_var_name_len(str);
	*len = i;
	if (i == 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < *len)
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value(char *var_name, t_data *data)
{
	char	*value;
	char	*exit_code_str;

	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_code_str = ft_itoa(data->exit_code);
		return (exit_code_str);
	}
	value = get_env_value(data->env, var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	should_expand(char *original_str, int pos)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (i < pos && original_str[i])
	{
		if (original_str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (original_str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	if (in_squote)
		return (0);
	return (1);
}
