# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:59:06 by elehtora          #+#    #+#              #
#    Updated: 2022/05/18 16:32:37 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
### VARIABLES ###
################

NAME			= fillit

SRCS_DIR		= sources/
SRCS			= main.c verify.c
OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror

INCL			= includes/
LIB				= ft

RM				= /bin/rm -rf

#############
### RULES ###
#############

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(SRCS) $< -c

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
