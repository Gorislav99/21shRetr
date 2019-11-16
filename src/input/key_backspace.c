/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_backspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:53:12 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:20:39 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	cut_line(t_history_session *h_session)
{
	int temp;
	int	temp2;
	int	i;

	i = 0;
	temp = h_session->victor->curr_arr;
	temp2 = h_session->victor->curr_arr;
	while (++temp < h_session->victor->lenght)
	{
		tputs(g_term->do_, 1, putchar_);
		tputs(g_term->cd, 1, putchar_);
	}
	(h_session->victor->lenght - 1) == h_session->victor->curr_arr ? temp-- : 0;
	while (temp-- > temp2)
		tputs(g_term->up, 1, putchar_);
	ft_printf("%s", &h_session->line[h_session->left]);
	temp = h_session->victor->array[h_session->victor->lenght - 1];
	while (temp--)
		tputs(g_term->le, 1, putchar_);
	while (++temp2 < (h_session->victor->lenght - 1))
		tputs(g_term->up, 1, putchar_);
}

static void	clean_down(t_history_session *h_session)
{
	int temp;
	int	temp2;
	int i;

	i = 0;
	temp = h_session->victor->curr_arr;
	temp2 = h_session->victor->curr_arr;
	while (temp++ < h_session->victor->lenght)
	{
		tputs(g_term->cd, 1, putchar_);
		tputs(g_term->do_, 1, putchar_);
	}
	while (--temp > temp2)
		tputs(g_term->up, 1, putchar_);
	i = 0;
	tputs(g_term->up, 1, putchar_);
	if (!(h_session->victor->curr_arr - 1))
		i -= h_session->lenght_hello;
	while (++i < h_session->victor->array[h_session->victor->curr_arr - 1])
		tputs(g_term->nd, 1, putchar_);
}

static void	add_line(t_history_session *h_session)
{
	int i;

	clean_down(h_session);
	ft_printf("%s", &h_session->line[h_session->left]);
	i = h_session->victor->array[h_session->victor->lenght - 1];
	if ((h_session->victor->lenght - 1) == h_session->victor->curr_arr)
		i += h_session->victor->array[h_session->victor->curr_arr - 1];
	while (i-- > 0)
		tputs(g_term->le, 1, putchar_);
	i = h_session->victor->lenght - h_session->victor->curr_arr;
	while (--i > 0)
		tputs(g_term->up, 1, putchar_);
	i = h_session->victor->array[h_session->victor->curr_arr - 1];
	if (!(h_session->victor->curr_arr - 1))
		i += h_session->lenght_hello;
	while (--i > 0)
		tputs(g_term->nd, 1, putchar_);
	h_session->victor->array[h_session->victor->curr_arr - 1] +=
	h_session->victor->array[h_session->victor->curr_arr];
	h_session->victor->pop(&h_session->victor, h_session->victor->curr_arr);
}

static void	bjump_up(t_history_session *h_session)
{
	int i;

	i = 0;
	h_session->victor->array[h_session->victor->curr_arr]--;
	if (!h_session->victor->array[h_session->victor->curr_arr])
	{
		cut_line(h_session);
		h_session->victor->pop(&h_session->victor, h_session->victor->curr_arr);
		tputs(g_term->up, 1, putchar_);
		if (!h_session->victor->curr_arr)
			i -= h_session->lenght_hello;
		while (++i < h_session->victor->array[h_session->victor->curr_arr])
			tputs(g_term->nd, 1, putchar_);
	}
	else
		add_line(h_session);
}

void		backspace_ch(t_history_session *h_session)
{
	char	*temp;
	char	*temp2;

	if (!(h_session->lenght > 0 && h_session->left > 0))
		return ;
	if (h_session->line[h_session->left - 1] == '\n' &&
			(!h_session->victor->curr_arr || h_session->fl))
		return ;
	else if (h_session->line[h_session->left - 1] == '\n')
		bjump_up(h_session);
	else
	{
		tputs(g_term->le, 1, putchar_);
		tputs(g_term->dc, 1, putchar_);
		h_session->victor->array[h_session->victor->curr_arr]--;
	}
	temp = ft_strsub(h_session->line, 0, h_session->left - 1);
	temp2 = ft_strjoin(temp, (h_session->line) + (h_session->left));
	free(temp);
	free(h_session->line);
	h_session->line = temp2;
	--(h_session->lenght);
	--(h_session->left);
}
