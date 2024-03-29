# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 09:14:12 by nsouchal          #+#    #+#              #
#    Updated: 2024/02/09 11:55:07 by nsouchal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC_FILE = main.c get_next_line.c get_next_line_utils.c init.c events.c \
			checking.c checking_valid_path.c utils.c image_error.c

DIR_BUILD		=	.build/
DIR_SRCS 		= 	srcs/
DIR_HEADERS		=	includes/
DIR_LIBFT		=	libft/
DIR_MLX			=	minilibx-linux/

HEADERFILES		= $(DIR_HEADERS)so_long.h $(DIR_HEADERS)get_next_line.h

OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
SRCS			=	$(addprefix $(DIR_SRCS),$(SRC_FILE))

FLAGS		=	-Wall -Werror -Wextra
MLX_FLAGS	=	-lXext -lX11 -lm -lz

CC = cc

.PHONY: all
all: mlx libft $(NAME)

$(NAME): $(OBJS) $(DIR_LIBFT)libft.a
			$(CC) $(OBJS) $(MLX_FLAGS) $(DIR_MLX)libmlx.a $(DIR_LIBFT)libft.a -o $(NAME)

$(DIR_BUILD)%.o: %.c $(HEADERFILES) Makefile
				mkdir -p $(shell dirname $@)
				$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

.PHONY: mlx
mlx:
		${MAKE} -C $(DIR_MLX)

.PHONY: libft
libft:
		${MAKE} -C $(DIR_LIBFT)

.PHONY: clean
clean:
	${MAKE} -C $(DIR_LIBFT) clean
	${MAKE} -C $(DIR_MLX) clean
	rm -rf $(DIR_BUILD)

.PHONY: fclean
fclean: clean
		$(MAKE) -C $(DIR_LIBFT) fclean
		rm -rf $(NAME)

.PHONY: re
re: fclean
	$(MAKE) all
