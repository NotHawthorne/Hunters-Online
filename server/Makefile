# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alkozma <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 15:35:39 by alkozma           #+#    #+#              #
#    Updated: 2020/03/07 01:48:53 by alkozma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

SRC = src/Packet.cpp src/Aura.cpp src/Item.cpp src/Server.cpp src/Player.cpp src/main.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))
DEBUGDEFINES := -D_DEBUG

CXX = g++
CXXFLAGS = -Iincludes -lpthread -lsqlite3 -g -fsanitize=address

debug: CXXFLAGS += -D_DEBUG
debug: re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

run: re
	./$(NAME)

re: fclean all
