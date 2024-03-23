/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:44:39 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:44:40 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_getenv(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

bool	is_in_env(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

size_t	ft_strlen2(char **strs)
{
	size_t	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	if (!s1 && !s2)
		return (-1);
	while (s1[i] || s2[i])
	{
		if ((!s1[i] && s2[i]) || (s1[i] && !s2[i]))
			return (1);
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

bool	is_whitespace(char c)
{
	if (c == 32 || c == 9 || c == 11)
		return (TRUE);
	return (FALSE);
}
