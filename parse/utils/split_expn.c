/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:31:15 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/15 20:38:57 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	skip_tillvar(char *val, size_t i)
{
	size_t	start;
	bool	s_q;
	bool	d_q;

	start = i;
	d_q = false;
	s_q = false;
	while (val[i])
	{
		if (val[i] == '\'' && !d_q)
			s_q = !s_q;
		if (val[i] == '\"' && !s_q)
			d_q = !d_q;
		if (val[i] == '$' && id_check(val + i + 1) && !s_q)
			break ;
		i++;
	}
	return (i - start);
}

int	list_size(char **list)
{
	int	size;

	if (!list)
		return (0);
	size = 0;
	while (list[size])
		size++;
	return (size);
}

void	add_to_lst(t_token **lst, char **list, char *cmd, t_var *vars)
{
	t_spli_cmd	s;
	t_token		*tmp;
	int			j;
	int			size;

	(1) && (j = 0, s.type = WORD, size = list_size(list));
	while (list[j])
	{
		if (j == 0)
			s.cmd = strj(cmd, list[j++]);
		else if (j == size - 1 && vars->next)
			break ;
		else
			s.cmd = list[j++];
		tmp = ft_malloc(sizeof(t_token), ALLOC);
		(1) && (tmp->value = s.cmd, tmp->next = NULL);
		(1) && (tmp->previous = NULL, tmp->fd_reder = -1);
		(1) && (tmp->ambg = 0, tmp->heredoc_expn = 0, tmp->removed = 1);
		tmp->type = WORD;
		ft_lstadd_back(lst, tmp);
	}
}

void	ft_split_expanded(char *val, t_token **lst, t_env *env)
{
	t_expand_ctx	ctx;
	t_spli_cmd		s;
	t_var			*vs;
	char			**v_e;

	(1) && (v_e = NULL, s.type = WORD, s.cmd = NULL, vs = s_var(val));
	init_expan(&ctx, val, env);
	while (vs)
	{
		if (vs->type == WORD_V)
		{
			s.cmd = ft_remove_quotes(&ctx, vs->value);
			if (v_e)
				s.cmd = strj(v_e[list_size(v_e) - 1], s.cmd);
		}
		if (vs->type == VAR || (vs->type == WORD_V && !vs->next))
		{
			vs->value = g_env(vs->value, env);
			v_e = a_split(vs->value);
			add_to_lst(lst, v_e, s.cmd, vs);
		}
		if (vs->type == VAR && vs->next && vs->next->type == VAR)
			s.cmd = v_e[list_size(v_e) - 1];
		vs = vs->next;
	}
}
