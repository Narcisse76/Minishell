/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:25:33 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_expand_ctx
{
	char	*str;
	char	*result;
	int		*i;
	int		*j;
}	t_expand_ctx;

static void	copy_var_value(char *result, int *j, char *var_value)
{
	int	k;

	k = 0;
	while (var_value[k])
		result[(*j)++] = var_value[k++];
}

static int	process_variable(t_expand_ctx *ctx, t_data *data)
{
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_name = extract_var_name(&ctx->str[*ctx->i + 1], &var_len);
	if (var_name)
	{
		var_value = get_var_value(var_name, data);
		copy_var_value(ctx->result, ctx->j, var_value);
		free(var_value);
		free(var_name);
		*ctx->i += var_len + 1;
		return (1);
	}
	ctx->result[(*ctx->j)++] = ctx->str[(*ctx->i)++];
	return (0);
}

char	*expand_variables(char *str, t_data *data)
{
	char			*result;
	int				i;
	int				j;
	t_expand_ctx	ctx;

	if (!str)
		return (NULL);
	result = malloc(calculate_expanded_size(str, data) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	ctx = (t_expand_ctx){str, result, &i, &j};
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			process_variable(&ctx, data);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
