# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 14:14:38 by mtavares          #+#    #+#              #
#    Updated: 2022/06/07 21:52:51 by mtavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c utils.c parse_args.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \

SRCS_B		=	main_bonus.c utils_bonus.c parse_args_bonus.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \

OBJS		=	$(SRCS:.c=.o)

OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc	#-g -fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

NAME		=	pipex

NAME_B		=	pipex_bonus

LIBS		=	printf/libftprintf.a

INCLUDE		=	-I.

# Outro
all:		$(NAME)

%.o:		%.c
				@$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	@make -C printf				

$(NAME):	$(LIBS) $(OBJS)
				@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(NAME)
				
b:		$(NAME_B)

$(NAME_B): $(LIBS) $(OBJS_B)
				@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_B) $(LIBS) -o $(NAME_B)

clean:
				@$(RM) $(OBJS) $(OBJS_B)
				@make clean -C printf

fclean: clean
				@$(RM) $(NAME) $(NAME_B) pipex_bonus.dSYM pipex.dSYM
				@make fclean -C printf

re:		fclean all

reb:	fclean b

.PHONY: all clean fclean re b reb