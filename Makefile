# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:59:06 by elehtora          #+#    #+#              #
#    Updated: 2022/06/10 17:18:14 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
### VARIABLES ###
################

NAME			= fillit

SRCDIR			= sources
SRCS			:= $(shell find $(SRCDIR) -name '*.c')
UTILDIR			= tests/utils
UTILS			:= $(shell find $(UTILDIR) -name '*.c')

OBJS			= $(SRCS:.c=.o)
CC				= clang
CFLAGS			= -Wall -Wextra -Werror

INCL			= -Isources -Itests/utils

LIB				= -lft
LIBDIR			= -Llib
LIB_BIN			= libft.a

RM				= /bin/rm -rf

#############
### RULES ###
#############

#.SILENT:

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIB) -o $(NAME)
	echo "Creating binary $(NAME)."

$(SRCDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCL) -c $<

debug : $(OBJS)
	$(CC) -g $(SRCS) $(INCL) $(LIBDIR) $(LIB) -o $(NAME)
	@echo "Creating debug binary $(NAME)."

utils :
	$(CC) -g $(SRCS) $(UTILS) $(INCL) $(LIBDIR) $(LIB) -o $(NAME)
	@echo "Creating debug binary with test_utils $(NAME)."

clean :
	$(RM) $(OBJS)
	@echo "Cleaning object files."

fclean : clean
	$(RM) $(NAME) *.dSYM
	@echo "Cleaning binary and debug files."

re : fclean all
