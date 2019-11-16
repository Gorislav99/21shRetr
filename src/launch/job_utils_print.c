/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:22:56 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:36:31 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				is_job_completed(int id)
{
	t_process	*proc;

	if (id > NR_JOBS || g_sh->jobs[id] == NULL)
		return (0);
	proc = g_sh->jobs[id]->root;
	while (proc != NULL)
	{
		if (proc->status != STATUS_DONE)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int				print_processes_of_job(int id)
{
	t_process	*proc;

	if (id > NR_JOBS || g_sh->jobs[id] == NULL)
		return (-1);
	ft_printf("[%d]", id);
	proc = g_sh->jobs[id]->root;
	while (proc != NULL)
	{
		ft_printf(" %d", proc->pid);
		proc = proc->next;
	}
	ft_printf("\n");
	return (0);
}

static char		*get_state_string(t_process *proc)
{
	char		*state;

	if (proc->status == 0)
		state = ft_strdup("running");
	else if (proc->status == 1)
		state = ft_strdup("done");
	else if (proc->status == 2)
		state = ft_strdup("suspended");
	else if (proc->status == 1)
		state = ft_strdup("continued");
	else
		state = ft_strdup("terminated");
	return (state);
}

int				print_job_status(int id)
{
	t_process	*proc;
	char		*state;

	if (id > NR_JOBS || g_sh->jobs[id] == NULL)
		return (-1);
	ft_printf("[%d]", id);
	proc = g_sh->jobs[id]->root;
	while (proc != NULL)
	{
		state = get_state_string(proc);
		ft_printf("\t%d\t%s\t%s", proc->pid, state, proc->query[0]);
		if (proc->next != NULL)
			ft_printf("|\n");
		else
			ft_printf("\n");
		proc = proc->next;
		ft_memdel((void **)&state);
	}
	return (0);
}

int				insert_job(t_job *job)
{
	int			id;

	id = get_next_job_id();
	if (id < 0)
		return (-1);
	job->id = id;
	g_sh->jobs[id] = job;
	return (id);
}
