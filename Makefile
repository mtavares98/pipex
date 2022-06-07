# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 14:14:38 by mtavares          #+#    #+#              #
#    Updated: 2022/06/07 01:49:26 by mtavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c utils.c parse_args.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \

SRCS_B		=	main_bonus.c utils_bonus.c parse_args_bonus.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \

OBJS		=	$(SRCS:.c=.o)

OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc	-g #-fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

NAME		=	pipex

NAME_B		=	pipex

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
				
bonus:		$(NAME_B)

$(NAME_B):	maker $(OBJS_B)
				$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_B) $(LIBS) -o $(NAME_B)

makerclean:
				make clean -C printf

makerfclean:
				make fclean -C printf

clean:		makerclean
				$(RM) $(OBJS) $(OBJS_B)

fclean:		makerfclean clean
				$(RM) $(NAME)

re:		fclean all

rebonus:	fclean bonus

.SILENT: all clean fclean re maker makerclean makerfclean
.PHONY: all clean fclean re maker makerclean makerfclean
