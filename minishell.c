/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:06:27 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/24 22:06:05 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (!recevied_from_inp(0, 0))
		ft_putstr_fd("\n", 1);
	rl_on_new_line();
	if (!recevied_from_inp(0, 0))
		rl_redisplay();
	else
		recevied_from_inp(0, 1);
	rl_replace_line("", 1);
	e_status(130, 1);
	(void)sig;
}

void	define_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
}

void	check_ac(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell : no arguments please\n", 2);
		exit(127);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("use terminal please.\n", 2);
		exit(1);
	}
}

void	init_main_ctx(t_main_ctx *ctx, char **env)
{
	ctx->input = NULL;
	ctx->expn = NULL;
	ctx->lst = NULL;
	ctx->exec = NULL;
	ctx->envp = init_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_main_ctx	ctx;

	check_ac(argc);
	(1) && (init_main_ctx(&ctx, env), argv = NULL);
	while (20052)
	{
		define_sig();
		recevied_from_inp(0, 1);
		ctx.input = readline("minishell➤ ");
		if (!ctx.input)
			return (ft_putstr_fd("exit\n", 1), free(ctx.input), \
			ft_malloc(0, CLEAR), e_status(0, 0));
		if (*ctx.input)
			add_history(ctx.input);
		if (ft_parse_command(ctx.input))
			continue ;
		ctx.lst = s_cmd(ft_split(ctx.input), ctx.envp);
		if (!ctx.lst || ft_expand(ctx.lst, ctx.envp))
			continue ;
		ctx.exec = convert_token_to_exec(ctx.lst, ctx.envp);
		if (!ctx.exec)
			continue ;
		execution(ctx.exec, &ctx.envp);
	}
	return (0);
}
