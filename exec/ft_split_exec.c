/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:23:39 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/24 20:54:51 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_countwords(char *str, char c)
{
	size_t	i;
	size_t	rst;
	size_t	cnt;

	i = 0;
	rst = 0;
	cnt = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			rst = 0;
		else if (rst == 0)
		{
			rst = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static char	*ft_strndup(char *str, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = ft_malloc(n + 1, ALLOC);
	while (n--)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static int	ft_split_helper(int *i, char const *s, char c)
{
	int	start;

	while (s[*i] == c && (s[*i]))
		(*i)++;
	start = *i;
	while (s[*i] != c && (s[*i]))
		(*i)++;
	return (start);
}

char	**ft_split_exec(char const *s, char c)
{
	int		i;
	int		word;
	int		start;
	char	**strs;

	(1) && (i = 0, word = 0, start = 0);
	strs = ft_malloc((sizeof(char *)) * (ft_countwords((char *)s, c) + 1),
			ALLOC);
	while (s && s[i])
	{
		start = ft_split_helper(&i, s, c);
		if (i > start)
		{
			strs[word++] = ft_strndup((char *)s + start, i - start);
			if (!strs[word - 1])
				return (NULL);
		}
	}
	strs[word] = NULL;
	return (strs);
}
