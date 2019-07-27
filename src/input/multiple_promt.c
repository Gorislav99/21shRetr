/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_promt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:56:34 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:26:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	multiple_promt(t_history_session *h_session, int mode)
{
	if (mode == MODE_QUOTE || mode == MODE_PIPE
						|| mode == MODE_AND || mode == MODE_OR)
	{
		h_session->victor->push_back(&(h_session->victor), 0);
		print_ch(h_session, '\n');
		if (mode == MODE_QUOTE)
			ft_printf("%s", COMMAND_QUOTE);
		else if (mode == MODE_PIPE)
			ft_printf("%s", "pipe> ");
		else if (mode == MODE_AND)
			ft_printf("%s", "cmdand> ");
		else if (mode == MODE_OR)
			ft_printf("%s", "cmdor> ");
	}
	if (mode == MODE_HEREDOC)
		ft_printf("heredoc> ");
}
