# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 14:14:38 by mtavares          #+#    #+#              #
#    Updated: 2022/05/27 10:46:16 by mtavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c utils.c parse_args.c

OBJS		=	$(SRCS:.c=.o)

CC			=	clang	-g #-fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

NAME		=	pipex

LIBS		=	libftprintf.a

INCLUDE	=	-I .

# Outro
all:		$(NAME)


%.o:		%.c
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

maker:
					make -C printf
					cp printf/ft_printf.h .
					cp printf/libftprintf.a .

$(NAME):	 maker $(OBJS)
				$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

clean:
				make clean -C printf
				$(RM) $(OBJS)

fclean:	clean
				make fclean -C printf
				$(RM) $(NAME) libftprintf.a ft_printf.h

re:		fclean all

.PHONY: all clean fclean re
