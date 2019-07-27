/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_preconfig.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:19:30 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 17:40:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	pre_launch_config_case(t_launch *launch, t_process *proc)
{
	if (launch->in_fd < 0)
	{
		printf("21sh: no such file or directory: %s\n", proc->input_path);
		return (0);
	}
	else
		return (1);
}

int			pre_launch_config(t_process *proc, t_launch *launch)
{
	if (proc->heredoc == NULL)
	{
		if (check_access(proc->input_file, launch->job_id))
		{
			launch->in_fd = open(proc->input_path, O_RDONLY);
			update_holder(launch, launch->in_fd);
		}
		else
			return (0);
	}
	else
	{
		launch_heredoc(proc, launch);
		launch->in_fd = open(proc->input_path, O_RDONLY);
		update_holder(launch, launch->in_fd);
		if (proc->input_file)
			if (!check_access(proc->input_file, launch->job_id))
				return (0);
	}
	return (pre_launch_config_case(launch, proc));
}

void		launch_pipe_config(t_process *proc, t_launch *launch, t_job *job)
{
	if (proc->output_path != NULL)
	{
		launch->out_fd = open(proc->output_path, CREATE_ATTR);
		if (launch->out_fd < 0)
			launch->out_fd = 1;
		proc->exec_mode = PIPELINE_EXECUTION;
		launch->status = shell_launch_process(job, proc, launch->in_fd,
				launch->out_fd);
	}
	pipe(launch->fd);
	proc->exec_mode = PIPELINE_EXECUTION;
	launch->status = shell_launch_process(job, proc,
			launch->in_fd, launch->fd[1]);
	close(launch->fd[1]);
	launch->in_fd = launch->fd[0];
	update_holder(launch, launch->in_fd);
}
