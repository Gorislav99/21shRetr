/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:11:01 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:25:09 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_ch(t_history_session *h_session, char key)
{
	char *temp;
	char *temp2;
	char buff[2];

	tputs(g_term->im, 1, putchar_);
	if (key != '\n')
		write(1, &key, 1);
	tputs(g_term->ei, 1, putchar_);
	buff[0] = key;
	buff[1] = '\0';
	if (h_session->line)
	{
		temp = ft_strsub(h_session->line, 0, h_session->left);
		temp2 = ft_strjoin(temp, buff);
		free(temp);
		temp = ft_strjoin(temp2, (h_session->line) + (h_session->left));
		free(h_session->line);
		free(temp2);
		h_session->line = temp;
	}
	else
		h_session->line = ft_strdup(buff);
	(h_session->lenght)++;
	(h_session->left)++;
	h_session->victor->array[h_session->victor->curr_arr]++;
}

void	left_ch(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(g_term->le, 1, putchar_);
		(h_session->left)--;
	}
	else if (h_session->left > 0 &&
	h_session->line[h_session->left - 1] == '\n' && !h_session->fl)
	{
		tputs(g_term->up, 1, putchar_);
		h_session->victor->curr_arr--;
		if (!h_session->victor->curr_arr)
			i -= h_session->lenght_hello;
		while (++i < h_session->victor->array[h_session->victor->curr_arr])
			tputs(g_term->nd, 1, putchar_);
		(h_session->left)--;
	}
}

void	right_ch(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->left < h_session->lenght &&
					h_session->line[h_session->left] != '\n')
	{
		tputs(g_term->nd, 1, putchar_);
		(h_session->left)++;
	}
	else if (h_session->left < h_session->lenght &&
		h_session->line[h_session->left] == '\n' && !h_session->fl)
	{
		tputs(g_term->do_, 1, putchar_);
		h_session->victor->curr_arr++;
		(h_session->left)++;
	}
}
