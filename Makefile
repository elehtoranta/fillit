# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:59:06 by elehtora          #+#    #+#              #
#    Updated: 2022/06/06 11:39:19 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
### VARIABLES ###
################

NAME			= fillit

SRCDIR			= sources
SRCS			:= $(shell find $(SRCDIR) -name '*.c')

OBJS			= $(SRCS:.c=.o)
CC				= clang
CFLAGS			= -Wall -Wextra -Werror

INCL			= sources
LIB				= -lft
LIBDIR			= -Llib

RM				= /bin/rm -rf

#############
### RULES ###
#############

.SILENT:

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIB) -o $(NAME)
	echo "Creating binary $(NAME)."

$(SRCDIR)/%.o : %.c
	$(CC) $(CFLAGS) -I$(INCL) -c $<

debug :
	$(CC) -g $(SRCS) -I$(INCL) $(LIBDIR) $(LIB) -o $(NAME)
	@echo "Creating debug binary $(NAME)."

clean :
	$(RM) $(OBJS)
	@echo "Cleaning object files."

fclean : clean
	$(RM) $(NAME) *.dSYM
	@echo "Cleaning binary and debug files."

re : fclean all
