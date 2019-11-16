/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:44:09 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:35 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*free_arg(char **arg)
{
	int i;

	i = 0;
	while (arg && arg[i])
		free(arg[i++]);
	if (arg)
		free(arg);
	return (NULL);
}

void	*free_process(t_process *proc)
{
	int	i;

	i = 0;
	proc->query = free_arg(proc->query);
	proc->heredoc = free_arg(proc->heredoc);
	proc->input_file = free_arg(proc->input_file);
	if (proc->input_path)
		free(proc->input_path);
	if (proc->aggregate)
		free(proc->aggregate);
	proc->output_file = free_arg(proc->output_file);
	if (proc->output_path)
		free(proc->output_path);
	free(proc);
	return (NULL);
}

void	*free_job(t_job *job)
{
	t_process	*temp;

	if (!job)
		return (NULL);
	while (job->root)
	{
		temp = job->root;
		job->root = job->root->next;
		free_process(temp);
	}
	free(job);
	return (NULL);
}
