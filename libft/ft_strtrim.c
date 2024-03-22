/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:39:31 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/10 14:03:59 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_result_len(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;
	size_t	result_len;

	i = 0;
	k = ft_strlen(s1);
	result_len = 0;
	while (is_in_set(s1[i], set) == 1)
		i++;
	if (i == k)
		return (0);
	while (is_in_set(s1[k - 1], set) == 1)
		k--;
	while (result_len != k - i)
		result_len++;
	return (result_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		*res;

	if (!s1)
		return (NULL);
	res = malloc((get_result_len(s1, set) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	k = get_result_len(s1, set);
	while (is_in_set(s1[i], set) == 1)
		i++;
	while (j < k)
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}
