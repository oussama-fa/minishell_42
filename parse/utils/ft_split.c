/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:18:55 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/21 17:06:03 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_spaces(char *s, int i)
{
	while (s[i] && ft_is_space(s[i]))
		i++;
	return (i);
}

int	acttual_len(char *s, int i)
{
	int		start;
	char	c;

	start = i;
	while (s[i])
	{
		if (ft_strchr("|<>", s[i]))
			return (i - start);
		else if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (!s[i])
				return (i - start);
		}
		else if (ft_is_space(s[i]))
			break ;
		i++;
	}
	return (i - start);
}

int	get_word_len(char *s, int i)
{
	int	start;

	start = i;
	if (s[i] == '|')
		return (1);
	if (ft_strchr("<>", s[i]))
	{
		while (ft_strchr("<>", s[i]) && s[i])
			i++;
		return (i - start);
	}
	return (acttual_len(s, i));
}

int	ft_countword(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		i += get_word_len(s, i);
		count++;
	}
	return (count);
}

char	**ft_split(char *s)
{
	int		i;
	int		j;
	int		word_len;
	int		words;
	char	**lst;

	(1) && (i = 0, j = 0, words = ft_countword(s));
	if (words == 0)
		return (free(s), NULL);
	lst = ft_malloc(sizeof(char *) * (words + 1), ALLOC);
	if (!lst)
		return (free(s), NULL);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		word_len = get_word_len(s, i);
		lst[j++] = subs(s, i, word_len);
		i += word_len;
	}
	lst[j] = NULL;
	return (free(s), lst);
}
