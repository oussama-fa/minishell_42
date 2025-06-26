/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/24 16:42:10 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_execve(t_exec *head, t_env *env)
{
	char		**envp;
	struct stat	sb;

	envp = convert_t_env(env);
	execve(head->cmd, head->opt, envp);
	if (stat(head->cmd, &sb) == -1)
	{
		perror("stat");
		ft_malloc(0, CLEAR);
		exit(errno);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(head->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_malloc(0, CLEAR);
		exit(126);
	}
	perror(head->cmd);
	ft_malloc(0, CLEAR);
	exit(errno);
}

void	in_child(t_exec *head, t_env **env, int *fd)
{
	if (is_builtin(head->cmd))
	{
		setup_child(fd, NULL, head, 1);
		execute_builtin(head, env, true);
		exit(0);
	}
	else
	{
		setup_child(fd, find_env(*env, "PATH"), head, 0);
		call_execve(head, *env);
	}
}

pid_t	execute_cmd(t_exec *head, t_env **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe"), ft_malloc(0, CLEAR), -1);
	child_sig(head->cmd);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), perror("fork"), \
		ft_malloc(0, CLEAR), -1);
	if (pid == 0)
	{
		default_sig();
		in_child(head, env, fd);
	}
	else
		parent_thing(fd, head);
	return (pid);
}

int	execution(t_exec *exec, t_env **env)
{
	int		fd;
	int		j;
	pid_t	last_pid;

	last_pid = -1;
	j = 2;
	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec, env, false), 1);
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (perror("dup()"), ft_malloc(0, CLEAR), 1);
	while (exec)
	{
		if (!exec->flag)
			last_pid = execute_cmd(exec, env);
		if (exec->fd_in != 0)
			close(exec->fd_in);
		if (exec->fd_out > 2)
			close(exec->fd_out);
		exec = exec->next;
	}
	dup2(fd, 0);
	close(fd);
	return (check_exit_status(last_pid));
}
