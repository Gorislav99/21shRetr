/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:33:13 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	jump_up(t_history_session *h_session)
{
	int i;

	i = 0;
	tputs(g_term->up, 1, putchar_);
	if (!(h_session->victor->curr_arr - 1))
	{
		i += h_session->victor->array[h_session->victor->curr_arr - 1] ? 0 : 1;
		while (i++ < h_session->lenght_hello)
			tputs(g_term->nd, 1, putchar_);
	}
	h_session->victor->curr_arr--;
	h_session->left--;
	g_dispersion--;
	i = 0;
	while (++i < h_session->victor->array[h_session->victor->curr_arr])
		tputs(g_term->nd, 1, putchar_);
}

static void	key_copy_left(t_history_session *h_session)
{
	if (h_session->line[h_session->left - 1] == '\n' && !h_session->fl)
		jump_up(h_session);
	if (!(h_session->left) || h_session->line[h_session->left - 1] == '\n')
		return ;
	tputs(g_term->im, 1, putchar_);
	tputs(g_term->le, 1, putchar_);
	tputs(g_term->dc, 1, putchar_);
	if (g_dispersion <= 0)
		write(1, "\e[45m", ft_strlen("\e[45m"));
	write(1, &(h_session->line[h_session->left - 1]), 1);
	if (g_dispersion <= 0)
		write(1, "\e[0m", ft_strlen("\e[0m"));
	tputs(g_term->le, 1, putchar_);
	h_session->left--;
	g_dispersion--;
	tputs(g_term->ei, 1, putchar_);
}

static void	key_copy_right(t_history_session *h_session)
{
	int i;

	i = 0;
	if (h_session->line[h_session->left] == '\n' && !h_session->fl)
	{
		tputs(g_term->do_, 1, putchar_);
		h_session->victor->curr_arr++;
		h_session->left++;
		g_dispersion++;
	}
	if (h_session->left == h_session->lenght ||
					h_session->line[h_session->left] == '\n')
		return ;
	tputs(g_term->dc, 1, putchar_);
	tputs(g_term->im, 1, putchar_);
	if (g_dispersion >= 0)
		write(1, "\e[45m", ft_strlen("\e[45m"));
	write(1, &(h_session->line[h_session->left]), 1);
	if (g_dispersion >= 0)
		write(1, "\e[0m", ft_strlen("\e[0m"));
	h_session->left++;
	g_dispersion++;
	tputs(g_term->ei, 1, putchar_);
}

void		key_cop(t_history_session *h_session, int key)
{
	if (key == KEY_COPY_LEFT && h_session->lenght && h_session->left)
		key_copy_left(h_session);
	else if (key == KEY_COPY_RIGHT &&
	h_session->lenght && h_session->left < h_session->lenght)
		key_copy_right(h_session);
}
