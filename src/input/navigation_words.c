/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 18:32:47 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	line_up(t_history_session *h_session)
{
	int i;

	i = 0;
	tputs(g_term->up, 1, putchar_);
	h_session->victor->curr_arr--;
	if (!h_session->victor->curr_arr)
	{
		while (i++ < h_session->lenght_hello)
			tputs(g_term->nd, 1, putchar_);
		i = 0;
	}
	while (i++ < h_session->victor->array[h_session->victor->curr_arr])
		tputs(g_term->nd, 1, putchar_);
}

void	key_shift_left(t_history_session *h_session)
{
	int i;

	i = h_session->left - 1;
	if (h_session->line[i] == 32 ||
	(h_session->line[i] > 8 && h_session->line[i] < 14))
	{
		while (i >= 0 && is_delim(h_session->line[i]))
		{
			if (h_session->line[i] == '\n' && h_session->fl)
				break ;
			else if (h_session->line[i] == '\n')
				line_up(h_session);
			tputs(g_term->le, 1, putchar_);
			h_session->left--;
			i--;
		}
		return ;
	}
	while (i >= 0 && h_session->line[i] && !is_delim(h_session->line[i]))
	{
		tputs(g_term->le, 1, putchar_);
		h_session->left--;
		i--;
	}
}

void	line_down(t_history_session *h_session)
{
	int i;

	i = h_session->left - 1;
	while (i >= 0 && h_session->line[i] != '\n')
	{
		--i;
		tputs(g_term->le, 1, putchar_);
	}
	if (!h_session->victor->curr_arr)
	{
		i = 0;
		while (++i < h_session->lenght_hello)
			tputs(g_term->le, 1, putchar_);
	}
	tputs(g_term->do_, 1, putchar_);
	h_session->victor->curr_arr++;
}

void	key_shift_right(t_history_session *h_session)
{
	int i;

	i = h_session->left ? h_session->left : 0;
	if (h_session->line[i] == 32 ||
	(h_session->line[i] > 8 && h_session->line[i] < 14))
	{
		while (i < h_session->lenght && is_delim(h_session->line[i]))
		{
			if (h_session->line[i] == '\n' && h_session->fl)
				break ;
			else if (h_session->line[i] == '\n')
				line_down(h_session);
			else
				tputs(g_term->nd, 1, putchar_);
			h_session->left++;
			i++;
		}
		return ;
	}
	while (h_session->line[i] && !is_delim(h_session->line[i]))
	{
		tputs(g_term->nd, 1, putchar_);
		h_session->left++;
		i++;
	}
}

void	navigation_words(t_history_session *h_session, int key)
{
	if (h_session->lenght == 0)
		return ;
	if (key == KEY_SHIFT_LEFT && (h_session->left - 1) > 0)
		key_shift_left(h_session);
	else if (key == KEY_SHIFT_RIGHT && (h_session->left) < h_session->lenght)
		key_shift_right(h_session);
}
