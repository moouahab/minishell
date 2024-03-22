/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:29:43 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:29:45 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	do_execute(t_cmd *cmd, t_shell *shell, bool is_forked, int e_status)
{
	if (is_builtin(cmd->av[0]))
		e_status = exec_builtin(cmd->av, shell, is_forked);
	else
	{
		close(shell->stdin_b);
		close(shell->stdout_b);
		if (execve(cmd->path, cmd->av, shell->envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	if (is_forked == FALSE)
	{
		dup2(shell->stdin_b, STDIN_FILENO);
		dup2(shell->stdout_b, STDOUT_FILENO);
	}
	return (e_status);
}

void	close_heredoc(t_cmd *cmd)
{
	if (cmd->typein == RD_AP_IN && cmd->filein)
		unlink(cmd->filein);
}

void	exec_manager(t_cmd *cmd, t_shell *shell, t_word *words, bool is_forked)
{
	int	e_status;

	e_status = 0;
	pipe_manager(shell, cmd->i);
	cmd = get_redirections(cmd, words, &shell);
	e_status = shell->ret_value;
	if (is_forked == TRUE)
		free_and_close_backup(shell);
	if (!cmd && is_forked == FALSE)
		return ;
	else if (!cmd && is_forked == TRUE)
		exitchild_and_free(shell, e_status);
	redirect(cmd, shell, is_forked);
	if (!cmd->av && is_forked == TRUE)
		exitchild_and_free(shell, e_status);
	if (is_unknown_cmd(cmd, shell, is_forked))
		return ;
	e_status = do_execute(cmd, shell, is_forked, e_status);
	if (is_forked == TRUE && cmd->av && is_builtin(cmd->av[0]))
		exitchild_and_free(shell, e_status);
	else
		shell->ret_value = e_status;
}

t_shell	*fork_and_execute(t_shell *shell, t_word *current, t_cmd *cmd, size_t i)
{
	int	id;

	id = fork();
	if (id == 0)
		exec_manager(cmd, shell, current, TRUE);
	else
		shell->ids[i] = id;
	return (shell);
}

void	execute(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_word	*cur_word;
	size_t	i;

	current = cmds;
	if (!current)
		return ;
	shell = init_exec(shell, cmds);
	cur_word = shell->words;
	i = 0;
	while (current)
	{
		current->i = i;
		if (current->av && ft_strcmp("echo", current->av[0]) && ft_getenv("_",
				shell->env))
			update_value(&shell->env, "_", ft_strdup(current->av[0]));
		if (shell->pipe_count == 0 && current->av && is_builtin(current->av[0]))
			exec_manager(current, shell, cur_word, FALSE);
		else
			shell = fork_and_execute(shell, cur_word, current, i);
		cur_word = go_to_next_pipe(cur_word);
		current = current->next;
		i++;
	}
	free_exec(shell, cmds);
}
