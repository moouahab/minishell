/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:53 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:38:53 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	is_valid_pipe(char *input, size_t i)
{
	if (input[0] == '|')
		return (FALSE);
	if (input[i] == '|' && input[i + 1] == '|')
		return (FALSE);
	if (!input[skip_spaces(input, i + 1, '+')])
		return (FALSE);
	if (!is_redirector(input[i - 1]) && skip_spaces(input, i - 1, '-') == 0)
		return (FALSE);
	if (input[skip_spaces(input, i + 1, '+')] == '|')
		return (FALSE);
	if (input[skip_spaces(input, i - 1, '-')] == '|')
		return (FALSE);
	if (is_redirector(input[i - 1]))
		return (FALSE);
	if (is_whitespace(input[i - 1]) && is_redirector(input[skip_spaces(input, i - 1,
					'-')]))
		return (FALSE);
	return (TRUE);
}

bool	is_valid_redirector(char *input, size_t i, char rd)
{
	if (input[i + 1] != rd && !input[skip_spaces(input, i + 1, '+')])
		return (FALSE);
	if (input[i + 1] == rd && !input[skip_spaces(input, i + 2, '+')])
		return (FALSE);
	if (input[i + 1] == rd && input[i + 2] && input[i + 2] == rd)
		return (FALSE);
	return (TRUE);
}

int		check_operators(char *input, size_t i)
{
	if (input[i] == '|' && !is_valid_pipe(input, i))
		return ('|');
	if (input[i] == '>' && input[i + 1] && input[i + 1] == '>' && !is_valid_redirector(input, i, '>'))
		return (2);
	if (input[i] == '<' && input[i + 1] && input[i + 1] == '<' && !is_valid_redirector(input, i, '<'))
		return (3);
	if (input[i] == '>' && !is_valid_redirector(input, i, '>'))
		return ('>');
	if (input[i] == '<' && !is_valid_redirector(input, i, '<'))
		return ('<');
	return ('\0');
}

int		check_invalid_tokens(char *input)
{
	char	*invalid_tokens;
	size_t	i;

	i = 0;
	invalid_tokens = "&;%\\*()[]{}";
	while (input[i])
	{
		if (check_operators(input, i) != '\0')
			return (check_operators(input, i));
		if (input[i] == '\n')
			return ('\n');
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (!is_quoted(input, &i, input[i]))
				return (input[i]);
			if (!input[i])
				break ;
		}
		if (ft_strchr(invalid_tokens, input[i]) && (!is_quoted(input, &i, '\"')
				|| !is_quoted(input, &i, '\'')))
			return (input[i]);
		i++;
	}
	return ('\0');
}
