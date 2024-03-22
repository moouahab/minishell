/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:55:19 by rbenoit           #+#    #+#             */
/*   Updated: 2023/09/25 20:53:04 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_char_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_char_in_charset(str[i], charset) == 1)
			i++;
		if (is_char_in_charset(str[i], charset) == 0 && str[i])
		{
			count++;
			while (is_char_in_charset(str[i], charset) == 0 && str[i])
				i++;
		}
	}
	return (count);
}

char	*next_word(int *index, char *str, char *charset)
{
	int		i;
	int		word_len;
	char	*res;

	i = 0;
	word_len = 0;
	res = "";
	while (is_char_in_charset(str[*index], charset) == 1 && str[*index])
		(*index)++;
	while (is_char_in_charset(str[*index + word_len], charset) == 0
		&& str[*index + word_len])
	{
		word_len++;
	}
	res = malloc((word_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < word_len)
	{
		res[i] = str[*index];
		i++;
		(*index)++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		i;
	int		word_count;
	int		index;

	if (!str)
		return (NULL);
	word_count = count_words(str, charset);
	i = 0;
	index = 0;
	res = malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < word_count)
	{
		res[i] = next_word(&index, str, charset);
		i++;
	}
	res[i] = 0;
	return (res);
}
