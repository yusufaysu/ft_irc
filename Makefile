# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 20:55:10 by altugyasar        #+#    #+#              #
#    Updated: 2023/03/11 03:14:33 by alyasar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

INC =	inc/ft_irc.hpp \
		inc/Server.hpp \
		inc/User.hpp \
		inc/Channel.hpp \

SRC =	src/main.cpp \
		src/Server.cpp \
		src/User.cpp \
		src/Channel.cpp \
		src/numericReply.cpp \
		src/utils.cpp \
		src/cmds/pass.cpp \
		src/cmds/user.cpp \
		src/cmds/nick.cpp \
		src/cmds/join.cpp \
		src/cmds/privmsg.cpp \
		src/cmds/ping.cpp \
		src/cmds/kick.cpp \
		src/cmds/part.cpp \
		src/cmds/quit.cpp \

OBJ =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all
