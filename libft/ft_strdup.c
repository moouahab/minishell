/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:51:05 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/10 10:14:51 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		s_len;
	int		i;
	char	*s2;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	s2 = malloc((s_len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
