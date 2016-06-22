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

NAME1 = Matt_daemon
NAME2 = Ben_AFK

SRC = Signal_handler.cpp \
main.cpp \
Daemon.cpp \
Logger.cpp \
Tintin_reporter.cpp \
Cryptage.cpp \
Client.cpp

SRC2 = Signal_handler.cpp \
main_client.cpp \
Daemon.cpp \
Logger.cpp \
Tintin_reporter.cpp \
Cryptage.cpp \
Client.cpp


OBJ = $(SRC:.cpp=.o)

OBJ2 = $(SRC2:.cpp=.o)

CC = clang++ -Wall -Werror -Wextra -lgmp

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ)
	$(CC) $(OBJ) -o $@

$(NAME2): $(OBJ2)
	$(CC) $(OBJ2) -o $@

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ2)

fclean: clean
	rm -rf $(NAME1)
	rm -rf $(NAME2)

re: fclean all

.PHONY: all clean fclean re
