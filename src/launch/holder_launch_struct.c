/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holder_launch_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:44:23 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 19:19:18 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				check_access(char **files, int id)
{
	int			i;

	id = 0;
	i = 0;
	while (files[i])
	{
		if (access(files[i], F_OK) == -1)
		{
			ft_printf("21sh: %s: No such file or directory\n", files[i]);
			return (0);
		}
		++i;
	}
	return (1);
}

void			update_holder(t_launch *launch, int fd)
{
	int			i;

	i = 0;
	if (fd >= 3)
	{
		while (launch->holder[i] != 0)
		{
			if (launch->holder[i] == fd)
				return ;
			++i;
		}
		launch->holder[i] = fd;
	}
}

void			print_holder(t_launch *launch)
{
	int			i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		ft_printf("%d --- fd in use: %d\n", i, launch->holder[i]);
		++i;
	}
}

void			clean_holder(t_launch *launch)
{
	int			i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		close(launch->holder[i]);
		i++;
	}
}

t_launch		*h_launch_init(void)
{
	t_launch	*launch;

	launch = (t_launch *)malloc(sizeof(t_launch));
	launch->status = 0;
	launch->in_fd = 0;
	launch->out_fd = 1;
	launch->job_id = -1;
	launch->holder[0] = 0;
	ft_bzero(launch->holder, 48);
	return (launch);
}
