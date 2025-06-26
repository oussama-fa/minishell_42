/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:24:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/23 10:33:22 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delet_node(t_env **env, char *key)
{
	t_env	*head;
	t_env	*prev;

	if (!env || !*env)
		return ;
	head = (*env)->next;
	prev = NULL;
	if (!*env)
		return ;
	if (!ft_strcmp((*env)->key, key))
	{
		*env = (*env)->next;
		return ;
	}
	prev = *env;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			prev->next = head->next;
			return ;
		}
		prev = head;
		head = head->next;
	}
}

void	ft_unset(char **opt, t_env **env)
{
	while (*opt)
	{
		delet_node(env, *opt);
		opt++;
	}
}
