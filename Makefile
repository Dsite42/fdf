# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/04/29 17:56:01 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc -g
CC_FLAGS = -Wall -Wextra -Werror
OBJDIR = obj
INFILES = 	of/of_arr_len.c\
			of/of_atoi_base.c\
			of/of_free_arr.c\
			of/of_free_two_d_arr.c\
				handle_keypress.c\
				init_map.c\
				transform_map_to_int.c\
				init_map_str.c\
				main.c\
				highest_y.c\
				is_map_valid.c\
				draw_line.c\
				img_pix_put.c\
				isometric_transformation.c\
				max_distance.c\
				render_image.c\

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

BONUSFILES = 	of/of_arr_len.c\
				of/of_atoi_base.c\
				of/of_free_arr.c\
				of/of_free_two_d_arr.c\
				init_map.c\
				transform_map_to_int.c\
				init_map_str.c\
				main.c\
				highest_y.c\
				is_map_valid.c\
				draw_line.c\
				img_pix_put.c\
				isometric_transformation.c\
				max_distance.c\
				render_image.c\
					handle_keypress_bonus.c\

BONUSOBJFILES = $(BONUSFILES:%.c=$(OBJDIR)/%.o)

NAME = fdf

all: setup $(NAME)

$(NAME): $(OBJFILES)
	cd libft && $(MAKE)
#cd minilibx-linux && $(MAKE)
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm
#$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -I/usr/include/X11 -L/usr/lib/X11 -lX11 -lXext -lm



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
#cd minilibx-linux && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	cd libft && $(MAKE) fclean

bonus: all $(BONUSOBJFILES)
	$(CC) $(CC_FLAGS) $(BONUSOBJFILES) -o $(NAME) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

re: fclean all

.PHONY: all clean fclean setup bonus re