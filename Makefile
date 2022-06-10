# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 00:52:18 by mtavares          #+#    #+#              #
#    Updated: 2022/06/10 13:21:41 by mtavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	$(foreach dir, $(SRCS_DIR), $(wildcard $(dir)/*.c))

SRCS_DIR	=	srcs

SRCS_B		=	$(foreach dir, $(SRCS_B_DIR), $(wildcard $(dir)/*.c))

SRCS_B_DIR	=	srcs_b

OBJS		=	$(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_B		=	$(subst $(SRCS_B_DIR),$(OBJS_DIR),$(SRCS_B:.c=.o))

OBJS_DIR	=	objs

NAME		=	pipex

NAME_B		=	pipex_b

CC			=	gcc -g

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

PRINTF		=	libs/printf_fd/libprintf_fd.a


all:	$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF):
		make -C libs/printf_fd

$(NAME):			$(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $(NAME)


$(OBJS_DIR)/%.o :	$(SRCS_B_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(NAME_B)

$(NAME_B):			$(PRINTF) $(OBJS_B)
		$(CC) $(CFLAGS) $(OBJS_B) $(PRINTF) -o $(NAME_B)

clean:
		$(RM) $(OBJS_DIR)
		make clean -C libs/printf_fd

fclean:				clean
		$(RM) $(NAME) $(NAME_B)
		make fclean -C libs/printf_fd

re: 				fclean all

rebonus:			fclean bonus

.PHONY:				all bonus clean fclean re reb