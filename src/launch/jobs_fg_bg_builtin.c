/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fg_bg_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:07:38 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/26 15:32:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		shell_fg_ext(pid_t pid, int job_id)
{
	if (kill(-pid, SIGCONT) < 0)
	{
		ft_printf("21sh: fg %d: job not found\n", pid);
		return (-1);
	}
	tcsetpgrp(0, pid);
	if (job_id > 0)
	{
		set_job_status(job_id, STATUS_CONTINUED);
		print_job_status(job_id);
		if (wait_for_job(job_id) >= 0)
			remove_job(job_id);
	}
	else
		wait_for_pid(pid);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
	return (0);
}

int				shell_fg(t_process *proc)
{
	pid_t		pid;
	int			job_id;

	job_id = -1;
	if (proc->query[1] == NULL)
	{
		ft_printf("usage: fg <pid>\n");
		return (-1);
	}
	if (proc->query[1][0] == '%')
	{
		job_id = ft_atoi(proc->query[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			ft_printf("21sh: fg %s: no such job\n", proc->query[1]);
			return (-1);
		}
	}
	else
		pid = ft_atoi(proc->query[1]);
	return (shell_fg_ext(pid, job_id));
}

static int		shell_bg_ext(pid_t pid, int job_id)
{
	if (kill(-pid, SIGCONT) < 0)
	{
		ft_printf("21sh: bg %d: job not found\n", pid);
		return (-1);
	}
	if (job_id > 0)
	{
		set_job_status(job_id, STATUS_CONTINUED);
		print_job_status(job_id);
	}
	return (0);
}

int				shell_bg(t_process *proc)
{
	pid_t		pid;
	int			job_id;

	job_id = -1;
	if (proc->query[1] == NULL)
	{
		ft_printf("usage: bg <pid>\n");
		return (-1);
	}
	if (proc->query[1][0] == '%')
	{
		job_id = ft_atoi(proc->query[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			ft_printf("21sh: bg %s: no such job\n", proc->query[1]);
			return (-1);
		}
	}
	else
		pid = ft_atoi(proc->query[1]);
	return (shell_bg_ext(pid, job_id));
}
