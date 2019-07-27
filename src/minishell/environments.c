/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:33:16 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:36:41 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char		*new_env(t_process *proc)
{
	char	*new_env;
	char	*temp;

	new_env = NULL;
	if (proc->query[1] == NULL)
		write(2, "setenv: not enough arguments\n", 29);
	if (!ft_strcmp(proc->query[1], "="))
		write(2, "zsh: bad assignment\n", 20);
	if (proc->query[2] == NULL)
	{
		if (ft_strstr(proc->query[1], "="))
			new_env = ft_strdup(proc->query[1]);
		else
			new_env = ft_strjoin(proc->query[1], "=");
	}
	else if (proc->query[3] == NULL)
	{
		temp = ft_strjoin(proc->query[1], "=");
		new_env = ft_strjoin(temp, proc->query[2]);
		free(temp);
	}
	return (new_env);
}

int			setenv_(t_process *proc)
{
	int		i;
	int		j;
	char	**temp;
	char	*tm;

	i = -1;
	if ((tm = new_env(proc)) == NULL)
		return (1);
	while (g_sh->env[++i])
	{
		j = 0;
		while (g_sh->env[i][j] == tm[j] && tm[j] != '=')
			++j;
		if (g_sh->env[i][j] == tm[j])
			CHANGE_ENV;
	}
	j = -1;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	temp[i + 1] = NULL;
	while (++j < i)
		temp[j] = g_sh->env[j];
	temp[j] = tm;
	free(g_sh->env);
	g_sh->env = temp;
	return (1);
}

int			remove_env(t_process *proc)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (g_sh->env[++i])
	{
		j = 0;
		while (proc->query[++j])
		{
			k = 0;
			while (g_sh->env[i][k] != '='
			&& proc->query[j][k] == g_sh->env[i][k])
				++k;
			if (g_sh->env[i][k] == '=')
			{
				free(g_sh->env[i]);
				g_sh->env[i] = ft_strdup("\0");
				++count;
			}
		}
	}
	return (i - count);
}

int			unset_(t_process *proc)
{
	int		j;
	int		k;
	char	**temp;
	int		count;

	if (!proc->query[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (1);
	}
	count = remove_env(proc);
	temp = (char**)malloc(sizeof(char*) * (count + 1));
	j = 0;
	k = -1;
	while (g_sh->env[++k])
	{
		if (g_sh->env[k][0] != '\0')
			temp[j++] = g_sh->env[k];
		else
			free(g_sh->env[k]);
	}
	temp[j] = NULL;
	free(g_sh->env);
	g_sh->env = temp;
	return (1);
}

char		*get_env(char *varible, char **environ)
{
	int		i;
	int		j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '='
			&& varible[j] && environ[i][j] == varible[j])
			++j;
		if (environ[i][j] == '=')
			return (&environ[i][ft_strlen(varible) + 1]);
		i++;
	}
	return (NULL);
}
