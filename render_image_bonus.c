/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:43:20 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/01 19:51:47 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_background(t_data *data, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->win_height)
	{
		j = 0;
		while (j < data->win_width)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

static void	render_rows(t_data *data)
{
	int		i;
	int		j;
	t_line	line_val;

	i = 0;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			if (j > 0)
			{
				line_val.direction = 0;
				draw_line(data, &line_val, i, j);
			}
			if (i > 0)
			{
				line_val.direction = 1;
				draw_line(data, &line_val, i, j);
			}
			j++;
		}
		i++;
	}
}

double	lowest_x(t_data *data)
{
	int		i;
	int		j;
	double	lowest_x;

	i = 0;
	lowest_x = DBL_MAX;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			if (data->map_double[i][j][0] < lowest_x)
				lowest_x = data->map_double[i][j][0];
			j++;
		}
		i++;
	}
	return (lowest_x);
}

static void	show_help(t_data *data)
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
	mlx_string_put(a, b, 10, 210, gp, "Press '+' to zoom in");
	mlx_string_put(a, b, 10, 230, gp, "Press '-' to zoom out");
	mlx_string_put(a, b, 10, 250, gp, "Press 'up' to move up");
	mlx_string_put(a, b, 10, 270, gp, "Press 'down' to move down");
	mlx_string_put(a, b, 10, 290, gp, "Press 'left' to move left");
	mlx_string_put(a, b, 10, 310, gp, "Press 'right' to move right");
}	

int	render_image(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(data, &data->img, BLACK_PIXEL);
	data->max_distance_x = max_distance(data, 0);
	data->max_distance_y = max_distance(data, 1);
	data->highest_y = highest_y(data);
	data->lowest_x = lowest_x(data);
	render_rows(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, GREEN_PIXEL,
		"Press 'h' to see possible controls");
	if (data->show_help == 1)
		show_help(data);
	return (0);
}
