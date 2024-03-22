/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <moouahab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:31:13 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 17:06:55 by moouahab         ###   ########.fr       */
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
	if (len == 0)
		return (NULL);
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
	if (len == 0)
		return (NULL);
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
	if (len == 0)
		return (NULL);
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
		return (add_word(words, word, get_operator_token(word)));
	}
	else
		word = get_word(input, i);
	if (!word)
		return (EXIT_FAILURE);
	if (*i > ft_strlen(input))
	{
		free(word);
		return (EXIT_FAILURE);
	}
	while (input[*i])
	{
		if (is_quote(input[*i]))
			word = ft_strjoin(word, get_quoted_word(input, i, input[*i]));
		else if (!is_operator(input[*i]) && input[*i] != ' ')
			word = ft_strjoin(word, get_word(input, i));
		else
			break ;
	}
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
			get_next_word(input, &i, &words);
			if (i > ft_strlen(input) || !input[i])
				break ;
		}
	}
	return (words);
}
