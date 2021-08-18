# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/18 19:32:44 by jihoh             #+#    #+#              #
#    Updated: 2021/08/18 19:32:45 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra

SERVER = server
SERVER_SRCS = server.o

CLIENT = client
CLIENT_SRCS = client.o

all : $(SERVER) $(CLIENT)

$(CLIENT) : $(CLIENT_SRCS)
	@$(CC) $(CLIENT_SRCS) -o $(CLIENT)

$(SERVER) : $(SERVER_SRCS)
	@$(CC) $(SERVER_SRCS) -o $(SERVER)

%.o : %.c
	@$(CC) $(FLAGS) $< -c

clean :
	@rm -f client.o server.o

fclean : clean
	@rm -f $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
