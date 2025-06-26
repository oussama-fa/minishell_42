/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:56:46 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/21 18:11:15 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_len_wo_q(char *value)
{
	size_t	count;
	size_t	i;
	size_t	count_inside;
	char	c;

	(1) && (i = 0, count = 0);
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
		{
			(1) && (c = value[i], count_inside = 0, i++);
			while (value[i] && value[i] != c)
				(1) && (count_inside++, i++);
			if (value[i] == c)
				i++;
			count += count_inside;
		}
		else
			(1) && (count++, i++);
	}
	return (count);
}

char	*remove_q(char *v)
{
	t_expand	s;

	(1) && (s.b = 0, s.s_q = false, s.d_q = false, s.i = 0);
	if (!v)
		return (ft_strdup(""));
	s.c = ft_malloc(ft_len_wo_q(v) + 1, ALLOC);
	while (v[s.b])
	{
		if (v[s.b] == '\'' && !s.d_q)
			(1) && (s.s_q = !s.s_q, s.b++);
		else if (v[s.b] == '\"' && !s.s_q)
			(1) && (s.d_q = !s.d_q, s.b++);
		else if (v[s.b] == '$' && !s.d_q && \
			!s.s_q && v[s.b + 1] && ft_strchr("\'\"", v[s.b + 1]))
			s.b++;
		else if (v[s.b] == '$' && v[s.b + 1] && v[s.b + 1] == '$')
		{
			(1) && (s.c[s.i] = v[s.b], s.c[s.i + 1] = v[s.b + 1]);
			(1) && (s.b += 2, s.i += 2);
		}
		else
			(1) && (s.c[s.i] = v[s.b], s.b++, s.i++);
	}
	s.c[s.i] = '\0';
	return (s.c);
}

int	check_end(char *string, char c, int *index)
{
	while (string[*index] && string[*index] != c)
		(*index)++;
	if (!string[*index])
	{
		e_status(2, 1);
		ft_syntax_error();
		return (1);
	}
	return (0);
}

int	ft_check_braces(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '{')
		{
			if (check_end(string, '}', &index))
				return (1);
			index++;
		}
		else if (string[index] == '}')
			return (e_status(2, 1), ft_syntax_error(), 1);
		else
			index++;
	}
	return (0);
}

int	check_case_rp(char *string, int *i)
{
	if (string[*i] == '>' && string[*i + 1] && string[*i + 1] == '|')
	{
		*i += 1;
		return (1);
	}
	return (0);
}
