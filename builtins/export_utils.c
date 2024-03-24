/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:33:24 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/24 11:33:25 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	print_env_var(t_env *current)
{
	printf("export %s", current->key);
	if (current->value)
		printf("=\"%s\"", current->value);
	printf("\n");
}

char	*add_to_prev_value(char *key, char *value, t_shell *shell)
{
	if (key[ft_strlen(key) - 1] == '+')
	{
		ft_strlcpy(key, key, ft_strlen(key));
		if (value)
			value = ft_strjoin(ft_strdup(ft_getenv(key, shell->env)), value);
		else
			value = ft_strdup(ft_getenv(key, shell->env));
	}
	return (value);
}
