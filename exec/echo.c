/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:14:46 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/27 17:42:45 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_option(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd, int fd)
{
	int	nline;
	int	i;

	i = 1;
	nline = 0;
	while (cmd[i] && is_valid_option(cmd[i]))
	{
		nline = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!nline)
		write(fd, "\n", 1);
	e_status(0, 1);
	return (0);
}
