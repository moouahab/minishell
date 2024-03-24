/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:52:43 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:52:45 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	check_error(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && i < ft_strlen(key) - 1)
	{
		if (ft_isdigit(key[i]) || (!ft_isalnum(key[i]) && key[i] != '_'))
		{
			write(2, "export: '", 9);
			write(2, key, ft_strlen(key));
			write(2, "': not a valid identifier\n", 26);
			free(key);
			return (1);
		}
		i++;
	}
	if (ft_isdigit(key[i]) || (!ft_isalnum(key[i]) && key[i] != '_'
			&& key[i] != '+'))
	{
		write(2, "export: '", 9);
		write(2, key, ft_strlen(key));
		write(2, "': not a valid identifier\n", 26);
		free(key);
		return (1);
	}
	return (0);
}

void	add_empty_value_to_env(char *key, t_shell *shell, char *value,
		char *var)
{
	if (is_in_env(key, shell->env))
		update_value(&shell->env, key, ft_strdup(value));
	else if (ft_strchr(var, '='))
		add_env(&shell->env, ft_strdup(key), ft_strdup(value));
}

void	add_or_update(char *key, char *value, char *var, t_shell *shell)
{
	value = add_to_prev_value(key, value, shell);
	if (!value)
	{
		if (ft_strchr(var, '='))
			value = ft_strdup("");
		add_empty_value_to_env(key, shell, value, var);
		if (is_in_env(key, shell->env_cpy))
			update_value(&shell->env_cpy, key, ft_strdup(value));
		else
			add_env(&shell->env_cpy, ft_strdup(key), ft_strdup(value));
	}
	else
	{
		if (is_in_env(key, shell->env_cpy))
			update_value(&shell->env_cpy, key, ft_strdup(value));
		if (is_in_env(key, shell->env))
			update_value(&shell->env, key, ft_strdup(value));
		else
			add_env(&shell->env, ft_strdup(key), ft_strdup(value));
		if (!is_in_env(key, shell->env_cpy))
			add_env(&shell->env_cpy, ft_strdup(key), ft_strdup(value));
	}
	if (value)
		free(value);
}

int	do_export(char *var, t_shell *shell)
{
	char	*key;
	char	*value;

	key = get_key(var);
	if (!key)
		return (1);
	if (check_error(key) == 1)
		return (1);
	value = get_value(var);
	add_or_update(key, value, var, shell);
	free(key);
	return (0);
}

int	bn_export(char **argv, t_shell *shell)
{
	t_env	*current;
	size_t	i;
	int		ret_value;

	sort_env(&shell->env_cpy);
	current = shell->env_cpy;
	i = 1;
	ret_value = 0;
	if (argv[1] == NULL)
	{
		while (current)
		{
			print_env_var(current);
			current = current->next;
		}
	}
	else
	{
		while (argv[i])
		{
			if (do_export(argv[i++], shell) == 1)
				ret_value = 1;
		}
	}
	return (ret_value);
}
