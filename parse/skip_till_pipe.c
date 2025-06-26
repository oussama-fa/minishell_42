/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_till_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:30:49 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/24 22:02:07 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_till_pipe(t_token **lst)
{
	if (!lst)
		return ;
	while ((*lst)->next && (*lst)->next->type != PIPE)
		(*lst) = (*lst)->next;
}

int	handle_redirects(t_token **lst, t_exec *node)
{
	int	status;

	status = 0;
	if ((*lst)->type == HERDOC)
	{
		if ((*lst)->fd_reder == -1)
			status = 1;
		else
		{
			if (node->fd_in != -1)
				close (node->fd_in);
			node->fd_in = (*lst)->fd_reder;
		}
	}
	else if ((*lst)->type == R_IN)
		status = handle_redirect_in(lst, node);
	else if ((*lst)->type == APPEND)
		status = handle_append(lst, node);
	else if ((*lst)->type == R_OUT)
		status = handle_redirect_out(lst, node);
	if (status && status != 33)
		e_status(1, 1);
	return (status);
}
