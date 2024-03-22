/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:30:06 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:30:08 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

size_t	count_pipes(t_cmd *cmds)
{
	t_cmd	*current;
	size_t	count;

	current = cmds;
	count = 0;
	while (current->next)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	free_pipes(int **pfd, size_t pipe_count)
{
	size_t	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pfd[i][0]);
		close(pfd[i][1]);
		free(pfd[i++]);
	}
	free(pfd);
}

int	**init_pipes(t_cmd *cmds)
{
	int		**pfd;
	size_t	pipe_count;
	size_t	i;

	pipe_count = count_pipes(cmds);
	if (pipe_count == 0)
		return (NULL);
	pfd = ft_calloc(sizeof(int *), pipe_count);
	if (!pfd)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pfd[i] = ft_calloc(sizeof(int), 2);
		if (!pfd[i])
		{
			free_pipes(pfd, pipe_count);
			return (NULL);
		}
		if (pipe(pfd[i++]) == -1)
			perror("pipe");
	}
	return (pfd);
}
