/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:53:29 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 11:53:31 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_env	*env_cpy(t_env *env)
{
	t_env	*current;
	t_env	*new;

	current = env;
	if (!env)
		return (NULL);
	new = NULL;
	while (current)
	{
		add_env(&new, ft_strdup(current->key), ft_strdup(current->value));
		current = current->next;
	}
	return (new);
}

void	sort_env(t_env **env)
{
	t_env	*current;
	t_env	*env_tmp;
	char	*tmp;

	env_tmp = *env;
	while (env_tmp)
	{
		current = *env;
		while (current)
		{
			if (current->next && current->key[0] > current->next->key[0])
			{
				tmp = current->next->key;
				current->next->key = current->key;
				current->key = tmp;
				tmp = current->next->value;
				current->next->value = current->value;
				current->value = tmp;
			}
			current = current->next;
		}
		env_tmp = env_tmp->next;
	}
}
