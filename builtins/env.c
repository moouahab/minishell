/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:47:37 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:47:39 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	bn_env(char **argv, t_env *env)
{
	t_env	*current;

	(void)argv;
	if (ft_strlen2(argv) > 1)
	{
		write(2, "env: too many arguments or options.\n", 36);
		return (1);
	}
	current = env;
	while (current)
	{
		printf("%s=", current->key);
		if (current->value)
			printf("%s\n", current->value);
		current = current->next;
	}
	return (0);
}
