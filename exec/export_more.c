/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:55:49 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/30 13:50:51 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_export(char *opt)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(opt[i]) || opt[i] == '_'))
		return (1);
	i++;
	while (opt[i])
	{
		if (!(ft_isalnum(opt[i]) || opt[i] == '_'))
		{
			if (opt[i] == '+' && opt[i +1] == '=')
				return (0);
			else if (opt[i] == '=')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	bubble_sort_env(t_env *env)
{
	int		swap;
	t_env	*ptr;

	if (!env)
		return ;
	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = env;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_env(ptr, ptr->next);
				swap = 1;
			}
			ptr = ptr->next;
		}
	}
}

void	print_sorted_env(t_env *env, int fd)
{
	bubble_sort_env(env);
	while (env)
	{
		if (env->key && !ft_strcmp("_", env->key))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->key, fd);
		if (env->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}
