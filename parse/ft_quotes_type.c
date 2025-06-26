/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:28:53 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/28 15:52:22 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes_type(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '\'')
			return (SINGLE);
		if (string[index] == '\"')
			return (COUPLE);
		index++;
	}
	return (0);
}
