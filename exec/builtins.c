/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/14 13:33:07 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_t_env(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_env(env);
	ret = ft_malloc(sizeof(char *) * (size + 1), ALLOC);
	while (env)
	{
		if (env->key && env->value)
		{
			tmp = strj(env->key, "=");
			ret[i] = strj(tmp, env->value);
			i++;
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *exec, t_env **env, bool forked)
{
	if (!ft_strcmp(exec->cmd, "echo") && !exec->flag)
		ft_echo(exec->opt, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "cd") && !exec->flag)
		ft_cd(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "pwd") && !exec->flag)
		ft_pwd(*env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "export") && !exec->flag)
		ft_export(exec->opt, env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "unset") && !exec->flag)
		ft_unset(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "env") && !exec->flag)
		ft_env(*env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "exit") && !exec->flag)
		ft_exec_exit(exec->opt, forked);
	if (forked)
		exit(e_status(0, 0));
}
