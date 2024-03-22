/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:44:59 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:45:00 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

size_t	ft_strlen_c(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	ft_strlen_sep(const char *s, char *sep)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(sep, s[i]))
		i++;
	return (i);
}

bool	is_operator(char c)
{
	if (c == '|')
		return (TRUE);
	if (c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

bool	is_quote(char c)
{
	if (c == '\'')
		return (TRUE);
	if (c == '\"')
		return (TRUE);
	return (FALSE);
}

bool	is_redirector(char c)
{
	if (c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}
