/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:25:10 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/13 11:49:38 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_list(t_list *head)
{
	WOW();
	t_list			*traverse;

	traverse = head;
	while (traverse)
	{
		b_printf("%s\n", traverse->content);
		traverse = traverse->next;
	}
}

void		enqueue(t_list **head, char *content)
{
	WOW();
	t_list			*new;
	t_list			*traverse;

	new = malloc(sizeof(*new));
	new->content = ft_strdup(content);
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
	}
	else
	{
		traverse = *head;
		while (traverse && traverse->next)
			traverse = traverse->next;
		traverse->next = new;
	}
	if (!ft_strncmp(new->content, "PATH", 4))
		g_PATH = new;
}

t_list		*copy_extern_env(void)
{
	WOW();
	t_list			*env;
	int				p;

	env = NULL;
	p = 0;
	while (environ[p])
	{
		enqueue(&env, environ[p]);
		p +=1 ;
	}
	print_list(env);
	return (env);
}

void		init_env(void)
{
	WOW();
	t_list			*env;
	
	env = copy_extern_env();
	g_env = env;
}
/*
void		init_env(void)
{
	WOW();
	char			**env;
	int				len;
	int				p;

	p = 0;
	len = get_pointer_len(environ);
	env = malloc(sizeof(*env) * (len + 1));
	while (environ[p])
	{
		env[p] = strdup(environ[p]);
		if (!strncmp(env[p], "PATH", 4))
			g_PATH = env[p];
		p += 1;
	}
	env[p] = NULL;
	g_env = env;
//	printf("g_env:\n");
//	print_strings(g_env, 0);
	printf("path @ %s\n", g_PATH);
}
*/
