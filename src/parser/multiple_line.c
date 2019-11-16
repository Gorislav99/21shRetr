/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:21:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	which_specdel(char *line, int i)
{
	if (!line)
		return (0);
	if (line[i] == '|' && line[i + 1] == '|')
		return (MODE_OR);
	else if (line[i] == '|')
		return (MODE_PIPE);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (MODE_AND);
	return (0);
}

int	get_md(char *line, int *i)
{
	int		mode;

	mode = which_specdel(line, *i);
	*i += is_specdel(line, *i);
	while (line[*i] && is_delim(line[*i]))
		++(*i);
	if (!line[*i])
		return (mode);
	return (0);
}

int	is_nwln(t_history_session *h_session, char *line, int i)
{
	if (line[i] == '\\' && i > 0 && line[i - 1] != '\\' && line[i + 1] == '\0')
	{
		cut_str(&h_session->line, h_session->lenght - 1, h_session->lenght);
		h_session->lenght--;
		h_session->victor->array[h_session->victor->curr_arr]--;
		h_session->left--;
		return (MODE_MULTPL);
	}
	return (0);
}

int	multiply_line(char *line, t_history_session *h_session)
{
	int		i;
	char	quote;
	int		mode;

	i = 0;
	while (line && line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') &&
								!(i > 0 && line[i - 1] == '\\'))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				++i;
			if (!line[i++])
				return (MODE_QUOTE);
		}
		else if (is_specdel(line, i) && (mode = get_md(line, &i)))
			return (mode);
		else if (is_nwln(h_session, line, i))
			return (MODE_MULTPL);
		else
			++i;
	}
	return (0);
}
