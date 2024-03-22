/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:40:00 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:40:01 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	add_env(t_env **env, char *key, char *value)
{
	t_env	*head;
	t_env	*new;

	if (!key || (!value && !key))
		return (EXIT_FAILURE);
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (EXIT_FAILURE);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return (EXIT_SUCCESS);
	}
	head = *env;
	while ((*env)->next)
		*env = (*env)->next;
	(*env)->next = new;
	(*env) = head;
	return (EXIT_SUCCESS);
}

void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	node->next = NULL;
	free(node);
	node = NULL;
}

int	delone_env(t_env **env, char *key)
{
	t_env	*head;
	t_env	*tmp;

	if (!key || !*env)
		return (EXIT_FAILURE);
	head = *env;
	tmp = *env;
	while (*env)
	{
		if ((*env)->next && !ft_strcmp((*env)->next->key, key))
			tmp = (*env);
		if (!ft_strcmp((*env)->key, key))
		{
			if (*env == head)
				head = (*env)->next;
			else
				tmp->next = (*env)->next;
			free_node(*env);
			break ;
		}
		else
			*env = (*env)->next;
	}
	*env = head;
	return (EXIT_SUCCESS);
}

int	update_value(t_env **env, char *key, char *value)
{
	t_env	*head;

	if (!key || !value || !*env)
		return (EXIT_FAILURE);
	head = *env;
	while ((*env))
	{
		if (!ft_strcmp((*env)->key, key))
		{
			free((*env)->value);
			(*env)->value = value;
			break ;
		}
		*env = (*env)->next;
	}
	*env = head;
	return (EXIT_SUCCESS);
}

int	free_env(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return (EXIT_FAILURE);
	while (*env)
	{
		tmp = (*env)->next;
		free_node(*env);
		*env = tmp;
	}
	return (EXIT_SUCCESS);
}
