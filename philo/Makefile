# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/09 16:02:42 by nait-ali          #+#    #+#              #
#    Updated: 2023/08/03 22:25:37 by nait-ali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror

FILES =  philo.c  les_outiles.c initialisation.c threads.c actions.c

OBJS = $(FILES:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME) 

clean:
	rm -f $(OBJS)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c  $< -o $@ 

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
