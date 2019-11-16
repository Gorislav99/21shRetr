/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:33:31 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	key_shift_up(t_history_session *h_session)
{
	int i;

	i = h_session->left;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(g_term->le, 1, putchar_);
		--h_session->left;
	}
	h_session->victor->curr_arr--;
	tputs(g_term->up, 1, putchar_);
	i = i - h_session->left;
	if (i > (h_session->victor->array[h_session->victor->curr_arr] - 1))
		i = h_session->victor->array[h_session->victor->curr_arr] - 1;
	h_session->left = h_session->left -
	(h_session->victor->array[h_session->victor->curr_arr] - i);
	if (!h_session->victor->curr_arr)
		h_session->left--;
	if (!h_session->victor->curr_arr)
		i += (h_session->lenght_hello);
	else
		++i;
	while (--i > 0)
		tputs(g_term->nd, 1, putchar_);
}

static void	miss_hello(t_history_session *h_session, int i)
{
	int j;

	j = 0;
	i = 0;
	h_session->left++;
	while (++j < h_session->lenght_hello)
		tputs(g_term->le, 1, putchar_);
}

static void	key_shift_down(t_history_session *h_session)
{
	int i;

	i = h_session->left;
	while (h_session->left > 0 && h_session->line[h_session->left - 1] != '\n')
	{
		tputs(g_term->le, 1, putchar_);
		--h_session->left;
	}
	if (!h_session->victor->curr_arr)
		miss_hello(h_session, ++i);
	tputs(g_term->do_, 1, putchar_);
	i = i - h_session->left;
	h_session->left += h_session->victor->array[h_session->victor->curr_arr];
	h_session->victor->curr_arr++;
	if (i > (h_session->victor->array[h_session->victor->curr_arr] - 1))
		i = h_session->victor->array[h_session->victor->curr_arr];
	else
		++i;
	while (--i > 0)
	{
		h_session->left++;
		tputs(g_term->nd, 1, putchar_);
	}
}

void		navigation_line(t_history_session *h_session, int key)
{
	if (h_session->victor->lenght == 1 || h_session->fl)
		return ;
	if (key == KEY_SHIFT_UP && h_session->victor->curr_arr > 0)
		key_shift_up(h_session);
	else if (key == KEY_SHIFT_DOWN &&
	h_session->victor->curr_arr < (h_session->victor->lenght - 1))
		key_shift_down(h_session);
}
