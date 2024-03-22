/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:27:22 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/10 09:35:17 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*src_tmp;
	char		*dest_tmp;

	if (!dest && !src)
		return (NULL);
	src_tmp = src;
	dest_tmp = dest;
	if (dest_tmp > src_tmp)
	{
		while (n > 0)
		{
			dest_tmp[n - 1] = src_tmp[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest_tmp, src_tmp, n);
	return (dest_tmp);
}
