/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:42 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/10 14:25:21 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	intlen(unsigned int n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				i;
	int				is_neg;
	char			*res;
	unsigned int	nb;

	is_neg = is_negative(n);
	if (is_neg == 1)
		n = n * -1;
	nb = n;
	res = malloc(sizeof(char) * (intlen(nb) + 1 + is_neg));
	if (!res)
		return (NULL);
	i = intlen(nb) - 1 + is_neg;
	while (i >= 0)
	{
		res[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	if (is_neg == 1)
		res[0] = '-';
	res[intlen(n) + is_neg] = '\0';
	return (res);
}
