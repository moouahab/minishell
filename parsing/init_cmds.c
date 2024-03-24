/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:37 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:30:38 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	add_cmd(t_cmd **cmds, char **av, t_shell *shell, t_word *words)
{
	t_cmd	*current;
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return ;
	new->av = av;
	new->fdout = 1;
	new->i = 0;
	new->filein = NULL;
	new = heredoc_manager(new, words, shell, cmds);
	if (av)
		new->path = get_path(av[0], shell->env);
	else
		new->path = NULL;
	new->next = NULL;
	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	current = *cmds;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_cmd	*init_cmds(t_word *words, t_shell *shell)
{
	t_cmd	*cmds;
	t_word	*current;

	cmds = NULL;
	current = words;
	while (current)
	{
		add_cmd(&cmds, get_av(current), shell, current);
		if (g_signum == SIGINT)
		{
			free_cmds(cmds);
			free_words(words);
			return (NULL);
		}
		current = go_to_next_pipe(current);
	}
	return (cmds);
}
