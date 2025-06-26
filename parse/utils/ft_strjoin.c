/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:56:08 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/19 16:56:09 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strj(char *s1, char *s2)
{
	char	*string;
	size_t	len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	string = ft_malloc(len, ALLOC);
	ft_strlcpy(string, s1, len);
	ft_strlcat(string, s2, len);
	return (string);
}
