# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleveque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 10:15:06 by bleveque          #+#    #+#              #
#    Updated: 2019/05/10 15:35:38 by anrzepec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, libft, clean, fclean, re 

NAME_1 = lem-in

INC_PATH = includes/
SRCS_PATH = srcs/
OBJS_PATH = objs/
LIB_PATH = libft/

SRC_NAME_1 = main.c \
			 jenkins_hash.c \
			 error_output.c \
			 parse_links.c \
			 tab_tools.c \
			 push_ants.c \
			 ft_parsing_tools.c \
			 create_graph.c \
			 links.c \
			 bfs_samere.c \
			 bfs_add_functions.c \
			 get_paths.c \
			 edmond_karp.c \
			 check_functions.c \
			 nb_ants.c \

INC_NAME = lem_in.h
LIB_NAME = libft.a
OBJ_NAME_1 = $(SRC_NAME_1:.c=.o)
SRCS_1 = $(addprefix $(SRCS_PATH),$(SRC_NAME_1))
OBJS_1 = $(addprefix $(OBJS_PATH),$(OBJ_NAME_1))
INC = $(addprefix $(INC_PATH),$(INC_NAME))
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

RED = \x1b[31;5;01m
GREEN = \x1b[32;01m

CC = gcc
CFLAGS =

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ -c $<

all : lib $(NAME_1) 

lib :
	@printf "Compiling libft ...\r"
	@make -C libft

$(NAME_1) : $(OBJS_1) $(LIB) 
	@$(CC) $(LIB) $^ -o $@
	@printf "Compiling lem_in ...\r"
	@echo "$(RED)lem_in$(END)$(GREEN) has compiled ✓✓$(END)"

clean :
	@/bin/rm -f $(OBJS_1) 
	@rmdir $(OBJS_PATH) 2> /dev/null || true
	@cd $(LIB_PATH) ; $(MAKE) fclean 


fclean : clean
	@/bin/rm -f $(NAME_1) 
	@make fclean -C libft

re : fclean all
