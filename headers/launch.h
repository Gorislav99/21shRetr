/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:01:17 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 18:37:24 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCH_H
# define LAUNCH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <pwd.h>
# include <glob.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <libgen.h>
# include <errno.h>
# include "minishell.h"

# define NR_JOBS 20
# define NR_BUILTINS 11
# define PATH_BUFSIZE 1024
# define TOKEN_BUFSIZE 64
# define DEBUG_LOG 0

# define BACKGROUND_EXECUTION 0
# define FOREGROUND_EXECUTION 1
# define PIPELINE_EXECUTION 2

# define RIGHTS  O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define CREATE_ATTR O_CREAT | RIGHTS
# define APPEND_ATTR O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

# define STATUS_RUNNING 0
# define STATUS_DONE 1
# define STATUS_SUSPENDED 2
# define STATUS_CONTINUED 3
# define STATUS_TERMINATED 4

# define PROC_FILTER_ALL 0
# define PROC_FILTER_DONE 1
# define PROC_FILTER_REMAINING 2

# define COLOR_NONE "\033[m"
# define COLOR_RED "\e[91m"
# define COLOR_MAGENTA "\e[1;95m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_CYAN "\033[1;36m"
# define COLOR_GREEN "\033[1;32;32m"
# define COLOR_GRAY "\033[1;30m"

/*
** 				process and t_job list structure
*/

typedef struct			s_aggregation
{
	int					in;
	int					out;

}						t_aggregation;

typedef struct			s_process
{
	char				**query;
	char				**heredoc;
	char				*input_path;
	char				**input_file;
	char				**output_file;
	char				*output_path;
	int					output_mode;
	t_aggregation		*aggregate;
	pid_t				pid;
	int					type;
	int					status;
	int					exec_mode;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	int					id;
	t_process			*root;
	pid_t				pgid;
	int					mode;
}						t_job;

typedef struct			s_builtins
{
	char				builtin_str[NR_BUILTINS][24];
	int					(*builtin_func[NR_BUILTINS]) (t_process*);
}						t_builtins;

typedef struct			s_launch
{
	t_process			*proc;
	int					job_id;
	int					status;
	int					in_fd;
	int					out_fd;
	int					fd[2];
	int					holder[48];
}						t_launch;

typedef struct			s_shell_info
{
	char				cur_user[TOKEN_BUFSIZE];
	char				cur_dir[PATH_BUFSIZE];
	char				pw_dir[PATH_BUFSIZE];
	char				**env;
	t_job				*jobs[NR_JOBS + 1];
	t_builtins			*builtins;
	int					signal;
	t_launch			*launch;
}						t_shell_info;

typedef struct			s_job_pid
{
	int					proc_count;
	int					wait_pid;
	int					wait_count;
	int					status;
	int					exit_status;
}						t_job_pid;

t_shell_info				*g_sh;

/*
** 				t_job handlers
*/

int						get_next_job_id(void);
int						insert_job(t_job *job);
void					check_zombie(void);
int						remove_job(int id);
int						print_processes_of_job(int id);
int						wait_for_job(int id);
int						get_proc_count(int id, int filter);
int						get_job_id_by_pid(int pid);
int						is_job_completed(int id);
void					shell_cleaner(void);

/*
** 				launcher funcs
*/

int						shell_launch_job(t_job *job);
int						shell_launch_process(t_job *job,
		t_process *proc, int in_fd, int out_fd);
int						execute_builtin_command(t_process *proc);
int						set_process_status(int pid, int status);
int						print_job_status(int id);
void					built_init(void);
int						launch_proc_cycle(t_process *proc,
		t_launch *launch, t_job *job);
void					parent_launch_process(t_process *proc,
		t_job *job, pid_t childpid);
t_launch				*h_launch_init(void);

/*
** 				heredocs
*/

char					*readline_her(t_process *proc, int i);
void					stdin_heredoc(t_process *proc,
		t_launch *launch, char *line);
void					launch_heredoc(t_process *proc, t_launch *launch);

/*
** 				out redirection launch
*/

int						launch_out_redir(t_process *proc,
											t_launch *launch);
int						launch_base_config(t_launch *launch,
		t_process *proc, t_job *job);

/*
** 				child launch processes
*/

void					pgid_and_dup_handle(t_process *proc,
		t_job *job, int in_fd, int out_fd);
void					child_launch_proc(t_job *job,
		t_process *proc, int in_fd, int out_fd);
void					signal_default_changer(t_process *proc, t_job *job);

/*
** 				PIPES and config
*/

int						pre_launch_config(t_process *proc, t_launch *launch);
void					launch_pipe_config(t_process *proc,
		t_launch *launch, t_job *job);

/*
** 				built-ins
*/

int						shell_jobs(t_process *proc);
int						get_pgid_by_job_id(int id);
t_job					*get_job_by_id(int id);
int						set_job_status(int id, int status);
int						wait_for_pid(int pid);
int						shell_kill(t_process *proc);
int						shell_bg(t_process *proc);
int						shell_fg(t_process *proc);
char					*read_ln_heredoc(char *eof);
void					update_holder(t_launch *launch, int fd);
void					print_holder(t_launch *launch);
void					clean_holder(t_launch *launch);

/*
** 				aux utils
*/

void					sh_update_cwd_info(void);
int						check_access(char **files, int id);
char					*str_join_her(char *s1, char *s2);

/*
** 				ENV
*/

int						print_env(t_process *proc);
int						setenv_(t_process *proc);
char					*get_env(char *varible, char **environ);
int						remove_env(t_process *proc);
int						unset_(t_process *proc);
int						cd_(t_process *proc);
void					print_error(char *error, char *name);
void					sigint_handler(int signal);
char					**init_environ(char **env);

#endif
