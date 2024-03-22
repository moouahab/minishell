/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:16 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:30:17 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	get_quote_state(char c, bool *is_in_single, bool *is_in_double)
{
	if (c == '\'' && !(*is_in_double))
		(*is_in_single) = !(*is_in_single);
	if (c == '\"' && !(*is_in_single))
		(*is_in_double) = !(*is_in_double);
}

char	*del_char(char *s, size_t i)
{
	size_t	len;

	len = ft_strlen(s);
	while (i < len && s[i + 1])
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = '\0';
	return (s);
}

bool	is_limiter(char *input, size_t i, bool is_in_double)
{
	while (i != 0)
	{
		if (input[i] == '<' || input[i] == '|')
			break ;
		i--;
	}
	if (i == 0)
		return (FALSE);
	if (input[i] == '<' && input[i - 1] == '<' && !is_in_double)
		return (TRUE);
	return (FALSE);
}
