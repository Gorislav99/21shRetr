/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_21sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:26:51 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 19:32:48 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sigint_handler(int signal)
{
	signal = 0;
	printf("\n");
}

void	sh_update_cwd_info(void)
{
	getcwd(g_sh->cur_dir, sizeof(g_sh->cur_dir));
}

void	built_init(void)
{
	g_sh->builtins = ft_memalloc(sizeof(t_builtins) + 1);
	g_sh->builtins->builtin_func[0] = &cd_;
	g_sh->builtins->builtin_func[1] = &help_shell;
	g_sh->builtins->builtin_func[2] = &exit_shell;
	g_sh->builtins->builtin_func[3] = &echo;
	g_sh->builtins->builtin_func[4] = &print_env;
	g_sh->builtins->builtin_func[5] = &setenv_;
	g_sh->builtins->builtin_func[6] = &unset_;
	g_sh->signal = 0;
	ft_strcpy(g_sh->builtins->builtin_str[0], "cd");
	ft_strcpy(g_sh->builtins->builtin_str[1], "help");
	ft_strcpy(g_sh->builtins->builtin_str[2], "exit");
	ft_strcpy(g_sh->builtins->builtin_str[3], "echo");
	ft_strcpy(g_sh->builtins->builtin_str[4], "jobs");
	ft_strcpy(g_sh->builtins->builtin_str[5], "bg");
	ft_strcpy(g_sh->builtins->builtin_str[6], "fg");
	ft_strcpy(g_sh->builtins->builtin_str[7], "kill");
	ft_strcpy(g_sh->builtins->builtin_str[8], "env");
	ft_strcpy(g_sh->builtins->builtin_str[9], "setenv");
	ft_strcpy(g_sh->builtins->builtin_str[10], "unsetenv");
	g_sh->launch = NULL;
}

char	**init_environ(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	if (!i)
		return (NULL);
	new_env = (char**)malloc(sizeof(char*) * (i + 1));
	if (!new_env)
		exit(1);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}
