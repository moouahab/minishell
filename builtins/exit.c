/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:08:14 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 11:08:16 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <limits.h>

int	is_invalid_arg(char *arg)
{
	size_t	i;

	i = 0;
	if ((!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+'))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		return (1);
	}
	i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_exit(t_shell *shell)
{
	free_words(shell->words);
	free_cmds(shell->cmds);
	free_env(&shell->env);
	free_env(&shell->env_cpy);
	free_tab2(shell->envp);
	close(shell->stdin_b);
	close(shell->stdout_b);
	if (shell->ids)
		free(shell->ids);
	free(shell);
}

int	bn_exit(char **av, t_shell *shell, bool is_forked)
{
	int	status;

	status = 0;
	if (av[1] && is_invalid_arg(av[1]))
		status = 2;
	else if (av[1] && av[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		if (shell->ret_value != 0)
			status = shell->ret_value;
		else
			status = 1;
		return (status);
	}
	else if (av[1])
		status = ft_atol(av[1]);
	if (is_forked == FALSE)
		free_pipes(shell->pfd, shell->pipe_count);
	free_exit(shell);
	exit(status);
}
