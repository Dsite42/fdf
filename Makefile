# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/04/26 11:35:26 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
#CC_FLAGS = -Wall -Wextra -Werror
OBJDIR = obj
INFILES = 	*.c\
				of/*.c
			
OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = fdf

all: setup $(NAME)

$(NAME): $(OBJFILES)
	cd libft && $(MAKE)
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME)  libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)/obj
	@mkdir -p $(OBJDIR)/list
	@mkdir -p $(OBJDIR)/of

clean:
	rm -f $(OBJFILES) $(BONUSOBJFILES)
	rm -r -f obj/
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	cd libft && $(MAKE) fclean
	
re: fclean all

.PHONY: all clean fclean setup re