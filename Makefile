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
SRCS			= file.c main.c solver.c error.c extract.c
UTILDIR			= tests/utils
UTILS			= print.c

OBJDIR			= objects
OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror

INCL			= ./sources/fillit.h ./tests/utils/utils.h
INCLDIR			= -I sources/ -I tests/utils/

LIB				= -lft
LIBDIR			= -Llib
LIB_BIN			= libft.a

RM				= /bin/rm -rf

#############
### RULES ###
#############

#.SILENT:

all : $(BIN)

$(OBJDIR)/%.o : $(SRCDIR)/$(SRCS) $(UTILS) $(INCL) $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLDIR) -o $@ -c $(SRCS) $(UTILS)

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIB) -o $(BIN)
	echo "Creating binary $(BIN)."

debug : $(OBJS)
	$(CC) -g $(OBJS) $(LIBDIR) $(LIB) -o $(BIN)
	@echo "Creating debug binary $(BIN)."

utils : $(OBJS) print.o
	$(CC) $(OBJS) $(UTILS) $(LIBDIR) $(LIB) -o $(BIN)
	@echo "Creating binary $(BIN) with test_utils."

$(OBJDIR) :
	-mkdir $(OBJDIR)

clean :
	$(RM) $(OBJS)
	@echo "Cleaning object files."

fclean : clean
	$(RM) $(BIN) *.dSYM
	@echo "Cleaning binary and debug files."

re : fclean all
