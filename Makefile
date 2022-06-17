# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 15:59:06 by elehtora          #+#    #+#              #
#    Updated: 2022/06/17 14:09:34 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
### VARIABLES ###
################

NAME			= fillit

SRCDIR			= sources
SRCS			= \
				error.c \
				extract.c \
				file.c \
				main.c \
				solver.c
OBJS			= $(SRCS:.c=.o)
DIRS			= $(SRCDIR)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

INCL			= sources/fillit.h
INCLDIR			= sources

LIB				= ft
LIBDIR			= libft
LIB_BIN			= libft.a

RM				= /bin/rm -rf

#############
### RULES ###
#############

#.SILENT:

all : $(NAME)

$(NAME) : $(OBJS) $(LIBDIR)/$(LIB_BIN)
	@echo "\033[1;32mCreating binary $(NAME).\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBDIR) -l$(LIB) -o $(NAME)

%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -g -I$(INCLDIR) -c -o $@ $<

$(LIBDIR)/$(LIB_BIN) :
	cd $(LIBDIR) && $(MAKE) $(LIB_BIN) && cd ..

debug : $(OBJS)
	@echo "\033[1;32mCreating debug binary $(NAME).\033[0m"
	$(CC) -g $(OBJS) -L$(LIBDIR) -l$(LIB) -o $(NAME)

clean :
	@echo "\033[1;32mCleaning object files.\033[0m"
	$(RM) $(OBJS)

fclean : clean
	@echo "\033[1;32mCleaning binary and debug files.\033[0m"
	$(RM) $(NAME) *.dSYM

re : fclean all
