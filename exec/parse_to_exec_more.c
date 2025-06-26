/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/24 16:19:37 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_heredoc_ctx(t_heredoc_ctx *ctx, t_token **lst)
{
	ctx->f = ft_malloc(100, ALLOC);
	if (!ctx->f)
		return (1);
	ctx->st = 0;
	ctx->fd_in = -1;
	ctx->fd_out = -1;
	ctx->f = strj("/tmp/", ft_itoa((long)&ctx->fd_in));
	ctx->fd_out = open(ctx->f, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (ctx->fd_out == -1)
		return (perror("open"), 1);
	ctx->fd_in = open(ctx->f, O_RDONLY);
	if (ctx->fd_in == -1)
		return (perror("open"), skip_till_pipe(lst), close(ctx->fd_out), 1);
	unlink(ctx->f);
	return (0);
}

int	handle_heredoc(t_token *lst, t_env *env)
{
	t_heredoc_ctx	ctx;

	if (init_heredoc_ctx(&ctx, &lst))
		return (skip_till_pipe(&lst), -1);
	signal(SIGINT, &signal_heredoc);
	if (ft_handle_heredoc(lst, env, ctx.fd_out))
		return (close(ctx.fd_in), -2);
	return (ctx.fd_in);
}

int	handle_redirect_in(t_token **lst, t_exec *node)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	if ((*lst)->next->ambg)
	{
		if (node->fd_in > 0)
			close(node->fd_in);
		if (node->fd_out > 2)
			close(node->fd_out);
		skip_till_pipe(lst);
		return (ambigous_red(), 1);
	}
	node->fd_in = open((*lst)->next->value, O_RDONLY);
	if (node->fd_in == -1)
	{
		node->flag = 1;
		perror("minishell");
		skip_till_pipe(lst);
		return (1);
	}
	else
	{
		if ((*lst)->next)
			(*lst) = (*lst)->next;
	}
	return (0);
}

int	handle_append(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	if ((*lst)->next->ambg)
	{
		skip_till_pipe(lst);
		return (ambigous_red(), 1);
	}
	node->fd_out = open((*lst)->next->value, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		node->flag = 1;
		perror("minishell");
		skip_till_pipe(lst);
		return (1);
	}
	else
	{
		if ((*lst)->next)
			(*lst) = (*lst)->next;
	}
	return (0);
}

int	handle_redirect_out(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	if ((*lst)->next->ambg)
	{
		skip_till_pipe(lst);
		return (ambigous_red(), 1);
	}
	if ((*lst)->next && !ft_strcmp((*lst)->next->value, "|") \
	&& (*lst)->next->next)
		(*lst) = (*lst)->next;
	node->fd_out = open((*lst)->next->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		node->flag = 1;
		perror("minishell");
		skip_till_pipe(lst);
		return (1);
	}
	else
	{
		if ((*lst)->next)
			(*lst) = (*lst)->next;
	}
	return (0);
}
