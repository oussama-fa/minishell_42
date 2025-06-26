/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:23 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/28 22:55:34 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	ft_check_end(char *command, char c)
{
	int	index;

	index = 1;
	while (command[index] && command[index] != c)
		index++;
	if (command[index] == c)
		return (index);
	return (ft_syntax_error(), -1);
}

int	ft_check_quots(char *command)
{
	int		index;
	int		resault;
	char	c;

	index = 0;
	resault = -1;
	while (command[index])
	{
		if (ft_strchr("\'\"", command[index]))
		{
			c = command[index];
			resault = ft_check_end(command + index, c);
			if (resault == -1)
				return (e_status(2, 1), 1);
			index += resault;
		}
		index++;
	}
	return (0);
}
