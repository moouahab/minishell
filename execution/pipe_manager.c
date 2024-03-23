/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:35:29 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:35:30 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	pipe_manager(t_shell *shell, size_t i)
{
	if (!shell->pfd)
		return ;
	if (i > 0)
	{
		if (dup2(shell->pfd[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
		close(shell->pfd[i - 1][1]);
	}
	if (i < shell->pipe_count)
	{
		if (dup2(shell->pfd[i][1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(shell->pfd[i][0]);
	}
	free_pipes(shell->pfd, shell->pipe_count);
}

void	wait_for_children(t_shell *shell, pid_t *ids)
{
	int		e_status;
	size_t	i;

	i = 0;
	while (i < shell->pipe_count + 1)
	{
		if (waitpid(ids[i++], &e_status, 0) != -1)
		{
			if (g_signum == SIGINT)
			{
				shell->ret_value = 130;
				g_signum = 0;
			}
			else
				shell->ret_value = WEXITSTATUS(e_status);
		}
	}
	free(ids);
}
