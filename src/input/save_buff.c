/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:03:59 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clean_left_assist(t_history_session *h_session, int temp, int i)
{
	while (i != h_session->left && h_session->line[i] != '\n')
	{
		--i;
		tputs(g_term->le, 1, putchar_);
	}
	if (h_session->line[i] == '\n')
	{
		while (temp > h_session->victor->curr_arr)
		{
			tputs(g_term->up, 1, putchar_);
			i -= h_session->victor->array[--temp];
		}
		i -= !h_session->victor->curr_arr ? h_session->lenght_hello : 0;
		while (++i < h_session->left)
			tputs(g_term->nd, 1, putchar_);
	}
}

void	clean_left(t_history_session *h_session)
{
	int i;
	int tmp;
	int temp;

	i = h_session->left;
	temp = h_session->victor->curr_arr;
	while (g_dispersion < 0)
	{
		if (h_session->line[i] == '\n')
		{
			tmp = !temp ? -h_session->lenght_hello : 0;
			while (tmp++ < h_session->victor->array[temp])
				tputs(g_term->le, 1, putchar_);
			tputs(g_term->do_, 1, putchar_);
			temp++;
		}
		else
		{
			tputs(g_term->dc, 1, putchar_);
			write(1, &(h_session->line[i]), 1);
		}
		++i;
		g_dispersion++;
	}
	clean_left_assist(h_session, temp, i);
}

void	clean_right_assist(t_history_session *h_session, int temp, int i)
{
	int tmp;

	tmp = 0;
	while (i > 0 && h_session->line[i] != '\n')
	{
		--i;
		tputs(g_term->le, 1, putchar_);
	}
	while (!temp && tmp++ < h_session->lenght_hello)
		tputs(g_term->le, 1, putchar_);
	while (temp < h_session->victor->curr_arr)
	{
		tputs(g_term->do_, 1, putchar_);
		i += h_session->victor->array[temp++];
	}
	tmp = 0;
	while (!temp && tmp++ < h_session->lenght_hello)
		tputs(g_term->nd, 1, putchar_);
	while (++i < h_session->left)
		tputs(g_term->nd, 1, putchar_);
}

void	clean_right(t_history_session *h_session)
{
	int i;
	int tmp;
	int temp;

	i = h_session->left;
	temp = h_session->victor->curr_arr;
	while (g_dispersion > 0)
	{
		if (h_session->line[--i] == '\n')
		{
			tputs(g_term->up, 1, putchar_);
			tmp = !(--temp) ? -h_session->lenght_hello : 0;
			while (++tmp < h_session->victor->array[temp])
				tputs(g_term->nd, 1, putchar_);
		}
		else
		{
			tputs(g_term->le, 1, putchar_);
			tputs(g_term->dc, 1, putchar_);
			write(1, &(h_session->line[i]), 1);
			tputs(g_term->le, 1, putchar_);
		}
		g_dispersion--;
	}
	clean_right_assist(h_session, temp, i);
}

void	save_buff(t_history_session *h_session)
{
	free(g_buffer);
	tputs(g_term->im, 1, putchar_);
	if (g_dispersion < 0)
	{
		g_buffer = ft_strsub(h_session->line,
		h_session->left, -1 * g_dispersion);
		clean_left(h_session);
	}
	else
	{
		g_buffer = ft_strsub(h_session->line,
		h_session->left - g_dispersion, g_dispersion);
		clean_right(h_session);
	}
	tputs(g_term->ei, 1, putchar_);
}
