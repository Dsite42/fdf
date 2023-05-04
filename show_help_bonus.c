/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_help_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:18:08 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:20:04 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_more_help(t_data *data)
{
	void	*a;
	void	*b;
	int		gp;

	a = data->mlx_ptr;
	b = data->win_ptr;
	gp = GREEN_PIXEL;
	mlx_string_put(a, b, 10, 250, gp, "Press '+' to zoom in");
	mlx_string_put(a, b, 10, 270, gp, "Press '-' to zoom out");
	mlx_string_put(a, b, 10, 290, gp, "Press 'up' to move up");
	mlx_string_put(a, b, 10, 310, gp, "Press 'down' to move down");
	mlx_string_put(a, b, 10, 330, gp, "Press 'left' to move left");
	mlx_string_put(a, b, 10, 350, gp, "Press 'right' to move right");
}

void	show_help(t_data *data)
{
	void	*a;
	void	*b;
	int		gp;

	a = data->mlx_ptr;
	b = data->win_ptr;
	gp = GREEN_PIXEL;
	mlx_string_put(a, b, 10, 30, gp, "Press 'esc' to exit");
	mlx_string_put(a, b, 10, 50, gp, "Press 'h' to hide this message");
	mlx_string_put(a, b, 10, 70, gp,
		"Press 'o' to reset the map and see top view");
	mlx_string_put(a, b, 10, 90, gp,
		"Press 'p' to switch to parallel projection");
	mlx_string_put(a, b, 10, 110, gp, "Press 'i' to switch to isometric view");
	mlx_string_put(a, b, 10, 130, gp, "Press 'w' to rotate up");
	mlx_string_put(a, b, 10, 150, gp, "Press 's' to rotate down");
	mlx_string_put(a, b, 10, 170, gp, "Press 'a' to rotate left");
	mlx_string_put(a, b, 10, 190, gp, "Press 'd' to rotate right");
	mlx_string_put(a, b, 10, 210, gp, "Press 'k' to increase hight");
	mlx_string_put(a, b, 10, 230, gp, "Press 'l' to decrease hight");
	show_more_help(data);
}	
