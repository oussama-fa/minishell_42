/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:05 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/24 16:45:05 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stop_redirect(t_token *lst, t_env *envp)
{
	t_token	*tmp;
	bool	f;

	tmp = lst;
	f = false;
	while (tmp)
	{
		if (tmp->type == WORD)
			f = true;
		tmp = tmp->next;
	}
	(void)envp;
	if (f)
		return (0);
	return (1);
}

bool	check_assi(char *st, int index)
{
	int	i;

	i = index;
	while (st[index] && !ft_is_space(st[index]))
	{
		if (ft_strchr("+-=", st[index]))
			return (1);
		index++;
	}
	while (i >= 0 && !ft_is_space(st[i]))
	{
		if (ft_strchr("+-=", st[i]))
			return (1);
		i--;
	}
	return (false);
}

bool	should_expand(char *s, t_expand e)
{
	return ((s[e.i] == '$' && !e.s_q && s[e.i + 1] \
	&& !delimter(s, e.i)));
}

bool	is_invalid_dollar_after_op(t_expand_ctx *c)
{
	if (c->s[c->e.i] == '$' && c->s[c->e.i + 1] == '"' \
		&& c->e.d_q)
		return (true);
	return ((c->s[c->e.i] == '$' && check_assi(c->s, c->e.i)));
}

int	check_for_s(char *string)
{
	int	indx;

	indx = 0;
	if (!string)
		return (0);
	while (string[indx])
	{
		if (ft_is_space(string[indx]))
			return (1);
		indx++;
	}
	return (0);
}
