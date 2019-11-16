/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:14:11 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int					putchar_(int c)
{
	write(1, &c, 1);
	return (0);
}

void				cut_str(char **comm, int i, int lenght)
{
	char *temp;
	char *temp2;

	if (!comm || !(*comm))
		return ;
	temp = ft_strsub(*comm, 0, i);
	temp2 = ft_strsub(*comm, lenght, ft_strlen(*comm));
	free(*comm);
	*comm = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
}

void				write_vector(t_history_session *h_session)
{
	int i;
	int j;

	h_session->victor->del(&(h_session->victor));
	h_session->victor = init_vector();
	i = 0;
	j = 0;
	h_session->lenght = 0;
	while (h_session->line[i])
	{
		if (h_session->line[i] == '\n')
		{
			h_session->victor->push_back(&(h_session->victor), j);
			j = 0;
		}
		i++;
		++j;
		h_session->lenght++;
	}
	h_session->victor->push_back(&(h_session->victor), j);
}

static void			init_verb(t_history_session *h_session, int lenght_hello)
{
	h_session->left = 0;
	h_session->lenght = 0;
	h_session->line = NULL;
	h_session->down = NULL;
	h_session->victor = init_vector();
	h_session->victor->push_back(&h_session->victor, 0);
	h_session->number_hist = 0;
	h_session->fl = 0;
	h_session->lenght_hello = 1 + lenght_hello;
}

t_history_session	*add_history(t_history_session *h_session, int lenght_hello)
{
	t_history_session *temp;

	if (!h_session)
	{
		if ((h_session =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		h_session->up = NULL;
		h_session->number_hist = 0;
		g_buffer = NULL;
		g_dispersion = 0;
	}
	else if (h_session->line)
	{
		if ((h_session->down =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		temp = h_session;
		h_session = h_session->down;
		h_session->up = temp;
	}
	else if (!h_session->line)
		h_session->victor->del(&h_session->victor);
	init_verb(h_session, lenght_hello);
	return (h_session);
}
