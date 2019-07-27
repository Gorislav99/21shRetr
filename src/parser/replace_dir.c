/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:14:24 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:31:20 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	exist_dir(char *line, int i, int lenght)
{
	char	*temp;
	char	*tmp;
	int		status;

	temp = ft_strsub(line, i, lenght - i);
	tmp = ft_strjoin("/Users/", temp);
	status = access(tmp, 0);
	if (status == -1)
	{
		write(2, "21sh: no such user or named directory: ", 39);
		write(2, temp, ft_strlen(temp));
		write(2, "\n", 1);
	}
	free(temp);
	free(tmp);
	if (status == -1)
		return (0);
	else
		return (1);
}

static char	*assist_tilde(char *chang_line, int *i)
{
	int lenght;
	int j;

	j = *i;
	lenght = j;
	while (chang_line[lenght] && !is_delimetr(chang_line[lenght]))
		++lenght;
	if (exist_dir(chang_line, j + 1, lenght))
		replace_str(&chang_line, j, j + 1, "/Users/");
	else
	{
		free(chang_line);
		chang_line = NULL;
	}
	while (chang_line && chang_line[j] && !is_delimetr(chang_line[j]))
		++j;
	*i = j;
	return (chang_line);
}

static char	*tilde(char *line, int *i, char **env)
{
	char	*chang_line;
	int		j;

	j = *i;
	env = NULL;
	chang_line = line;
	if (!chang_line[j + 1] ||
	is_delimetr(chang_line[j + 1]) || chang_line[j + 1] == '/')
	{
		if (getenv("HOME"))
			replace_str(&chang_line, j, j + 1, getenv("HOME"));
		j += getenv("HOME") ? ft_strlen(getenv("HOME")) : 1;
		while (chang_line[j] && !is_delimetr(chang_line[j]))
			++j;
	}
	else
		chang_line = assist_tilde(chang_line, &j);
	*i = j;
	return (chang_line);
}

char		*replace_dir(char *line, char **env)
{
	int		i;
	char	*chang_line;
	char	temp;

	i = 0;
	chang_line = line;
	while (chang_line && chang_line[i])
	{
		if (chang_line[i] == '\'' || chang_line[i] == '\"')
		{
			temp = chang_line[i++];
			while (chang_line[i] && chang_line[i] != temp)
				++i;
		}
		if (chang_line[i] == '~')
			chang_line = tilde(chang_line, &i, env);
		else
			++i;
	}
	return (chang_line);
}
