/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:39:40 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	print_err(char *line, int i, int lenght)
{
	write(2, "21sh: parse error near `", 24);
	write(2, &line[i], lenght);
	write(2, "\'\n", 2);
	return (1);
}

int	check_symbolb(char *line)
{
	int i;
	int fl;

	i = 0;
	while (line[i])
	{
		fl = 0;
		while (line[i] && !is_specdel(line, i))
		{
			if (!is_delimetr(line[i]))
				fl = 1;
			if (is_agregation(line, i))
				i += 4;
			else
				++i;
		}
		if (line[i] && !fl && is_specdel(line, i))
			return (print_err(line, i, is_specdel(line, i)));
		else
			i += is_specdel(line, i);
	}
	return (0);
}

int	check_redirarg(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		while (line[i] && is_delimetr(line[i]))
			++i;
		if (is_agregation(line, i))
			i += 4;
		if (line[i] && is_redir(line, i))
		{
			i += is_redir(line, i);
			while (line[i] && is_delimetr(line[i]))
				++i;
			if (spec_token(line, i))
				return (print_err(line, i, spec_token(line, i)));
			else if (is_agregation(line, i))
				return (print_err(line, i, 4));
			else if (!line[i])
				return (print_err("\\n", 0, 2));
		}
		while (line[i] && !is_delimetr(line[i]))
			++i;
	}
	return (0);
}

int	parse_error(char *line)
{
	if (!line)
		return (0);
	if (check_symbolb(line))
		return (1);
	if (check_redirarg(line))
		return (1);
	return (0);
}
