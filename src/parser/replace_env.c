/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:55:23 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:30:52 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*check_env_verb(char *line, int i, int *lenght)
{
	char	*temp;
	char	*temp2;

	*lenght = ++i;
	if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]))
	{
		return ("$");
	}
	while (ft_isalpha(line[(*lenght)]) || ft_isdigit(line[(*lenght)]))
		++(*lenght);
	temp = ft_strsub(line, i, (*lenght) - i);
	i = (*lenght);
	if (getenv(temp))
	{
		temp2 = getenv(temp);
		free(temp);
		return (temp2);
	}
	free(temp);
	return (" ");
}

static int	envin_quote(char **chang_line, int i, char **env)
{
	int		lenght;
	char	*env_verb;

	lenght = i;
	env = NULL;
	env_verb = check_env_verb(*chang_line, i, &lenght);
	if (!ft_strcmp(env_verb, " "))
		cut_str(chang_line, i, lenght);
	else if (ft_strcmp(env_verb, "$"))
	{
		replace_str(chang_line, i, lenght, env_verb);
		i += ft_strlen(env_verb);
	}
	else
		++i;
	return (i);
}

static int	miss_quote(char **chang_line, int i, char **env)
{
	if ((*chang_line)[i] == '\'')
	{
		++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\'')
			++i;
		i += (*chang_line)[i] ? 1 : 0;
	}
	else if ((*chang_line)[i] == '\"')
	{
		++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\"')
		{
			if ((*chang_line)[i] == '$')
				i = envin_quote(chang_line, i, env);
			else
				++i;
		}
		i += (*chang_line)[i] ? 1 : 0;
	}
	return (i);
}

char		*replace_env(char *chang_line, char **env)
{
	int		i;
	int		lenght;
	char	*env_verb;

	i = 0;
	while (chang_line && chang_line[i])
	{
		if (chang_line[i] == '\'' || chang_line[i] == '\"')
			i = miss_quote(&chang_line, i, env);
		else if (chang_line[i] == '$')
		{
			env_verb = check_env_verb(chang_line, i, &lenght);
			if (!ft_strcmp(env_verb, " "))
				cut_str(&chang_line, i, lenght);
			else
			{
				if (ft_strcmp(env_verb, "$"))
					replace_str(&chang_line, i, lenght, env_verb);
				i += ft_strcmp(env_verb, "$") ? ft_strlen(env_verb) : 1;
			}
		}
		else
			++i;
	}
	return (chang_line);
}
