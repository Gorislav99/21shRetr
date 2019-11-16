/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:09:23 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:36:31 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				launch_proc_cycle(t_process *proc, t_launch *launch, t_job *job)
{
	while (proc != NULL)
	{
		if (proc == job->root &&
		(proc->input_path != NULL || proc->heredoc != NULL))
			if (!pre_launch_config(proc, launch))
				return (0);
		if (proc->next != NULL)
			launch_pipe_config(proc, launch, job);
		else
		{
			if (!launch_base_config(launch, proc, job))
				return (0);
		}
		proc = proc->next;
	}
	return (launch->status);
}

int				shell_launch_job(t_job *job)
{
	t_process	*proc;

	if (g_sh->launch)
		free(g_sh->launch);
	g_sh->launch = h_launch_init();
	check_zombie();
	if (job->root->type == COMMAND_EXTERNAL || job->root->type != COMMAND_EXTERNAL)
		g_sh->launch->job_id = insert_job(job);
	proc = job->root;
	g_sh->launch->status = launch_proc_cycle(proc, g_sh->launch, job);
	if (job->root->type == COMMAND_EXTERNAL  || job->root->type != COMMAND_EXTERNAL)
	{
		if (g_sh->launch->status >= 0 && job->mode == FOREGROUND_EXECUTION)
			remove_job(g_sh->launch->job_id);
		else if (job->mode == BACKGROUND_EXECUTION)
			print_processes_of_job(g_sh->launch->job_id);
	}
	if (DEBUG_LOG)
		print_holder(g_sh->launch);
	clean_holder(g_sh->launch);
	return (g_sh->launch->status);
}

void			parent_launch_process(t_process *proc,
		t_job *job, pid_t childpid)
{
	proc->pid = childpid;
	if (job->pgid > 0)
		setpgid(childpid, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(childpid, job->pgid);
	}
}
static char	*get_full_path(char *temp, int i, int k, char *arg)
{
    char	*path;
    char	*full_path;

    path = ft_strsub(temp, i, k - i);
    full_path = ft_strnew(ft_strlen(path)
                          + ft_strlen(arg) + 1);
    full_path = ft_strcpy(full_path, path);
    ft_strcpy(full_path + ft_strlen(path), "/");
    ft_strcpy(full_path + ft_strlen(path) + 1, arg);
    free(path);
    return (full_path);
}

static char	*brute_force_exec(char *query)
{
    char	*temp;
    char	*full_path;
    int		i;
    int		k;

    i = 0;
    if (access(query, 1) != -1)
        return (ft_strdup(query));
    if ((temp = get_env("PATH", g_sh->env)) == NULL)
        return (NULL);
    while (temp[i])
    {
        k = i;
        while (temp[k] != ':' && temp[k])
            ++k;
        full_path = get_full_path(temp, i, k, query);
        if (access(full_path, 1) != -1)
            return (full_path);
        free(full_path);
        i = temp[k] != '\0' ? k + 1 : k;
    }
    return (NULL);
}

int				fork_after_check_exist(t_process *proc)
{
    char *temp;

    if (!(temp = brute_force_exec(proc->query[0])))
    {
        print_error("zsh: command not found: ", proc->query[0]);
        g_sh->signal = 1;
        return (1);
    }
    free(temp);
    return (0);
}

int				shell_launch_process(t_job *job, t_process *proc,
		int in_fd, int out_fd)
{
	pid_t		childpid;
	int			status;

	proc->status = STATUS_RUNNING;
	if (proc->type != COMMAND_EXTERNAL && execute_builtin_command(proc, out_fd))
		return (0);
	status = 0;
    if (fork_after_check_exist(proc))
		return (1);
	childpid = fork();
	if (childpid < 0)
		return (-1);
	else if (childpid == 0)
		child_launch_proc(job, proc, in_fd, out_fd);
	else
	{
		parent_launch_process(proc, job, childpid);
		if (proc->exec_mode == FOREGROUND_EXECUTION)
		{
			tcsetpgrp(0, job->pgid);
			status = wait_for_job(job->id);
			signal(SIGTTOU, SIG_IGN);
			tcsetpgrp(0, getpid());
			signal(SIGTTOU, SIG_DFL);
		}
	}
	return (status);
}
