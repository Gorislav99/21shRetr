/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:53:07 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 19:12:28 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			help_shell(t_process *proc)
{
	int		i;

	proc = NULL;
	ft_printf("21shell of 21's school project\n");
	ft_printf("Built-in commands (input argument if needed):\n");
	i = 0;
	while (i < NR_BUILTINS)
	{
		ft_printf("\t -> %s\n", g_sh->builtins->builtin_str[i]);
		i++;
	}
	ft_printf("For additional info -> use \"man\".\n");
	return (1);
}

int			exit_shell(t_process *proc)
{
	int		i;

	i = 0;
	proc = NULL;
	printf(COLOR_MAGENTA "say-o-nara~\n" COLOR_NONE);
	shell_cleaner();
	exit(1);
}

int			echo(t_process *proc)
{
	int		i;

	i = 1;
	string_var_parser(proc->query);
	while (proc->query[i] != 0)
	{
		ft_printf("%s ", proc->query[i]);
		i++;
	}
	ft_printf("\n");
	return (1);
}

void		shell_cleaner(void)
{
	int		i;

	i = 0;
	if (g_sh->jobs[i])
	{
		while (g_sh->jobs[i])
			free_job(g_sh->jobs[i++]);
	}
	free_arg(g_sh->env);
}
