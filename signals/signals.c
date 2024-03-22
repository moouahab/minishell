/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:48:18 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 11:48:20 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_signals(char *input, t_shell *shell)
{
	if (g_signum == SIGINT)
	{
		shell->ret_value = 130;
		g_signum = 0;
	}
	if (g_signum == SIGQUIT)
	{
		shell->ret_value = 131;
		g_signum = 0;
	}
	if (!input)
		exit_and_free(input, shell, shell->ret_value);
}
