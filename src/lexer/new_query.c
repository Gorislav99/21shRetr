/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:49:40 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:35 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_mode(char *command)
{
	if (strcmp(command, "|") == 0)
		return (COMMAND_PIPE);
	else if (strcmp(command, "<") == 0)
		return (COMMAND_LREDIR);
	else if (strcmp(command, ">") == 0)
		return (COMMAND_RREDIR);
	else if (strcmp(command, "<<") == 0)
		return (COMMAND_HEREDOC);
	else if (strcmp(command, ">>") == 0)
		return (COMMAND_APPEND);
	else if (strcmp(command, "&") == 0)
		return (COMMAND_BACKGR);
	else
		return (COMMAND_EXTERNAL);
}

int		lenght_argproc(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (get_mode(arg[i]))
			++i;
		else if (!is_agrarg((arg[i])))
			++lenght;
		arg[i] ? ++i : 0;
	}
	return (lenght);
}

char	**new_query(char **arg, int i)
{
	char	**query;
	int		lenght;
	int		j;

	j = 0;
	if ((lenght = lenght_argproc(arg, i)) == 0)
		return (NULL);
	if ((query = malloc(sizeof(char*) * (lenght + 1))) == NULL)
		exit(1);
	while (j < lenght)
	{
		if (get_mode(arg[i]))
			i += 1;
		else if (!is_agrarg(arg[i]))
		{
			query[j] = ft_strdup(arg[i]);
			++j;
		}
		if (!arg[i++])
			break ;
	}
	query[j] = NULL;
	return (query);
}
