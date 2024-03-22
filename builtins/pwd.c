/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:53:18 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:53:19 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	bn_pwd(char **av, t_env *env)
{
	char	pwd[1024];

	(void)av;
	if (ft_getenv("PWD", env))
		printf("%s\n", ft_getenv("PWD", env));
	else
	{
		getcwd(pwd, sizeof(pwd));
		printf("%s\n", pwd);
	}
	return (0);
}
