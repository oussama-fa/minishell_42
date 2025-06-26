/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_bracets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:22:13 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/16 17:16:40 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	recevied_from_inp(int set, int st)
{
	static int	j;

	if (st)
		j = set;
	return (j);
}

int	check_pip(char *s, int *i)
{
	int	index;

	index = *i;
	if (s[*i] == '|')
	{
		index--;
		while (index >= 0 && (s[index] == 32 || s[index] == '\t'))
			index--;
		if (index == -1)
			return (e_status(2, 1), ft_syntax_error(), 1);
		if (ft_count_operator(s, *i, s[*i]) > 1)
			return (e_status(2, 1), ft_syntax_error(), 1);
		*i += 1;
		skip_s(s, i);
		if (!s[*i] || s[*i] == '|')
			return (e_status(2, 1), ft_syntax_error(), 1);
	}
	return (0);
}

void	skip_s(char *s, int *i)
{
	while (s[*i] == 32 || s[*i] == '\t')
		*i += 1;
}
