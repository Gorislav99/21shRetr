/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:48:19 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 17:38:13 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	launch_out_cases(t_process *proc, t_launch *launch, int i)
{
	if (proc->output_mode == 2)
	{
		if (access(proc->output_file[i], F_OK) == -1)
			launch->out_fd = open(proc->output_file[i], CREATE_ATTR);
		else
			launch->out_fd = open(proc->output_file[i], APPEND_ATTR);
	}
	else
		launch->out_fd = open(proc->output_file[i], CREATE_ATTR);
	update_holder(launch, launch->out_fd);
}

int			launch_out_redir(t_process *proc, t_launch *launch)
{
	int		i;

	i = 0;
	if (proc->output_file)
	{
		while (proc->output_file[i])
		{
			launch_out_cases(proc, launch, i);
			if (launch->out_fd == -1)
			{
				ft_printf("21sh: %s: Permission denied:\n",
						proc->output_file[i]);
				return (0);
			}
			++i;
			if (proc->output_file[i])
				close(launch->out_fd);
		}
	}
	return (1);
}

int			launch_base_config(t_launch *launch, t_process *proc, t_job *job)
{
	launch->out_fd = 1;
	if (proc->output_path != NULL)
	{
		if (!launch_out_redir(proc, launch))
			return (0);
	}
	proc->exec_mode = job->mode;
	launch->status = shell_launch_process(job, proc, launch->in_fd,
			launch->out_fd);
	return (1);
}
