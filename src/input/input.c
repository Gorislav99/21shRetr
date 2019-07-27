/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:52:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:27:58 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		is_delim(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v')
		return (1);
	return (0);
}

int		input_disp(t_history_session *h_session, int key, int mode, int *temp)
{
	if (key == -1 && key_control_c(h_session))
		return (0);
	if (key == KEY_COPY_LEFT || key == KEY_COPY_RIGHT)
	{
		*temp = 0;
		key_cop(h_session, key);
	}
	else if (!(*temp))
	{
		*temp = !g_dispersion ? 1 : g_dispersion;
		if (key == KEY_CUT && g_dispersion)
			key_cut(h_session, *temp);
		else if (g_dispersion)
			save_buff(h_session);
	}
	if (key == KEY_NL && key_entr(h_session))
		return (0);
	if (mode != MODE_HEREDOC &&
		(key == KEY_UP || key == KEY_DOWN) && !(h_session)->fl)
		key_history(h_session, key);
	else
		(h_session)->number_hist = 0;
	key_func(h_session, key);
	return (1);
}

char	*input(t_history_session **h_session,
									int lenght_hello, int mode)
{
	int		key;
	int		temp;

	temp = 1;
	(*h_session)->lenght_hello = 1 + lenght_hello;
	multiple_promt(*h_session, mode);
	(*h_session)->fl = mode ? 1 : 0;
	set_keypress();
	while (21)
	{
		key = ft_readkey(0);
		if (key == 4 && !(*h_session)->lenght)
		{
			shell_cleaner();
			write(1, "\n", 1);
			exit(0);
		}
		if (!input_disp((*h_session), key, mode, &temp))
			break ;
	}
	(*h_session)->victor->curr_arr = (*h_session)->victor->lenght - 1;
	(*h_session)->left = (*h_session)->lenght;
	(*h_session)->fl = 0;
	reset_keypress();
	return ((*h_session)->lenght == 0 ? NULL : ft_strdup((*h_session)->line));
}
