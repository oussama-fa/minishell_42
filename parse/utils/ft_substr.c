/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:55:26 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/19 16:55:28 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*subs(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	tot_len;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s) || !len)
		return (NULL);
	if (len > ft_strlen(s + start))
		tot_len = ft_strlen(s + start) + 1;
	else
		tot_len = len + 1;
	str = ft_malloc(tot_len, ALLOC);
	ft_strlcpy(str, s + start, tot_len);
	return (str);
}
