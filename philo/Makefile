# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 15:29:59 by gmunoz            #+#    #+#              #
#    Updated: 2025/07/17 22:03:45 by gmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Leak check
LEAKS =  valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

# Executable name
NAME = philo

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pthread

# Source files
SRC = src/philo.c src/philo_utils.c src/init.c src/thread_init.c src/monitor.c \
	src/cycle_actions.c

# Object files
OBJS = $(SRC:.c=.o)

# Default NAME
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Link object files into the executable
$(NAME): $(OBJS)

# Clean up generated files
clean:
	rm -f $(OBJS)

# Clean up everything
fclean: clean
	rm -f $(NAME)

# Re-compile everything
re: fclean
	make all

.PHONY: all clean fclean re