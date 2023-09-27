# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/23 21:30:38 by fsuomins          #+#    #+#              #
#    Updated: 2023/09/26 23:42:06 by fsuomins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC 	= includes/philo.h

SRC		= src/philo.c \
		  src/check_args.c \
		  src/init.c \
		  src/utils.c \
		  src/routine.c \
		  src/execute_threads.c \
		  src/get.c \
		  src/destroy.c

CC 		= gcc

FLAGS	= -Wall -Wextra -Werror -pthread -g

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
