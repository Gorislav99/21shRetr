/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:51:43 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:24:34 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_keypress(void)
{
	struct termios	new_settings;

	tcgetattr(0, &g_stored_settings);
	new_settings = g_stored_settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
}

void	reset_keypress(void)
{
	tcsetattr(0, TCSANOW, &g_stored_settings);
}

char	*get_termcap(void)
{
	char	*term;
	char	*term_edit;

	if ((term = ft_strnew(2048)))
	{
		if ((term_edit = ft_strdup(getenv("TERM"))))
		{
			tgetent(term, term_edit);
			if (tgetent(term, term_edit) == 1)
			{
				free(term_edit);
				return (term);
			}
			free(term_edit);
		}
		free(term);
	}
	return (NULL);
}

void	set_termenv(char *termcap)
{
	g_term = (t_term *)malloc(sizeof(t_term));
	g_term->le = tgetstr("le", &termcap);
	g_term->nd = tgetstr("nd", &termcap);
	g_term->cd = tgetstr("cd", &termcap);
	g_term->dc = tgetstr("dc", &termcap);
	g_term->im = tgetstr("im", &termcap);
	g_term->ei = tgetstr("ei", &termcap);
	g_term->so = tgetstr("so", &termcap);
	g_term->se = tgetstr("se", &termcap);
	g_term->up = tgetstr("up", &termcap);
	g_term->do_ = tgetstr("do", &termcap);
}

void	set_termcap(char **env)
{
	char	*termcap;

	env = NULL;
	termcap = get_termcap();
	if (termcap)
	{
		set_termenv(termcap);
	}
}
