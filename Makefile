SRC_21SH = ./src/21sh/
SRC_LAUNCH = ./src/launch/
SRC_MINISHELL = ./src/minishell/
SRC_INPUT = ./src/input/
SRC_VECTOR = ./src/vector/
SRC_PARSER = ./src/parser/
SRC_LEXER = ./src/lexer/

NAME = 21sh
PRINT = lib/printf/libftprintf.a
NAME_21SH = main.c kazekage.c assist_21sh.c
NAME_MINISHELL = built_ins.c cpy_func.c launch.c linked_list.c\
				linked_list2.c linked_list3.c sig_handler.c utilities.c utilities2.c environments.c cd.c
NAME_LAUNCH = aux_utilities.c job_process_status.c job_utils.c jobs_builtins.c launch_pro.c job_utils_print.c\
				heredoc_input.c child_launch_proc.c holder_launch_struct.c jobs_fg_bg_builtin.c jobs_kill_builtin.c\
				out_redir_launch.c pipe_and_preconfig.c
NAME_INPUT = assist_func.c key_backspace.c key_copy.c key_cut.c key_paste.c key_endhome.c history_session.c input.c\
			navigation_words.c navigation_line.c save_buff.c spec_key.c set_termcap.c multiple_promt.c key_control.c\
			
NAME_VECTOR = vector.c
NAME_PARSER = parser.c replace_env.c write_arg.c replace_dir.c get_token.c assist_parser.c parse_error.c multiple_line.c
NAME_LEXER = lexer.c new_segment.c input_path.c output_path.c  free_job.c new_query.c new_agregation.c

SRC = 	$(addprefix $(SRC_21SH), $(NAME_21SH))\
		$(addprefix $(SRC_MINISHELL), $(NAME_MINISHELL))\
		$(addprefix $(SRC_LAUNCH), $(NAME_LAUNCH))\
		$(addprefix $(SRC_INPUT), $(NAME_INPUT))\
		$(addprefix $(SRC_VECTOR), $(NAME_VECTOR))\
		$(addprefix $(SRC_PARSER), $(NAME_PARSER))\
		$(addprefix $(SRC_LEXER), $(NAME_LEXER))\


FLAG = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
OBJ = *.o

CG = \033[92m
all: start $(NAME)
$(NAME):
	@make -sC ./lib/printf/
	@gcc  -c $(FLAG) $(SRC)
	@gcc  -ltermcap -o $(NAME) $(OBJ) -L. $(PRINT) 

	@echo "\r$(CY)--------------------------------------------------- GO --------------------------------------------------------"
start:
	@echo "\r$(CG)compile...																			  "
	@echo "	-------------------------------------------------------------------------------------------------------"
	@echo "	|	                000|             000|               00|       	         	              |	"
	@echo "	|	000000000000|          000000|           000000|    00|  	00000|   00|	    00|       | "
	@echo "	|	000  00  000|	000|   00  00|   000|    000|       000000|	00|      00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|      0000|    00  00|	00000|   00|        00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|        000|   00  00|	00|  	 00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|    000000|    00  00|	00000|   0000000|   0000000|  |	"
	@echo "	-------------------------------------------------------------------------------------------------------"
clean:
	@make clean -sC lib/printf/
	@rm -rf $(OBJ)
fclean: clean
	@make fclean -sC lib/printf/
	@rm -rf $(NAME)
re: fclean all clean
