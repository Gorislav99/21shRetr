/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 12:24:58 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:27:41 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		ft_readkey(t_history_session *h_session)
{
	int				ret;
	unsigned char	b[6];
	int				res;
	int				i;

	ft_memset(b, 0, sizeof(b));
	res = 0;
	i = -1;
	if ((ret = read(0, &b[0], 6)) > 0)
	{
		if (!ft_isprint(b[0]))
		{
			while (++i < ret)
				res += b[i];
			res += (ret > 1 ? 1000 : 0);
		}
		else
		{
			while (++i < ret)
				print_ch(h_session, b[i]);
		}
	}
	return (res);
}

void	key_tabs(t_history_session *h_session)
{
	int i;

	i = 0;
	while (i++ < 4)
		print_ch(h_session, ' ');
}

void	key_func(t_history_session *h_session, int key)
{
	if (key == KEY_BS)
		backspace_ch(h_session);
	else if (key == KEY_LEFT)
		left_ch(h_session);
	else if (key == KEY_RIGHT)
		right_ch(h_session);
	else if (key < 255 && key >= 32)
		print_ch(h_session, key);
	else if (key == KEY_SHIFT_UP || key == KEY_SHIFT_DOWN)
		navigation_line(h_session, key);
	else if (key == KEY_HOME || key == KEY_END)
		key_endhome(h_session, key);
	else if (key == KEY_SHIFT_LEFT || key == KEY_SHIFT_RIGHT)
		navigation_words(h_session, key);
	else if (key == KEY_PASTE && g_buffer)
		key_paste(h_session);
	else if (key == KEY_TAB)
		key_tabs(h_session);
}

int		key_entr(t_history_session *h_session)
{
	if (h_session->line && h_session->line[0] == '\0')
	{
		free(h_session->line);
		h_session->line = NULL;
	}
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(g_term->do_, 1, putchar_);
	}
	write(1, "\n", 1);
	return (1);
}

int		key_control_c(t_history_session *h_session)
{
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(g_term->do_, 1, putchar_);
	}
	if (h_session->line)
		free(h_session->line);
	h_session->line = NULL;
	return (1);
}
