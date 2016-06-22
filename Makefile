# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/16 12:00:42 by aleung-c          #+#    #+#              #
#    Updated: 2016/06/16 12:00:49 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Matt_daemon

SRC = Signal_handler.cpp \
main.cpp \
Daemon.cpp \
Logger.cpp \
Tintin_reporter.cpp \
Cryptage.cpp


OBJ = $(SRC:.cpp=.o)

CC = clang++ -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
