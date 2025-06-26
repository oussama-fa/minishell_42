/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:16:24 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/24 19:53:47 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit_status(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)", 19);
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				write(1, "\n", 1);
				exit_code = 128 + WTERMSIG(status);
			}
		}
		pid = wait(&status);
	}
	e_status(exit_code, 1);
	return (exit_code);
}

void	cmd_not_found(char *cmd)
{
	int	k;

	k = 2;
	if (!cmd)
		exit(0);
	write(2, cmd, ft_strlen(cmd));
	ft_putstr_fd(": command not found\n", 2);
	ft_malloc(0, CLEAR);
	exit(127);
}

int	parent_thing(int *fd, t_exec *head)
{
	if (head->next && dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	setup_child(int *fd, t_env *path, t_exec *head, int bltn)
{
	char	*pth;

	if (!bltn)
	{
		if (path)
			pth = path->value;
		else
			pth = "";
		head->cmd = get_cmd_path(head->cmd, pth);
	}
	if (head->next)
		dup2(fd[1], 1);
	if (head->fd_in != 0)
	{
		dup2(head->fd_in, 0);
		close(head->fd_in);
	}
	if (head->fd_out != 1)
	{
		dup2(head->fd_out, 1);
		close(head->fd_out);
	}
	close(fd[1]);
	close(fd[0]);
}
