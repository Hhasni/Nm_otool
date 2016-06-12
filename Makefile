# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhasni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/09 06:28:32 by hhasni            #+#    #+#              #
#    Updated: 2015/07/09 06:28:32 by hhasni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_nm

NAMEB =		ft_otool

CPATH =		./

SRCS =		ft_error.c \
			ft_list.c \
			ft_mix.c \
			ft_mix2.c \
			ft_nm_main.c \
			ft_nm_hexa.c \
			ft_otool_main.c \
			ft_otool_hexa.c \
			ft_tools.c

OBJS =		$(SRCS:.c=.o)

CC =		clang

CFLAGS =	-Wall -Wextra -Werror

RM =		rm -rf

all:		$(NAME) $(NAMEB)

$(NAME):	$(OBJS)
			@echo "\n\r\033[38;5;11m⌛  MAKE $(NAME) plz wait...\033[0m\033[K"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo -en "\r\033[38;5;22m✅  MAKE $(NAME)\033[0m\033[K"
			@echo "💟"

$(NAMEB):	$(OBJS)
			@echo "\n\r\033[38;5;11m⌛  MAKE $(NAMEB) plz wait...\033[0m\033[K"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAMEB)
			@echo -en "\r\033[38;5;22m✅  MAKE $(NAMEB)\033[0m\033[K"
			@echo "💟"

%.o:		$(CPATH)%.c
			@$(CC) $(CFLAGS) -c $< 

clean:
			@$(RM) $(OBJS)
			@echo -en "\r\033[38;5;124m❌  CLEAN $(NAME) \033[0m\033[K"
			@echo -en "\r\033[38;5;124m❌  CLEAN $(NAMEB) \033[0m\033[K"

fclean:		clean
			@$(RM) $(NAME) $(NAMEB)
			@echo -en "\r\033[38;5;124m❌  FCLEAN $(NAME) \033[0m\033[K"
			@echo -en "\r\033[38;5;124m❌  FCLEAN $(NAMEB) \033[0m\033[K"

re:			fclean all
