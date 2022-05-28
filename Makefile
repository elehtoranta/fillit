# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:59:06 by elehtora          #+#    #+#              #
#    Updated: 2022/05/20 18:34:22 by Erkka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
### VARIABLES ###
################

NAME			= fillit

SRCDIR			= sources/
SRCS			:= $(shell find $(SRCDIR) -name '*.c')

OBJS			= $(SRCS:.c=.o)
CC				= clang
CFLAGS			= -Wall -Wextra -Werror

INCL			= sources/
LIB				= -lft
LIBDIR			= -Llib

RM				= /bin/rm -rf

#############
### RULES ###
#############

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIB) -o $(NAME)

$(SRCDIR)/%.o : %.c
	$(CC) $(CFLAGS) -I$(INCL) -c $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all