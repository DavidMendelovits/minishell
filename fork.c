/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:40:52 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/13 20:14:40 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		execute(char *path, char **argv)
{
	int			pid;
	int			status;

	if (!strcmp(path, "/usr/bin/env"))
	{
		print_list(g_env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, environ);
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		status = -1;
	}
	else
	{
		if (waitpid(pid, &status, 0) != pid)
		{
			status = 1;
		}
		return ;
	}
}
