/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 09:47:07 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/13 09:51:26 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_char(char *s, int old, int new)
{
	WOW();
	char			*ret;
	int				p;

	ret = strdup(s);
	p = 0;
	while (s[p])
	{
		if (s[p] == old)
		{
			ret[p] = new;
		}
		p += 1;
	}
	return (ret);
}

int			get_pointer_len(char **env)
{
	WOW();
	int				p;

	p = 0;
	while (env[p])
	{
//		printf("%s\n", env[p]);
		p += 1;
	}
	return (p);
}

void		free_2d(char **ptrs)
{
	WOW();
	int				p;
	int				len;

	len = get_pointer_len(ptrs);
	p = 0;
	while (ptrs[p] && p < len)
	{
		printf("%s\n", ptrs[p]);
		if (ptrs[p])
			free(ptrs[p]);
		p += 1;
	}
	printf("2\n");
	printf("%p\n", ptrs);
	free(ptrs);
}

int			main(void)
{
	DIR				*dirp;
	struct dirent 	*entry;

	dirp = opendir(".");
	entry = readdir(dirp);
	printf("%s\n", entry->d_name);
	init_env();
	read_line();
	//free_2d(g_env);
}
