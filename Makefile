# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 14:14:38 by mtavares          #+#    #+#              #
#    Updated: 2022/06/03 14:21:51 by mtavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c utils.c utils2.c variable_init.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc	-g #-fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

NAME		=	pipex

LIBS		=	printf/libftprintf.a

INCLUDE		=	-I.

# Outro
all:		$(NAME)

%.o:		%.c
				$(CC) $(CFLAGS) -c $< -o $@

maker:
					@make -C printf

$(NAME):	maker $(OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(NAME)

makerclean:
				make clean -C printf

makerfclean:
				make fclean -C printf

clean:		makerclean
				$(RM) $(OBJS)

fclean:		makerfclean clean
				$(RM) $(NAME)

re:		fclean all

.SILENT: all clean fclean re maker makerclean makerfclean
.PHONY: all clean fclean re maker makerclean makerfclean
