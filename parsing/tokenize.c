/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:31:13 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:31:14 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_quoted_word(char *input, size_t *i, char quote)
{
	char	*word;
	size_t	j;
	size_t	len;

	(*i)++;
	len = ft_strlen_c(input + *i, quote);
	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && j < len)
		word[j++] = input[(*i)++];
	word[j] = '\0';
	(*i)++;
	return (word);
}

char	*get_word(char *input, size_t *i)
{
	char	*word;
	size_t	len;
	size_t	j;

	len = ft_strlen_sep(input + *i, "|<>\'\" ");
	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && j < len)
		word[j++] = input[(*i)++];
	word[j] = '\0';
	return (word);
}

char	*get_operator_word(char *input, size_t *i)
{
	size_t	len;
	size_t	j;
	char	*word;

	len = 0;
	while (input[*i + len] && input[*i + len] == input[*i])
		len++;
	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && j < len)
		word[j++] = input[(*i)++];
	word[j] = '\0';
	return (word);
}

int	get_next_word(char *input, size_t *i, t_word **words)
{
	char	*word;

	if (is_quote(input[*i]))
		word = get_quoted_word(input, i, input[*i]);
	else if (is_operator(input[*i]))
	{
		word = get_operator_word(input, i);
		if (!word)
			return (EXIT_FAILURE);
		return (add_word(words, word, get_operator_token(word)));
	}
	else
		word = get_word(input, i);
	while (input[*i])
	{
		if (is_quote(input[*i]))
			word = ft_strjoin(word, get_quoted_word(input, i, input[*i]));
		else if (!is_operator(input[*i]) && input[*i] != ' ')
			word = ft_strjoin(word, get_word(input, i));
		else
			break ;
	}
	if (!word)
		return (EXIT_FAILURE);
	return (add_word(words, word, WORD));
}

t_word	*tokenize(char *input)
{
	t_word	*words;
	size_t	i;

	i = 0;
	words = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else
		{
			if (get_next_word(input, &i, &words) == EXIT_FAILURE)
				return (NULL);
			if (!input[i])
				break ;
		}
	}
	return (words);
}
