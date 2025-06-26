/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:18:18 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/19 17:19:02 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_pip(char *string)
{
	if (string[0] == '|')
		return (true);
	return (false);
}

bool	ft_check_redirect_in(char *string)
{
	if (string[0] == '<' && string[1] != '<')
		return (true);
	return (false);
}

bool	ft_check_redirect_out(char *string)
{
	if (string[0] == '>' && string[1] != '>')
		return (true);
	return (false);
}

bool	ft_check_append(char *string)
{
	if (string[0] == '>' && string[1] == '>')
		return (true);
	return (false);
}

bool	ft_check_heredoc(char *string)
{
	if (string[0] == '<' && string[1] == '<')
		return (true);
	return (false);
}
