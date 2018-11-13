/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:36:10 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/13 09:36:44 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_args(char *s)
{
	int				p;
	int				count;

	p = 0;
	count = 0;
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else if (s[p] == '"')
		{
			count += 1;
			p += 1;
			while (s[p] && s[p] != '"')
			{
				p += 1;
			}
			p += 1;
		}
		else
		{
			count += 1;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
		}
	}
	return (count);
}

void		expand_tilde(char **tilde)
{
	WOW();
	char			*tmp;
	char			*new;
	int				p;

	if (!strncmp(*tilde, "~+", 2))
	{
		new = search_env("PWD");
		p = 2;
	}
	else if (!strncmp(*tilde, "~-", 2))
	{
		new = search_env("OLDPWD");
		p = 2;
	}
	else
	{
		new = search_env("HOME");
		p = 1;
	}
	printf("home = %s\n", new);
	printf("p = %d\n", p);
	printf("tilde = %s\n", *tilde);
	if (!(*tilde)[p])
	{
		printf("simple\n\n");
		free(*tilde);
		*tilde = new;
	}
	else if ((int)strlen(*tilde) > p && (*tilde)[p] == '/')
	{
		printf("hum\n\n");
		tmp = ft_strdup_range(*tilde, ft_strchr_index(*tilde, '/'), strlen(*tilde) - 1);
		printf("hum\n\n");
		free(*tilde);
		*tilde = trip_join(new, 0, tmp);
		free(new);
		free(tmp);
	}
	else
	{
		free(new);
	}
	printf("--------expansion = %s\n", *tilde);
}

char		**split_stream(char *s)
{
	WOW();
	char			**strings;
	int				p;
	int				sp;
	int				arg_count;
	int				begin;

	arg_count = count_args(s);
	printf("arg_count = %d\n", arg_count);
	strings = malloc(sizeof(*strings) * (arg_count + 1));
	p = 0;
	sp = 0;
	while (s[p])
	{
		printf("%s\n%*c\n", s, p - 1, s[p]);
		if (s[p] == ' ' || s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else if (s[p] == '"')
		{
			begin = ++p;
			while (s[p] && s[p] != '"')
			{
				p += 1;
			}
			if (!s[p])
			{
				g_err_num = PAREN;
				return (write_error(MISSING_P, sizeof(MISSING_P)));
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			printf("strings[%d] = %s\n", sp, strings[sp]);
			sp += 1;
			p += 1;
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			if (strings[sp][0] == '~')
				expand_tilde(&strings[sp]);
			printf("strings[%d] = %s\n", sp, strings[sp]);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
}
