/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:56:33 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_quotes(char c, int *i, t_quote_state *qs)
{
	if (c == '\'' && !qs->in_dquote)
	{
		qs->in_squote = !qs->in_squote;
		(*i)++;
		return (1);
	}
	else if (c == '"' && !qs->in_squote)
	{
		qs->in_dquote = !qs->in_dquote;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	expand_var_in_quotes(t_expand_qctx *ctx, t_data *data)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		k;

	var_name = extract_var_name(&ctx->str[*ctx->i + 1], &var_len);
	if (var_name)
	{
		var_value = get_var_value(var_name, data);
		k = 0;
		while (var_value[k])
			ctx->result[(*ctx->j)++] = var_value[k++];
		free(var_value);
		free(var_name);
		*ctx->i += var_len + 1;
		return (1);
	}
	ctx->result[(*ctx->j)++] = ctx->str[(*ctx->i)++];
	return (0);
}

char	*expand_with_quotes(char *str, t_data *data)
{
	char			*result;
	int				i;
	int				j;
	t_quote_state	qs;
	t_expand_qctx	ctx;

	if (!str)
		return (NULL);
	result = malloc(calculate_expanded_size(str, data) + ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	qs = (t_quote_state){0, 0};
	i = 0;
	j = 0;
	ctx = (t_expand_qctx){str, result, &i, &j, &qs};
	while (str[i])
	{
		if (handle_quotes(str[i], &i, &qs))
			continue ;
		if (str[i] == '$' && str[i + 1] && !qs.in_squote)
			expand_var_in_quotes(&ctx, data);
		else
			result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}
