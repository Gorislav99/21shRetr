/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:53:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:29:19 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	replace_str(char **chang_line, int i, int lenght, char *env_verb)
{
	char *temp;
	char *tmp;

	temp = *chang_line;
	*chang_line = ft_strsub(temp, 0, i);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, env_verb);
	free(tmp);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, &temp[lenght]);
	free(tmp);
	free(temp);
}

char	**parser(t_history_session **h_session, char **env, int lenght_hello)
{
	char	**arg;
	char	*line;
	int		mode;

	*h_session = add_history(*h_session, lenght_hello);
	mode = 0;
	while (1)
	{
		line = input(h_session, lenght_hello, mode);
		if (parse_error(line))
		{
			free(line);
			return (NULL);
		}
		mode = multiply_line(line);
		if (!mode)
			break ;
		free(line);
	}
	line = replace_env(line, env);
	line = replace_dir(line, env);
	arg = write_arg(line);
	free(line);
	return (arg);
}
