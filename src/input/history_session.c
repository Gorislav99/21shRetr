/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_session.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:17:28 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:20:19 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void			clear_line(t_history_session *h_session)
{
	int i;
	int j;

	i = 0;
	if (h_session->victor->lenght > 1)
	{
		j = h_session->victor->lenght;
		while (++h_session->victor->curr_arr < h_session->victor->lenght)
			tputs(g_term->do_, 1, putchar_);
		h_session->victor->curr_arr--;
		while (--j > 0 && !(i = 0))
		{
			while (i++ < h_session->victor->array[j])
				tputs(g_term->le, 1, putchar_);
			tputs(g_term->cd, 1, putchar_);
			tputs(g_term->up, 1, putchar_);
		}
		while (++j < h_session->lenght_hello)
			tputs(g_term->nd, 1, putchar_);
		tputs(g_term->cd, 1, putchar_);
		return ;
	}
	while (i++ < h_session->left)
		tputs(g_term->le, 1, putchar_);
	tputs(g_term->cd, 1, putchar_);
}

static void			key_upp(t_history_session *h_session)
{
	int					i;
	t_history_session	*temp;

	i = 0;
	temp = h_session;
	while (temp && i++ <= h_session->number_hist)
		temp = temp->up;
	if (!temp || !(temp->line))
		return ;
	clear_line(h_session);
	(h_session->number_hist)++;
	free(h_session->line);
	h_session->line = ft_strdup(temp->line);
	h_session->left = temp->left;
	h_session->lenght = temp->lenght;
	h_session->victor->del(&(h_session->victor));
	h_session->victor = temp->victor->copy(temp->victor);
	ft_printf("%s", h_session->line);
}

static void			key_dow(t_history_session *h_session)
{
	int					i;
	t_history_session	*temp;

	i = 0;
	temp = h_session;
	while (temp && ++i < h_session->number_hist)
		temp = temp->up;
	if (!temp || !(temp->line))
		return ;
	clear_line(h_session);
	(h_session->number_hist)--;
	free(h_session->line);
	h_session->line = ft_strdup(temp->line);
	h_session->left = temp->left;
	h_session->lenght = temp->lenght;
	h_session->victor->del(&(h_session->victor));
	h_session->victor = temp->victor->copy(temp->victor);
	ft_printf("%s", h_session->line);
}

void				key_history(t_history_session *h_session, int key)
{
	if (key == KEY_UP)
		key_upp(h_session);
	else if (key == KEY_DOWN && h_session->number_hist > 1)
		key_dow(h_session);
}
