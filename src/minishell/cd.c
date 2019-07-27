/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:39:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 19:16:32 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char		*get_home(char **environ)
{
	char	*path;
	char	*temp;

	path = NULL;
	temp = get_env("HOME", environ);
	if (temp)
		path = ft_strjoin("/", temp);
	return (path);
}

static void	set_pwd(void)
{
	char	new_dir[100];
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (g_sh->env[++i])
	{
		if (ft_strstr(g_sh->env[i], "PWD=") &&
			!ft_strstr(g_sh->env[i], "OLDPWD"))
			break ;
	}
	while (g_sh->env[j])
	{
		if (ft_strstr(g_sh->env[j], "OLDPWD"))
			break ;
		++j;
	}
	if (!g_sh->env[i] || !g_sh->env[j])
		return ;
	free(g_sh->env[j]);
	g_sh->env[j] = ft_strjoin("OLDPWD=", &g_sh->env[i][4]);
	getcwd(new_dir, 100);
	free(g_sh->env[i]);
	g_sh->env[i] = ft_strjoin("PWD=", new_dir);
}

static void	back_to_oldpwd(void)
{
	int	j;

	j = 0;
	while (g_sh->env[j])
	{
		if (ft_strstr(g_sh->env[j], "OLDPWD="))
			break ;
		++j;
	}
	if (!g_sh->env[j])
		return ;
	chdir(&g_sh->env[j][7]);
	if (ft_strstr(&g_sh->env[j][7], getenv("HOME")))
		ft_printf("~%s\n", &g_sh->env[j][7 + 15]);
	else
		ft_printf("%s\n", &g_sh->env[j][7]);
	set_pwd();
}

static void	cd_ext(t_process *proc, int i)
{
	struct stat buff;

	if (!lstat(proc->query[i], &buff) && access(proc->query[i], 0) != 0)
		print_error("cd: no such file or directory: ", proc->query[i]);
	else if ((buff.st_mode & S_IFMT) != S_IFDIR)
		print_error("cd: not a directory: ", proc->query[i]);
	else
		print_error("cd: permission denied: ", proc->query[i]);
}

int			cd_(t_process *proc)
{
	int			i;

	i = 1;
	proc->query[i] && !ft_strcmp(proc->query[i], "--") ? ++i : 0;
	if (proc->query[i] == NULL)
		chdir(get_home(g_sh->env)) != -1 ? set_pwd() : 0;
	else if (!ft_strcmp(proc->query[i], "-") && proc->query[i + 1] == NULL)
		back_to_oldpwd();
	else if (proc->query[i + 1] != NULL)
		print_error("cd: string not in pwd: ", proc->query[i]);
	else
	{
		if (chdir(proc->query[i]) == -1)
			cd_ext(proc, i);
		else
			set_pwd();
	}
	sh_update_cwd_info();
	return (1);
}
