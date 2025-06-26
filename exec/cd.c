/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:07:07 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/27 17:42:39 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	getcwd_fail(char *path, t_env **env, char **hold_pwd, char *newpwd)
{
	char	*av[3];

	ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories\n", 2);
	newpwd = ft_strdup(path);
	if (!ft_strcmp(path, ".") || !ft_strcmp(path, ".."))
	{
		av[0] = ft_strdup("export");
		if (find_env(*env, "PWD"))
			av[1] = strj("PWD+=/", path);
		else
		{
			av[1] = strj("PWD=", strj(*hold_pwd, "/.."));
			*hold_pwd = av[1];
		}
		av[2] = NULL;
		ft_export(av, env, 1);
	}
}

void	update_oldpwd(t_env **env, char *oldpwd)
{
	char	*av[3];

	av[0] = ft_strdup("export");
	av[1] = strj("OLDPWD=", oldpwd);
	av[2] = NULL;
	ft_export(av, env, 1);
}

int	change_dir(char *path, t_env **env, char **hold_pwd)
{
	char	*oldpwd;
	char	*newpwd;
	char	*av[3];

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup2(get_env_value(env, "PWD"));
	else
		update_oldpwd(env, oldpwd);
	if (chdir(path) == -1)
		return (free(oldpwd), perror("cd"), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		getcwd_fail(path, env, hold_pwd, newpwd);
	else
	{
		*hold_pwd = ft_strdup(newpwd);
		av[0] = ft_strdup("export");
		av[1] = strj("PWD=", newpwd);
		av[2] = NULL;
		ft_export(av, env, 1);
		free(newpwd);
	}
	free(oldpwd);
	return (0);
}

char	*ft_cd(char **opt, t_env **env)
{
	char		*home;
	static char	*hold_pwd;

	if (!opt && !env)
		return (hold_pwd);
	if (!opt[1])
	{
		home = get_env_value(env, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), \
					e_status(1, 1), NULL);
		return (change_dir(home, env, &hold_pwd), NULL);
	}
	if (opt[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	else if (opt[1])
		return (change_dir(opt[1], env, &hold_pwd), NULL);
	return (NULL);
}
