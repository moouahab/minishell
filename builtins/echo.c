/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <moouahab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:47:12 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/19 20:57:14 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <stdio.h>

int	check_n_option(char *arg)
{
	if (!ft_strncmp(arg, "-n", 2))
		return (1);
	return (0);
}

void	check_options(char **argv, size_t *i)
{
	while (argv[*i])
	{
		if (check_n_option(argv[*i]) == 0)
			break ;
		(*i)++;
	}
}

int	bn_echo(char **argv)
{
	size_t	i;
	int		no_nl;

	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	no_nl = check_n_option(argv[1]);
	i = 1;
	check_options(argv, &i);
	if (ft_strlen2(argv) > 1)
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
	}
	if (!no_nl)
		printf("\n");
	return (0);
}
