/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:20:08 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/19 10:20:09 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	can_rd_out(char *filename)
{
	if (ft_strchr(filename, '/') || is_directory(filename))
	{
		if (access(filename, F_OK) == 0 && !is_directory(filename))
			return (TRUE);
		else if (access(filename, F_OK) == -1 && !is_directory(filename))
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

void	ambiguous_redirect(t_cmd *cmd, t_shell **shell)
{
	close_heredoc(cmd);
	write(2, "minishell: ambiguous redirect\n", 30);
	(*shell)->ret_value = 1;
}

t_cmd	*get_redirections(t_cmd *cmd, t_word *words, t_shell **shell)
{
	t_word	*current;

	current = words;
	cmd->fdout = 1;
	cmd->fdin = 0;
	while (current && current->token != PIPE)
	{
		cmd = get_out_rds(cmd, current, shell);
		if (!cmd)
			return (NULL);
		if (current && current->token == RD_IN && (!current->next
				|| current->next->token <= 5))
		{
			ambiguous_redirect(cmd, shell);
			return (NULL);
		}
		if (current && current->token == RD_IN)
		{
			if (check_in(&cmd, current, shell) == 1)
				return (NULL);
		}
		if (current && current->token != PIPE)
			current = current->next;
	}
	return (cmd);
}

void	redirect(t_cmd *cmd, t_shell *shell, bool is_forked)
{
	int	fdin;

	(void)is_forked;
	(void)shell;
	if (cmd->filein)
	{
		fdin = open(cmd->filein, O_RDONLY);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (cmd->typein == RD_AP_IN)
		unlink(cmd->filein);
	if (cmd->filein)
	{
		free(cmd->filein);
		cmd->filein = NULL;
	}
	if (cmd->fdout != 1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
}
