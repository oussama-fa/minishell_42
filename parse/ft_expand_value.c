/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:56:21 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/25 13:01:29 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_quotes(char *s, t_expand *e)
{
	if (s[e->i] == '\'' && !e->d_q)
	{
		e->s_q = !e->s_q;
		e->i++;
		return (true);
	}
	else if (s[e->i] == '\"' && !e->s_q)
	{
		e->d_q = !e->d_q;
		e->i++;
		return (true);
	}
	return (false);
}

void	init_expand_vars(char **nv, t_expand *e, bool *reset)
{
	*nv = NULL;
	e->i = 0;
	e->s_q = false;
	e->d_q = false;
	*reset = true;
}

void	first_expand(t_expand_ctx *c)
{
	t_var	*list;

	list = s_var(c->s);
	while (list)
	{
		if (!ft_strcmp(list->value, "$?"))
			list->value = ft_itoa(e_status(0, 0));
		else if (!ft_strcmp(list->value, "$"))
			list->value = list->value;
		else if (list->type == VAR)
			list->value = g_env(list->value, c->envp);
		else
			list->value = ft_remove_quotes(c, list->value);
		c->nv = strj(c->nv, list->value);
		list = list->next;
	}
}

void	init_expan(t_expand_ctx *ctx, char *s, t_env *envp)
{
	ctx->nv = NULL;
	ctx->e.i = 0;
	ctx->e.s_q = false;
	ctx->e.d_q = false;
	ctx->r = true;
	ctx->envp = envp;
	ctx->s = s;
	ctx->i = 0;
}

char	*exp_val(char *s, t_env *envp)
{
	t_expand_ctx	ctx;

	init_expan(&ctx, s, envp);
	first_expand(&ctx);
	return (ctx.nv);
}
