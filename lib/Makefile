# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 15:27:40 by elehtora          #+#    #+#              #
#    Updated: 2022/05/20 16:20:11 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES

NAME = libft.a

SRCS		=	ft_alphabetize.c	\
				ft_atoi.c			\
				ft_bzero.c			\
				ft_del.c			\
				ft_count_digs.c		\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_islower.c		\
				ft_isprint.c		\
				ft_isupper.c		\
				ft_iswhite.c		\
				ft_itoa.c			\
				ft_lstadd.c			\
				ft_lstcpyone.c		\
				ft_lstdel.c			\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_memalloc.c		\
				ft_memccpy.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memdel.c			\
				ft_memmove.c		\
				ft_memrchr.c		\
				ft_memset.c			\
				ft_putchar.c		\
				ft_putchar_fd.c		\
				ft_putendl.c		\
				ft_putendl_fd.c		\
				ft_putmem.c			\
				ft_putnbr.c			\
				ft_putnbr_fd.c		\
				ft_putstr.c			\
				ft_putstr_fd.c		\
				ft_strcat.c			\
				ft_strchr.c			\
				ft_strclr.c			\
				ft_strrclr.c		\
				ft_strcmp.c			\
				ft_strcpy.c			\
				ft_strdel.c			\
				ft_strdup.c			\
				ft_strequ.c			\
				ft_striter.c		\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strlen.c			\
				ft_strmap.c			\
				ft_strmapi.c		\
				ft_strncat.c		\
				ft_strncmp.c		\
				ft_strncpy.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_strnequ.c		\
				ft_strnew.c			\
				ft_strnlen.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strsep.c			\
				ft_strsplit.c		\
				ft_strstr.c			\
				ft_strsub.c			\
				ft_strtrim.c		\
				ft_tolower.c		\
				ft_toupper.c

OBJS = $(SRCS:.c=.o)

CC=clang
CFLAGS = -c -Wall -Wextra -Werror
LIB=ar rcs
RM=/bin/rm -f

# RULES

all : $(NAME)

$(NAME) : $(SRCS)
	@echo "Compiling library $(NAME)..."
	@$(CC) $(CFLAGS) $(SRCS)
	@$(LIB) $(NAME) $(OBJS)

clean :
	@echo "Cleaning..."
	@$(RM) $(OBJS)

fclean : clean
	@echo "Cleaning $(NAME)..."
	@$(RM) $(NAME)

re : fclean all
