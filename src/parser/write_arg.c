/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:19:50 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		miss_quote(char *line, int i)
{
	char temp;

	temp = (line[i++] == '\"') ? '\"' : '\'';
	while (line[i] && line[i] != temp)
		++i;
	i += line[i] ? 1 : 0;
	return (i);
}

void	assis_coutargv(char *line, int *i, int *count)
{
	if (!(is_delimetr(line[*i])) && !is_agregation(line, *i))
	{
		while (line[*i] && !(is_delimetr(line[*i])) && !spec_token(line, *i))
		{
			if (line[*i] == '\"' || line[*i] == '\'')
				*i = miss_quote(line, *i);
			else
				++(*i);
		}
		++(*count);
		return ;
	}
	if (is_delim(line[*i]))
		++(*i);
	if (is_agregation(line, *i))
	{
		(*i) += 4;
		++(*count);
	}
}

int		count_argv(char *line)
{
	int		i;
	char	temp;
	int		count;

	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = miss_quote(line, i);
			++count;
		}
		else if ((temp = spec_token(line, i)))
		{
			i += temp;
			++count;
		}
		else
			assis_coutargv(line, &i, &count);
	}
	return (count);
}

char	**write_arg(char *line)
{
	char	**arg;
	int		i;
	int		j;
	int		count_arg;

	i = 0;
	j = 0;
	count_arg = count_argv(line);
	if (!count_arg)
		return (NULL);
	if ((arg = (char**)malloc(sizeof(char*) * (count_arg + 1))) == NULL)
		exit(1);
	while (i < count_arg)
	{
		while (line[j] && is_delimetr(line[j]))
			++j;
		arg[i] = get_token(line, &j);
		++i;
	}
	arg[i] = NULL;
	return (arg);
}
