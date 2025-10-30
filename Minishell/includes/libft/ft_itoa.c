/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trambure <trambure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:01:12 by trambure          #+#    #+#             */
/*   Updated: 2025/04/07 23:51:45 by trambure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			i;
	intmax_t	nbr;
	char		*str;
	int			is_neg;

	nbr = n;
	is_neg = (nbr < 0);
	if (is_neg)
		nbr = -nbr;
	i = count_digits(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (nbr != 0)
	{
		str[i--] = '0' + (nbr % 10);
		nbr /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
