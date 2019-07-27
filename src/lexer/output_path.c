/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:00:00 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 17:21:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		lenght_outpth(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (!ft_strcmp(arg[i], ">") || !ft_strcmp(arg[i], ">>"))
			lenght++;
		++i;
	}
	return (lenght);
}

void	fill_outputline(char **arg, int i, t_process *new_process)
{
	int j;

	j = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (!ft_strcmp(arg[i], ">"))
		{
			new_process->output_file[j++] = ft_strdup(arg[i + 1]);
			new_process->output_mode = 1;
			if (new_process->output_path)
				free(new_process->output_path);
			new_process->output_path = ft_strdup(arg[i + 1]);
		}
		else if (!ft_strcmp(arg[i], ">>"))
		{
			new_process->output_file[j++] = ft_strdup(arg[i + 1]);
			new_process->output_mode = 2;
			if (new_process->output_path)
				free(new_process->output_path);
			new_process->output_path = ft_strdup(arg[i + 1]);
		}
		++i;
	}
	new_process->output_file[j] = NULL;
}

void	output_path(char **arg, int i, t_process *new_process)
{
	int lenght;

	lenght = lenght_outpth(arg, i);
	if (!lenght)
		return ;
	new_process->output_file = (char**)malloc(sizeof(char*) * (lenght + 1));
	if (new_process->output_file == NULL)
		exit(1);
	fill_outputline(arg, i, new_process);
}
