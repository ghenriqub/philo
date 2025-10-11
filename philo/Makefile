# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 19:44:31 by lgertrud          #+#    #+#              #
#    Updated: 2025/10/11 21:31:00 by ghenriqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror

#directories
SRC_DIR = src
I_DIR = includes

#includes
INCLUDES = -I$(I_DIR)

#sources
SRC =	$(SRC_DIR)/cleanup.c \
		$(SRC_DIR)/functions.c \
		$(SRC_DIR)/init_args.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/monitoring.c \
		$(SRC_DIR)/philosophers.c \
		$(SRC_DIR)/utils_args.c

#objects
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)
	rm -f $(OBJS)

re: fclean all
