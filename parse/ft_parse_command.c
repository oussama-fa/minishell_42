/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:30:18 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/15 20:43:32 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_operator(char *string, int index, char c)
{
	int	count;

	count = 0;
	while (string[index] == c)
	{
		count++;
		index++;
	}
	return (count);
}

void	skip_quotes(char *string, int *i)
{
	char	c;

	c = string[*i];
	(*i)++;
	while (string[*i] && string[*i] != c)
		(*i)++;
}

int	check_operator(char *string, int *i)
{
	char	c;

	c = string[*i];
	if (check_case_rp(string, i))
		return (2);
	if (ft_count_operator(string, *i, string[*i]) > 2)
		return (e_status(2, 1), ft_syntax_error(), 1);
	while (string[*i] == c)
		(*i)++;
	skip_s(string, i);
	if (!string[*i] || ft_strchr("|<>", string[*i]))
		return (e_status(2, 1), ft_syntax_error(), 1);
	return (0);
}

int	ft_check_syntax(char *string, int count, int i)
{
	int	s;

	(1) && (i = 0, count = 0);
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
			skip_quotes(string, &i);
		else if (string[i] && (string[i] == '<' || string[i] == '>'))
		{
			s = check_operator(string, &i);
			if (s == 2)
				continue ;
			else if (s == 1)
				return (1);
		}
		else if (string[i] && check_pip(string, &i))
			return (1);
		if (string[i])
			i++;
	}
	return (0);
}

int	ft_parse_command(char *string)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (string)
	{
		if (ft_check_quots(string))
			return (free(string), 1);
		if (ft_check_syntax(string, count, i))
			return (free(string), 1);
		if (ft_check_braces(string))
			return (free(string), 1);
	}
	return (0);
}
