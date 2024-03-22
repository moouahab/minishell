/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:34:50 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/16 10:43:54 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;

	if (len == 0 && ft_strlen(little) != 0)
		return (NULL);
	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && (size_t)(i + j) < len)
			j++;
		if (little[j] == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
