/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:33:35 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ins_line(t_history_session *h_session)
{
	char	*temp_str;
	char	*temp_str2;

	if (!h_session->line)
	{
		h_session->line = ft_strdup(g_buffer);
		h_session->lenght = ft_strlen(g_buffer);
		h_session->victor->array[0] = h_session->lenght;
	}
	else
	{
		temp_str = ft_strjoin(g_buffer, &(h_session->line[h_session->left]));
		cut_str(&(h_session->line), h_session->left, h_session->lenght);
		temp_str2 = h_session->line;
		h_session->line = ft_strjoin(h_session->line, temp_str);
		free(temp_str2);
		free(temp_str);
		write_vector(h_session);
	}
}

void		key_paste(t_history_session *h_session)
{
	int		temp;
	int		i;

	ins_line(h_session);
	tputs(g_term->im, 1, putchar_);
	tputs(g_term->cd, 1, putchar_);
	ft_printf("%s", &(h_session->line[h_session->left]));
	h_session->left += ft_strlen(g_buffer);
	temp = h_session->lenght;
	while (temp > h_session->left)
	{
		if (h_session->line[temp - 1] == '\n')
		{
			h_session->victor->curr_arr--;
			tputs(g_term->up, 1, putchar_);
			i = !h_session->victor->curr_arr ? -(h_session->lenght_hello) : 0;
			while (++i < h_session->victor->array[h_session->victor->curr_arr])
				tputs(g_term->nd, 1, putchar_);
		}
		else
			tputs(g_term->le, 1, putchar_);
		temp--;
	}
	tputs(g_term->ei, 1, putchar_);
}
