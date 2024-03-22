/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:32:34 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 11:32:36 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	is_undir(t_cmd *cmd, bool is_forked, t_shell *shell)
{
	if (!is_builtin(cmd->av[0]) && !ft_strcmp(cmd->path, "undir"))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->av[0], ft_strlen(cmd->av[0]));
		write(2, ": No such file or directory\n", 28);
		if (is_forked == FALSE)
		{
			shell->ret_value = 127;
			return (1);
		}
		else
			exitchild_and_free(shell, 127);
	}
	return (0);
}

static int	is_dir(t_cmd *cmd, bool is_forked, t_shell *shell)
{
	if (!is_builtin(cmd->av[0]) && !ft_strcmp(cmd->path, "dir"))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->av[0], ft_strlen(cmd->av[0]));
		write(2, ": Is a directory\n", 17);
		if (is_forked == FALSE)
		{
			shell->ret_value = 126;
			return (1);
		}
		else
			exitchild_and_free(shell, 126);
	}
	return (0);
}

int	is_unknown_cmd(t_cmd *cmd, t_shell *shell, bool is_forked)
{
	if (!is_builtin(cmd->av[0]) && (!cmd->path || !ft_strcmp(cmd->path, "dir"))
		&& !ft_strchr(cmd->av[0], '/'))
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->av[0], ft_strlen(cmd->av[0]));
		write(2, "\n", 1);
		if (is_forked == FALSE)
		{
			shell->ret_value = 127;
			return (1);
		}
		else
			exitchild_and_free(shell, 127);
	}
	if (is_dir(cmd, is_forked, shell) == 1)
		return (1);
	if (is_undir(cmd, is_forked, shell) == 1)
		return (1);
	return (0);
}
