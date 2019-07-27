/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:20:49 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:36:31 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				release_job(int id)
{
	t_process	*proc;
	t_process	*tmp;
	t_job		*job_free;

	if (id > NR_JOBS || g_sh->jobs[id] == NULL)
		return (-1);
	job_free = g_sh->jobs[id];
	proc = job_free->root;
	while (proc != NULL)
	{
		tmp = proc->next;
		free(proc->input_path);
		free(proc->output_path);
		free(proc);
		proc = tmp;
	}
	free(job_free);
	return (0);
}

int				remove_job(int id)
{
	if (id > NR_JOBS || g_sh->jobs[id] == NULL)
		return (-1);
	if (g_sh->jobs[id] && g_sh->jobs[id]->root)
		g_sh->jobs[id] = free_job(g_sh->jobs[id]);
	return (0);
}

int				get_job_id_by_pid(int pid)
{
	int			i;
	t_process	*proc;

	i = 0;
	while (++i <= NR_JOBS)
	{
		if (g_sh->jobs[i] != NULL)
		{
			proc = g_sh->jobs[i]->root;
			while (proc != NULL)
			{
				if (proc->pid == pid)
					return (i);
				proc = proc->next;
			}
		}
	}
	return (-1);
}

int				get_next_job_id(void)
{
	int			i;

	i = 0;
	while (++i <= NR_JOBS)
		if (g_sh->jobs[i] == NULL)
			return (i);
	return (-1);
}
