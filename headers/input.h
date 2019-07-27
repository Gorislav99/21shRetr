/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:43:12 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 19:28:27 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# define KEY_TAB 9
# define KEY_NL 10
# define KEY_ESC 27
# define KEY_BS 127
# define KEY_UP 1183
# define KEY_DOWN 1184
# define KEY_RIGHT 1185
# define KEY_LEFT 1186
# define KEY_SHIFT_UP 1341
# define KEY_SHIFT_DOWN 1342
# define KEY_END 1188
# define KEY_HOME 1190
# define KEY_SHIFT_LEFT 1344
# define KEY_SHIFT_RIGHT 1343
# define KEY_COPY_LEFT 1349
# define KEY_COPY_RIGHT 1351
# define KEY_PASTE 1297
# define KEY_CUT 1298
# define GRID_LENGHT 3
# define MODE_HEREDOC 100
# define MODE_QUOTE 101
# define MODE_PIPE 102
# define MODE_OR 103
# define MODE_BACKGROUND 104
# define MODE_AND 105
# include <termios.h>
# include <term.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "unistd.h"
# include "./vector.h"

typedef struct					s_term
{
	char						*le;
	char						*nd;
	char						*cd;
	char						*dc;
	char						*im;
	char						*ei;
	char						*so;
	char						*se;
	char						*up;
	char						*do_;

}								t_term;

typedef struct					s_history_session
{
	int							left;
	int							lenght;
	char						*line;
	int							number_hist;
	int							lenght_hello;
	int							fl;
	t_vector					*victor;
	struct s_history_session	*up;
	struct s_history_session	*down;

}								t_history_session;

t_term							*g_term;
int								g_dispersion;
char							*g_buffer;
static struct termios			g_stored_settings;
int								putchar_(int c);
void							backspace_ch(t_history_session *h_session);
void							print_ch
						(t_history_session *h_session, char key);
void							left_ch(t_history_session *h_session);
void							right_ch
								(t_history_session *h_session);
t_history_session				*add_history
							(t_history_session *h_session, int lenght_hello);
void							key_history
								(t_history_session *h_session, int key);
void							navigation_line
								(t_history_session *h_session, int key);
void							navigation_words
								(t_history_session *h_session, int key);
void							save_buff(t_history_session *h_session);
void							key_paste(t_history_session *h_session);
void							key_cut(t_history_session *h_session, int temp);
void							cut_str(char **comm, int i, int lenght);
char							*input
		(t_history_session **h_session, int lenght_hello, int mode);
void							write_vector(t_history_session *h_session);
void							key_cop(t_history_session *h_session, int key);
int								is_delim(char ch);
void							key_endhome
								(t_history_session *h_session, int key);
void							free_hsess(t_history_session *h_session);
void							multiple_promt
								(t_history_session *h_session, int mode);
void							set_termcap(char **env);
void							reset_keypress(void);
void							multiple_promt
								(t_history_session *h_session, int mode);
void							kazekage(char **arg);
int								ft_readkey(int fd);
void							key_func(t_history_session *h_session, int key);
int								key_entr(t_history_session *h_session);
int								key_control_c(t_history_session *h_session);
void							set_keypress(void);

#endif
