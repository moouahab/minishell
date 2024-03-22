/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:04:34 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 12:04:36 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long long int	ft_atol(const char *str)
{
	long long int	res;
	long long int	sign;

	res = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((sign == 1 && (res * 10 + (*str - '0')) < 0) || (sign == -1 && (res
					* 10 + (*str - '0')) * sign >= 0))
		{
			write(2, "minishell: exit: numeric arguments required\n", 44);
			exit(2);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
