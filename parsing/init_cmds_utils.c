/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:44 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:30:46 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_word	*skip_rd_and_file(t_word *current)
{
	if (current && !current->next)
		return (current);
	if (current && current->token >= 1 && current->token <= 5
		&& current->next->token > 5)
		current = current->next->next;
	if (current && current->token == PIPE)
		return (current);
	if (current && current->next && current->token >= 1 && current->token <= 5
		&& current->next->token > 5)
		current = skip_rd_and_file(current);
	return (current);
}

t_word	*go_to_next_pipe(t_word *current)
{
	while (current && current->token != PIPE)
		current = current->next;
	if (current && current->token == PIPE)
		current = current->next;
	return (current);
}

size_t	get_ac(t_word *words)
{
	t_word	*current;
	size_t	len;

	current = words;
	len = 0;
	while (current && current->token != PIPE)
	{
		if (current->token >= 1 && current->token <= 5)
			current = skip_rd_and_file(current);
		if (current && current->token != PIPE && current->token > 5)
		{
			len++;
		}
		if (current && current->token != PIPE)
			current = current->next;
	}
	return (len);
}

char	**get_av(t_word *words)
{
	t_word	*current;
	char	**av;
	size_t	len;
	size_t	i;

	len = get_ac(words);
	if (len == 0)
		return (NULL);
	av = ft_calloc(sizeof(char *), len + 1);
	if (!av)
		return (NULL);
	current = words;
	i = 0;
	while (current && current->token != PIPE)
	{
		if (current->token >= 1 && current->token <= 5)
			current = skip_rd_and_file(current);
		if (current && current->token > 5)
			av[i++] = ft_strdup(current->word);
		if (current && current->token != PIPE)
			current = current->next;
	}
	av[i] = NULL;
	return (av);
}
