/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_endhome.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:30:34 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	key_hom(t_history_session *h_session)
{
	int i;

	i = 0;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		h_session->left--;
		tputs(g_term->le, 1, putchar_);
	}
	if (h_session->fl || h_session->left == 0)
		return ;
	while (h_session->victor->curr_arr > 0)
	{
		h_session->victor->curr_arr--;
		tputs(g_term->up, 1, putchar_);
	}
	while (++i < h_session->lenght_hello)
		tputs(g_term->nd, 1, putchar_);
	h_session->left = 0;
}

void	assist_en(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->left == 0 && h_session->victor->lenght > 1)
		while (++i < h_session->lenght_hello)
			tputs(g_term->le, 1, putchar_);
	else if (h_session->victor->lenght == 1)
		tputs(g_term->nd, 1, putchar_);
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(g_term->do_, 1, putchar_);
	}
	i = 0;
	while (++i < h_session->victor->array[h_session->victor->curr_arr])
		tputs(g_term->nd, 1, putchar_);
	h_session->left = h_session->lenght;
}

void	key_en(t_history_session *h_session)
{
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		h_session->left--;
		tputs(g_term->le, 1, putchar_);
	}
	if (h_session->fl)
	{
		while (h_session->left < h_session->lenght)
		{
			h_session->left++;
			tputs(g_term->nd, 1, putchar_);
		}
	}
	else
		assist_en(h_session);
}

void	key_endhome(t_history_session *h_session, int key)
{
	if (key == KEY_HOME && h_session->left > 0)
		key_hom(h_session);
	else if (key == KEY_END && h_session->left < h_session->lenght)
		key_en(h_session);
}
