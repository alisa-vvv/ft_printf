# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:39:24 by avaliull          #+#    #+#              #
#    Updated: 2024/10/26 15:55:58 by avaliull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES	=	ft_printf.c\
			ft_utoa.c\
			printf_conv_s%cidu.c
#			printf_conversions_02.c

OFILES	= $(CFILES:.c=.o)

LIBFT	= libft/libft.a

LIBFTDIR = libft

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

AR	= ar -rcs

LIBFTALL	= all

NAME	= libftprintf.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):	
	$(MAKE) all -C $(LIBFTDIR)

$(NAME): $(OFILES) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OFILES)

libft_clean:
	$(MAKE) clean -C $(LIBFTDIR)

clean: libft_clean
	$(RM) $(OFILES)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re libft_clean libft_bonus