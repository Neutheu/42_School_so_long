# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 09:38:53 by nsouchal          #+#    #+#              #
#    Updated: 2023/11/28 14:56:19 by nsouchal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c printf_c.c printf_d_i.c printf_s.c printf_u.c printf_xlow_xupp.c \
		printf_p.c

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra

CC = cc

LIB = ft_printf.h

%.o: %.c $(LIB)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

compile : $(SRC)
	$(CC) $^

$(NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
