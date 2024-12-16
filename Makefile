# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galambey <galambey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 11:40:45 by galambey          #+#    #+#              #
#    Updated: 2023/08/31 16:57:42 by galambey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
C_FLAGS = -Wall -Wextra -Werror -g3
INC_LIBFT = ./libft/megalibft.a
INC_MINILIBX = -L./minilibx-linux -lmlx -lX11 -lXext
INC_MATH = -lm
DIR_MINILIBX = ./minilibx

################################### SOURCES ###################################

COLOR_DIR         	=   color/
COLOR_SRCS        	=   color_set.c \
	  					color_set_error.c \
	  					color_change.c \
	  					color_map_fade.c

BRESENHAM_DIR       =   bresenham/
BRESENHAM_SRCS      =   bresenham.c \
	  					bresenham_utils.c

EVENTS_DIR        	=   events/
EVENTS_SRCS       	=   event.c \
	  					event_utils.c \
						translation.c

PROJECTIONS_DIR     =   projection/
PROJECTIONS_SRCS    =   projection.c \
	  					projection_utils.c \
	  					isometry.c \
	  					parallele.c \
						coefficient.c

PARSING_DIR       	=   parsing/
PARSING_SRCS      	=   parsing_utils.c \
	  					parsing.c

MAIN_DIR       		=   main/
MAIN_SRCS      		=   main.c \
	  					fdf.c

END_DIR       		=   end/
END_SRCS      		=   exit.c

############################# HANDLE DIRECTORIES ##############################

SRCS_DIR        =   srcs/

SRCS			=	$(addprefix $(COLOR_DIR), $(COLOR_SRCS)) \
				$(addprefix $(BRESENHAM_DIR), $(BRESENHAM_SRCS)) \
				$(addprefix $(EVENTS_DIR), $(EVENTS_SRCS)) \
				$(addprefix $(PROJECTIONS_DIR), $(PROJECTIONS_SRCS)) \
				$(addprefix $(PARSING_DIR), $(PARSING_SRCS)) \
				$(addprefix $(MAIN_DIR), $(MAIN_SRCS)) \
				$(addprefix $(END_DIR), $(END_SRCS))

OBJS_DIR 		= 	.objs/

OBJS_NAMES 		= 	$(SRCS:.c=.o)

OBJS_FOLDER		=	$(addprefix $(OBJS_DIR), $(COLOR_DIR) \
                        $(BRESENHAM_DIR) \
                        $(EVENTS_DIR) \
                        $(PROJECTIONS_DIR) \
                        $(PARSING_DIR) \
                        $(MAIN_DIR) \
                        $(END_DIR))

OBJS			= $(addprefix $(OBJS_DIR), $(OBJS_NAMES))

DEPS := $(OBJS:.o=.d)

#################################### RULES ####################################

all: $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -j -C ./libft
	make -j -C ./minilibx-linux
	$(CC) $(C_FLAGS) $(OBJS) -I $(DIR_MINILIBX) $(INC_LIBFT) $(INC_MINILIBX) $(INC_MATH) -o $@

clean :
	make -j clean -C ./libft
	make -j clean -C ./minilibx-linux
	rm -rf $(OBJS)

fclean : clean
	make -j fclean -C ./libft
	rm -f fdf

re : fclean
	make all

.PHONY : all clean fclean re