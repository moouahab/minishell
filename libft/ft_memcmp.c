/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:55:01 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/10 10:02:46 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;

	i = 0;
	s1_ptr = s1;
	s2_ptr = s2;
	while (i < n)
	{
		if (s1_ptr[i] != s2_ptr[i])
			return (s1_ptr[i] - s2_ptr[i]);
		i++;
	}
	return (0);
}
