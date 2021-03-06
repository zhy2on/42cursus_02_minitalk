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
SERVER_OBJS = server.o utils.o

CLIENT = client
CLIENT_OBJS = client.o

all : $(SERVER) $(CLIENT)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT) : $(CLIENT_OBJS)
	@$(CC) $(CLIENT_OBJS) -o $(CLIENT)

$(SERVER) : $(SERVER_OBJS)
	@$(CC) $(SERVER_OBJS) -o $(SERVER)

clean :
	@rm -rf $(CLIENT_OBJS) $(SERVER_OBJS)

fclean : clean
	@rm -rf $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
