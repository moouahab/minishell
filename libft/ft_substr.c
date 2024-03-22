/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:11:06 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/16 10:44:13 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_sub_s_len(char const *s, unsigned int start, size_t len)
{
	size_t	sub_s_len;

	if (start > ft_strlen(s))
		sub_s_len = 0;
	else if (len > ft_strlen(s + start))
		sub_s_len = ft_strlen(s + start);
	else
		sub_s_len = len;
	return (sub_s_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;
	size_t	sub_s_len;

	if (!s)
		return (NULL);
	i = 0;
	sub_s_len = get_sub_s_len(s, start, len);
	sub_s = malloc(sizeof(char) * sub_s_len + 1);
	if (!sub_s)
		return (NULL);
	while (i < sub_s_len && s[start])
	{
		sub_s[i] = s[start];
		i++;
		start++;
	}
	sub_s[i] = 0;
	return (sub_s);
}
