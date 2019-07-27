/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:25:02 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		lenght_token(char *line, int j)
{
	int		lenght;
	char	temp;

	lenght = 0;
	if (is_agregation(line, j))
		return (4);
	if ((lenght = spec_token(line, j)))
		return (lenght);
	while (line[j] && !is_delimetr(line[j]) && !spec_token(line, j))
	{
		if (line[j] == '\"' || line[j] == '\'')
		{
			temp = line[j++];
			while (line[j] && line[j] != temp)
			{
				++j;
				lenght++;
			}
		}
		else
			lenght++;
		j += line[j] ? 1 : 0;
	}
	return (lenght);
}

char	*get_token(char *line, int *j)
{
	char	*token;
	char	temp;
	int		lenght;
	int		i;

	i = 0;
	lenght = lenght_token(line, *j);
	token = (char*)malloc(sizeof(char) * (lenght + 1));
	if (!token)
		exit(1);
	while (i < lenght && line[(*j)])
	{
		if (line[(*j)] == '\"' || line[*j] == '\'')
		{
			temp = line[(*j)];
			(*j)++;
			while (line[(*j)] && line[(*j)] != temp)
				token[i++] = line[(*j)++];
			(*j) += line[*j] ? 1 : 0;
		}
		else
			token[i++] = line[(*j)++];
	}
	token[i] = '\0';
	return (token);
}
