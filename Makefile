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

SRC = ./src_Server/Signal_handler.cpp \
./src_Server/main.cpp \
./src_Server/Daemon.cpp \
./src_Server/Logger.cpp \
./src_Server/Tintin_reporter.cpp \
./src_Common/Cryptage.cpp \

SRC2 = ./src_Client/main_client.cpp \
./src_Client/Client.cpp \
./src_Common/Cryptage.cpp

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
