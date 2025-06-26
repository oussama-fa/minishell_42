/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:56:36 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/21 18:04:08 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	id_check(char *var)
{
	int	i;

	i = 0;
	if (!(ft_isalnum(var[i]) || var[i] == '?' \
	|| var[i] == '_' || var[i] == '$'))
		return (0);
	i++;
	while (var[i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '?' \
		|| var[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

int	skip_variable(char *value, int index)
{
	int	count;

	count = index + 1;
	if (value[count] == '$' || value[count] == '?' \
		|| (value[count] >= '0' && value[count] <= '9'))
	{
		return (2);
	}
	count += id_check(value + count);
	return (count - index);
}

size_t	ft_len_wo_quotes(t_expand_ctx *c, char *value)
{
	size_t	count;
	size_t	i;
	bool	d_q;
	bool	s_q;

	(1) && (i = 0, count = 0, d_q = c->e.d_q, s_q = c->e.s_q);
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'' && !d_q)
		{
			s_q = !s_q;
			i++;
		}
		else if (value[i] == '\"' && !s_q)
		{
			d_q = !d_q;
			i++;
		}
		else
			(1) && (count++, i++);
	}
	return (count);
}

char	*ft_remove_quotes(t_expand_ctx *c, char *tmp)
{
	int		index;
	char	*clean;
	int		index_tmp;

	index = 0;
	index_tmp = 0;
	if (!tmp)
		return (ft_strdup(""));
	clean = ft_malloc(ft_len_wo_quotes(c, tmp) + 1, ALLOC);
	while (tmp[index_tmp])
	{
		if (tmp[index_tmp] == '\'' && !c->e.d_q)
			(1) && (c->e.s_q = !c->e.s_q, index_tmp++);
		else if (tmp[index_tmp] == '\"' && !c->e.s_q)
			(1) && (c->e.d_q = !c->e.d_q, index_tmp++);
		else if (tmp[index_tmp] == '$' && !c->e.d_q \
			&& !c->e.s_q && ft_strchr("\'\"", tmp[index + 1]))
			index_tmp++;
		else
			(1) && (clean[index] = tmp[index_tmp], index_tmp++, index++);
	}
	clean[index] = '\0';
	return (clean);
}

int	ft_expand(t_token *lst, t_env *envp)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (check_type_exp(tmp->type))
			tmp->type = WORD;
		if (tmp->type == HERDOC)
		{
			tmp->fd_reder = handle_heredoc(tmp, envp);
			if (tmp->fd_reder == -1)
				continue ;
			else if (tmp->fd_reder == -2)
				return (1);
		}
		if (!tmp->removed)
			tmp->value = remove_q(tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
