/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:20:47 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/30 17:16:42 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_plus_equal(char *opt, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = subs(opt, 0, ft_strstr(opt, "+=") - opt);
	value = ft_strdup(ft_strstr(opt, "+=") + 2);
	tmp = find_env(*env, key);
	if (tmp && tmp->value)
		tmp->value = strj(tmp->value, value);
	else if (tmp)
		tmp->value = value;
	else
		ft_lstadd_back_exec(env, ft_lstnew_exec(key, value));
}

void	handle_equal_or_none(char *opt, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	if (ft_strchr(opt, '='))
	{
		key = subs(opt, 0, ft_strchr(opt, '=') - opt);
		value = ft_strdup(ft_strchr(opt, '=') + 1);
	}
	else
	{
		key = ft_strdup(opt);
		value = NULL;
	}
	tmp = find_env(*env, key);
	if (tmp)
		tmp->value = value;
	else
		ft_lstadd_back_exec(env, ft_lstnew_exec(key, value));
}

void	err_identifier(char *opt)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(opt, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	e_status(1, 1);
}

int	ft_export(char **opt, t_env **env, int fd)
{
	int		i;
	t_env	*tmp;
	char	*ptr;

	i = 0;
	if (!opt[1])
		return (print_sorted_env(*env, fd), 0);
	while (opt[++i])
	{
		if (is_valid_export(opt[i]))
		{
			err_identifier(opt[i]);
			continue ;
		}
		tmp = find_env(*env, opt[i]);
		if (tmp && tmp->value && !ft_strchr(opt[i], '='))
			continue ;
		ptr = ft_strchr(opt[i], '=');
		if (ptr && *(ptr -1) == '+')
			handle_plus_equal(opt[i], env);
		else
			handle_equal_or_none(opt[i], env);
	}
	return (e_status(0, 0), 0);
}
