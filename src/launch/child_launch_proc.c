/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_launch_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:53:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:36:31 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void		signal_default_changer(t_process *proc, t_job *job)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	proc->pid = getpid();
	if (job->pgid > 0)
		setpgid(0, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(0, job->pgid);
	}
}

void		pgid_and_dup_handle(t_process *proc, t_job *job,
		int in_fd, int out_fd)
{
	signal_default_changer(proc, job);
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (proc->aggregate)
	{
		if (proc->aggregate->out == -1)
			close(proc->aggregate->in);
		else
		{
			if (proc->next != NULL)
				dup2(proc->aggregate->out, proc->aggregate->in);
		}
	}
}

void		child_launch_cycle(t_process *proc)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	if (execve(proc->query[0], proc->query, g_sh->env) == -1)
	{
		paths = ft_strsplit(get_env("PATH", g_sh->env), ':');
		while (paths && paths[i] != NULL)
		{
			path = ft_strjoiner(paths[i++], proc->query[0]);
			if (DEBUG_LOG)
				ft_printf("----> starting path: %s\n", path);
			if (execve(path, proc->query, g_sh->env) != -1)
			{
				free_arg(paths);
				exit(0);
			}
			free(path);
		}
		free_arg(paths);
	}
}

void		child_launch_proc(t_job *job, t_process *proc,
		int in_fd, int out_fd)
{
	pgid_and_dup_handle(proc, job, in_fd, out_fd);
	child_launch_cycle(proc);
	ft_printf("21sh: %s: command not found\n", proc->query[0]);
	exit(1);
}
