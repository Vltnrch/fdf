# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 17:32:05 by vroche            #+#    #+#              #
#    Updated: 2015/01/26 15:10:23 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIB = -framework OpenGL -framework AppKit \
		-L./minilibx_macos -lmlx -L./libft -lft -lm

HDR = -I./minilibx_macos -I./libft

C = ft_draw_line.c \
	ft_key.c \
	ft_list.c \
	ft_split.c \
	ft_manage.c \
	main.c

all: $(NAME)

$(NAME):
	make -C ./libft
	make -C ./minilibx_macos
	gcc -Wall -Werror -Wextra $(HDR) $(LIB) $(C) -o $(NAME)

clean:
	make -C ./libft clean
	make -C ./minilibx_macos clean

fclean:
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
