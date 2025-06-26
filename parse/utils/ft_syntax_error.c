/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/21 18:24:28 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell : Syntax error\n", 2);
}

int	delimter(char *s, size_t index)
{
	if (index >= ft_strlen(s))
		return (0);
	while (1)
	{
		if (index > 0 && s[index] == '<' && s[index - 1] == '<')
			return (1);
		if (index == 0)
			break ;
		index--;
	}
	return (0);
}

int	check_env(char *v, t_env *e)
{
	t_expand	ex;

	(1) && (ex.i = 0, ex.d_q = false, ex.s_q = false, ex.b = 0);
	while (v[ex.i])
	{
		while (v[ex.i])
		{
			if (v[ex.i] == '=' && !ex.d_q && !ex.d_q)
				ex.b = 1;
			if (v[ex.i] == '$' && v[ex.i + 1] \
				&& id_check(v + ex.i + 1) && !ex.s_q && !ex.d_q)
				break ;
			if (v[ex.i] == '\'' && !ex.d_q)
				ex.s_q = !ex.s_q;
			else if (v[ex.i] == '\"' && !ex.s_q)
				ex.d_q = !ex.d_q;
			ex.i++;
		}
		if (!v[ex.i])
			break ;
		(1) && (ex.c = g_env(v + ex.i, e), ex.i += skip_variable(v, ex.i));
		if (check_for_s(ex.c) && !ex.b)
			return (1);
	}
	return (0);
}
