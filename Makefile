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
SRC = src/main.c \
	  src/parsing_utils.c \
	  src/parsing.c \
	  src/fdf.c \
	  src/coefficient.c \
	  src/projection.c \
	  src/projection_utils.c \
	  src/isometry.c \
	  src/parallele.c \
	  src/color_set.c \
	  src/color_set_error.c \
	  src/color_change.c \
	  src/color_map_fade.c \
	  src/bresenham.c \
	  src/bresenham_utils.c \
	  src/event.c \
	  src/event_utils.c \
	  src/translation.c \
	  src/exit.c
OBJ = $(SRC:.c=.o)
CC = cc
C_FLAGS = -Wall -Wextra -Werror -g3
INC_LIBFT = ./libft/megalibft.a
INC_MINILIBX = -L./minilibx-linux -lmlx -lX11 -lXext
INC_MATH = -lm
DIR_MINILIBX = ./minilibx

all: $(NAME)

%.o:%.c
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	make -j -C ./libft
	make -j -C ./minilibx-linux
	$(CC) $(C_FLAGS) $(OBJ) -I $(DIR_MINILIBX) $(INC_LIBFT) $(INC_MINILIBX) $(INC_MATH) -o $@

clean :
	make -j clean -C ./libft
	make -j clean -C ./minilibx-linux
	rm -f src/*.o

fclean : clean
	make -j fclean -C ./libft
	rm -f fdf

re : fclean
	make all

.PHONY : all clean fclean re