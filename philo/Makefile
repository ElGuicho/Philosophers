# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 15:29:59 by gmunoz            #+#    #+#              #
#    Updated: 2024/12/13 15:57:23 by gmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Leak check
LEAKS =  valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

# Executable name
NAME = philo

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra

# Source files
SRC = 

# Object files
OBJS = $(SRC:.c=.o)

# Default NAME
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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