/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:15:31 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/14 18:28:30 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_default_env(t_env **env, char *pwd)
{
	char	*path;

	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	ft_lstadd_back_exec(env, ft_lstnew_exec(ft_strdup("OLDPWD"), NULL));
	ft_lstadd_back_exec(env, ft_lstnew_exec(ft_strdup("PATH"),
			ft_strdup(path)));
	ft_lstadd_back_exec(env, ft_lstnew_exec(ft_strdup("PWD"), ft_strdup(pwd)));
	ft_lstadd_back_exec(env, ft_lstnew_exec(ft_strdup("SHLVL"), \
			ft_strdup("1")));
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*equal;
	char	*key;
	char	*value;
	char	*pwd;

	env = NULL;
	pwd = getcwd(NULL, 0);
	if (!envp || !*envp)
		init_default_env(&env, pwd);
	while (envp && *envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			key = subs(*envp, 0, equal - *envp);
			value = ft_strdup(equal + 1);
		}
		else
			(1) && (key = ft_strdup(*envp), value = NULL);
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
		envp++;
	}
	free(pwd);
	return (env);
}

char	*get_env_value(t_env **env, char *path)
{
	t_env	*tmp;
	char	*value;

	tmp = find_env(*env, path);
	if (!tmp)
		return (NULL);
	value = ft_strdup(tmp->value);
	return (value);
}

t_env	*find_env(t_env	*env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_env(t_env *env, int fd)
{
	char	*av[3];

	av[0] = ft_strdup("export");
	av[1] = strj("_=", "/usr/bin/env");
	av[2] = NULL;
	ft_export(av, &env, 1);
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
	return (0);
}
