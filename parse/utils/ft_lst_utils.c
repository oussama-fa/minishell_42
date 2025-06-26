/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:14:28 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/24 18:04:54 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	shouldnt_split(char *v, t_tokentype type, int f)
{
	int		i;
	bool	d_q;
	bool	s_q;
	int		operator;

	i = 0;
	d_q = false;
	s_q = false;
	operator = 0;
	if (type == R_FILE)
		return (1);
	while (v[i])
	{
		if (v[i] == '\'' && !d_q)
			s_q = !s_q;
		if (v[i] == '\"' && !s_q)
			d_q = !d_q;
		if (v[i] == '$' && v[i + 1] && id_check(v + 1 + i) && operator && f)
			return (1);
		if (v[i] == '=' && !d_q)
			operator = 1;
		i++;
	}
	return (0);
}

void	ft_split_ex(t_token **lst, t_env *e, char *value, t_tokentype type)
{
	t_token		*elt;
	char		*exp;
	int			f;

	(1) && (elt = NULL, f = check_env(value, e));
	if (!f || (f && type == R_FILE))
	{
		exp = exp_val(value, e);
		(1) && (elt = ft_malloc(sizeof(t_token), ALLOC), elt->type = type);
		(1) && (elt->value = exp, elt->next = NULL, elt->previous = NULL);
		elt->removed = 1;
		if (type == R_FILE)
		{
			if (!exp || !exp[0] || f)
				elt->ambg = 1;
		}
		else
			elt->ambg = 0;
		if (type == R_FILE)
			type = WORD;
		return (ft_lstadd_back(lst, elt));
	}
	else
		ft_split_expanded(value, lst, e);
}

void	ft_lstnew(t_token **lst, t_spli_cmd s, t_env *e, int r)
{
	t_token		*elt;
	t_token		*last;

	elt = ft_malloc(sizeof(t_token), ALLOC);
	(1) && (elt->value = s.cmd, elt->next = NULL);
	(1) && (elt->previous = NULL, elt->fd_reder = -1);
	(1) && (elt->ambg = 0, elt->heredoc_expn = 0, elt->removed = r);
	last = ft_lstlast(*lst);
	if (last && last->type == HERDOC)
		s.type = DELEMTER;
	if (ft_check_var(s.cmd) && s.type != DELEMTER)
		return (ft_split_ex(lst, e, s.cmd, s.type));
	if (s.type == DELEMTER && (ft_strchr(s.cmd, '\'') \
	|| ft_strchr(s.cmd, '\"')))
	{
		elt->value = remove_q(s.cmd);
		elt->heredoc_expn = 1;
	}
	elt->type = s.type;
	ft_lstadd_back(lst, elt);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->previous = tmp;
}
