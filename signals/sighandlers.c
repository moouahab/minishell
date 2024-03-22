/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:06:01 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 09:06:02 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signum = SIGINT;
	}
}

void	sigint_handler2(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_signum = SIGINT;
	}
}

void	sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		write(0, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_signum = SIGQUIT;
	}
}

void	sigquit_handler2(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "", 1);
		g_signum = SIGQUIT;
	}
}
