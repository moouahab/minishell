/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:45:20 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 11:45:21 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	check_ap_out(t_cmd **cmd, t_word *current, t_shell **shell)
{
	if ((*cmd)->fdout != 1)
		close((*cmd)->fdout);
	if (can_rd_out(current->next->word))
	{
		(*cmd)->fdout = open(current->next->word, O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if ((*cmd)->fdout == -1)
		{
			(*shell)->ret_value = 1;
			write(2, "minishell: ", 11);
			perror(current->next->word);
			close_heredoc(*cmd);
			return (1);
		}
	}
	else
	{
		(*shell)->ret_value = 1;
		close_heredoc(*cmd);
		check_filetype(current->next->word);
		return (1);
	}
	(*cmd)->typeout = RD_AP_OUT;
	return (0);
}

int	check_out(t_cmd **cmd, t_word *current, t_shell **shell)
{
	if ((*cmd)->fdout != 1)
		close((*cmd)->fdout);
	if (can_rd_out(current->next->word))
	{
		(*cmd)->fdout = open(current->next->word, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		if ((*cmd)->fdout == -1)
		{
			(*shell)->ret_value = 1;
			write(2, "minishell: ", 11);
			perror(current->next->word);
			close_heredoc(*cmd);
			return (1);
		}
	}
	else
	{
		(*shell)->ret_value = 1;
		close_heredoc(*cmd);
		check_filetype(current->next->word);
		return (1);
	}
	(*cmd)->typeout = RD_OUT;
	return (0);
}

t_cmd	*get_out_rds(t_cmd *cmd, t_word *current, t_shell **shell)
{
	if (current && (current->token == RD_AP_OUT || current->token == RD_OUT)
		&& (!current->next || current->next->token <= 5))
	{
		(*shell)->ret_value = 1;
		close_heredoc(cmd);
		write(2, "minishell: ambiguous redirect\n", 30);
		return (NULL);
	}
	if (current->token == RD_AP_OUT)
	{
		if (check_ap_out(&cmd, current, shell) == 1)
			return (NULL);
	}
	if (current->token == RD_OUT && current->next)
	{
		if (check_out(&cmd, current, shell) == 1)
			return (NULL);
	}
	return (cmd);
}

t_cmd	*close_fds(t_cmd *cmd)
{
	if (cmd->typein == RD_AP_IN)
		unlink(cmd->filein);
	if (cmd->filein)
		free(cmd->filein);
	if (cmd->fdout != 1)
		close(cmd->fdout);
	cmd->filein = NULL;
	return (cmd);
}

int	check_in(t_cmd **cmd, t_word *current, t_shell **shell)
{
	(*cmd)->fdin = open(current->next->word, O_RDONLY);
	if ((*cmd)->fdin == -1)
	{
		*cmd = close_fds(*cmd);
		perror(current->next->word);
		(*shell)->ret_value = 1;
		return (1);
	}
	if ((*cmd)->fdin != 0)
		close((*cmd)->fdin);
	return (0);
}
