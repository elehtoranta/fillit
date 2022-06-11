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

BIN				= fillit

SRCDIR			= sources
SRCS			= \
				error.c \
				extract.c \
				file.c \
				main.c \
				print.c \
				solver.c
OBJDIR			= objects
OBJS			= $(SRCS:.c=.o)
DIRS			= $(SRCDIR) $(OBJDIR)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

INCL			= sources/fillit.h
INCLDIR			= -I sources/

LIB				= -lft
LIBDIR			= -Llib
LIB_BIN			= libft.a

RM				= /bin/rm -rf

#############
### RULES ###
#############

#.SILENT:

all : $(BIN) $(DIRS)

$(BIN) : $(OBJS)
	@echo "\033[1;32mCreating binary $(BIN).\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIB) -o $(BIN)

%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLDIR) -c -o $@ $<

debug : $(OBJS)
	@echo "\033[1;32mCreating debug binary $(BIN).\033[0m"
	$(CC) -Wall -g $(OBJS) $(LIBDIR) $(LIB) -o $(BIN)

clean :
	@echo "\033[1;32mCleaning object files.\033[0m"
	$(RM) $(OBJS)

fclean : clean
	@echo "\033[1;32mCleaning binary and debug files.\033[0m"
	$(RM) $(BIN) *.dSYM

re : fclean all
