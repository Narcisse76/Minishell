/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:00:00 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:40:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	calc_var_size(char *str, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		size;

	var_name = extract_var_name(&str[*i + 1], &var_len);
	if (var_name)
	{
		var_value = get_var_value(var_name, data);
		size = ft_strlen(var_value);
		free(var_value);
		free(var_name);
		*i += var_len + 1;
		return (size);
	}
	(*i)++;
	return (1);
}

int	calculate_expanded_size(char *str, t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			size += calc_var_size(str, &i, data);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
