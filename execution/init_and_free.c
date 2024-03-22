/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:30:30 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:30:31 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	exitchild_and_free(t_shell *shell, int e_status)
{
	free_env(&shell->env);
	free_env(&shell->env_cpy);
	free(shell->ids);
	free_cmds(shell->cmds);
	free_tab2(shell->envp);
	free(shell);
	exit(e_status);
}

t_shell	*init_exec(t_shell *shell, t_cmd *cmds)
{
	shell->envp = get_env_tab(shell->env);
	shell->pipe_count = count_pipes(cmds);
	shell->pfd = init_pipes(cmds);
	shell->ids = ft_calloc(sizeof(pid_t), shell->pipe_count + 1);
	signal(SIGINT, sigint_handler2);
	if (shell->pipe_count == 0)
		signal(SIGQUIT, sigquit_handler);
	else
		signal(SIGQUIT, sigquit_handler2);
	return (shell);
}

void	free_exec(t_shell *shell, t_cmd *cmds)
{
	free_words(shell->words);
	free_pipes(shell->pfd, shell->pipe_count);
	wait_for_children(shell, shell->ids);
	free_tab2(shell->envp);
	free_cmds(cmds);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
