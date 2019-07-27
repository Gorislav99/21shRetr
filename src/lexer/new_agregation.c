/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_agregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:57:55 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		is_agrarg(char *line)
{
	if (ft_strlen(line) == 4)
	{
		if (line[0] >= '0' && line[0] <= '2')
		{
			if (line[1] == '>' && line[2] == '&')
			{
				if ((line[3] >= '0' && line[3] <= '2') || line[3] == '-')
					return (1);
			}
		}
	}
	return (0);
}

int		lenght_agrg(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (is_agrarg(arg[i]))
			++lenght;
		++i;
	}
	return (lenght);
}

void	new_agregation(char **arg, int i, t_process *new_process)
{
	int lenght;

	lenght = lenght_agrg(arg, i);
	if (lenght == 0)
		return ;
	new_process->aggregate = (t_aggregation*)malloc(sizeof(t_aggregation));
	if (new_process->aggregate == NULL)
		exit(1);
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (is_agrarg(arg[i]))
		{
			new_process->aggregate->in = arg[i][0] - 48;
			if (arg[i][3] == '-')
				new_process->aggregate->out = -1;
			else
				new_process->aggregate->out = arg[i][3] - 48;
		}
		++i;
	}
}
