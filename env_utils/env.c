/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:39:53 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:39:54 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_key(char *env_str)
{
	char	*key;
	size_t	i;

	i = 0;
	if (env_str[i] == '=')
		return (ft_strdup("="));
	while (env_str[i] && env_str[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		key[i] = env_str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *env_str)
{
	char	*value;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	i++;
	if ((int)(ft_strlen(env_str) - i) <= 0)
		return (NULL);
	value = ft_calloc(sizeof(char), ft_strlen(env_str) - i + 1);
	if (!value)
		return (NULL);
	while (env_str[i])
		value[j++] = env_str[i++];
	value[j] = '\0';
	return (value);
}

t_env	*init_env(char *const *env)
{
	size_t	i;
	t_env	*new_env;

	i = 0;
	new_env = NULL;
	while (env[i])
	{
		if (add_env(&new_env, get_key(env[i]),
				get_value(env[i])) == EXIT_FAILURE)
		{
			free_env(&new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}
