/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:02 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/27 11:05:15 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	of_free_two_d_arr((void ***)data->map_double, 1);
	of_free_two_d_arr((void ***)data->map_str, 1);
	//data->win_ptr = NULL;
	//data->img.mlx_img = NULL;
	exit (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
		if (x0 >= 0 && x0 < WINDOW_WIDTH && y0 >= 0 && y0 < WINDOW_HEIGHT)
			img_pix_put(&data->img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

double	max_distance(t_data *data, int axis)
{
	double	max;
	double min;
	int		i;
	int		j;

	i = 0;
	j = 0;
	max = DBL_MIN;
	min = DBL_MAX;

	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (data->map_double[i][j][axis] > max)
				max = data->map_double[i][j][axis];
			if (data->map_double[i][j][axis] < min)
				min = data->map_double[i][j][axis];
			j++;
		}
		j = 0;
		i++;
	}
	return (max - min);
}

double	scale_x(t_data *data, double x)
{
	double	scaled_x;

	scaled_x = ((WINDOW_WIDTH - max_distance(data, 0) * data->scale)
			/ 2) + data->scale * x + (max_distance(data, 0) * data->scale / 2) + data->shift_x;
	return (scaled_x);
}

double	scale_y(t_data *data, double y)
{
	double	scaled_y;

	scaled_y = ((WINDOW_HEIGHT - max_distance(data, 1) * data->scale)
			/ 2) + data->scale * y + data->shift_y;
	return (scaled_y);
}

void	render_row(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (j > 0)
				draw_line(data, scale_x(data, data->map_double[i][j - 1][0]),
					scale_y(data, data->map_double[i][j - 1][1]),
					scale_x(data, data->map_double[i][j][0]),
					scale_y(data, data->map_double[i][j][1]),
					data->map_double[i][j][3]);
			if (i > 0)
				draw_line(data, scale_x(data, data->map_double[i - 1][j][0]),
					scale_y(data, data->map_double[i - 1][j][1]),
					scale_x(data, data->map_double[i][j][0]),
					scale_y(data, data->map_double[i][j][1]),
					data->map_double[i][j][3]);
			j++;
		}
		j = 0;
		i++;
	}
}


int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLACK_PIXEL);
	render_row(data);
	
	//img_pix_put(&data->img, 1199, 100, RED_PIXEL);
	

	//render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	//render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	init_map(&data, argv[1]);
	isometric_transformation(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, 1*WINDOW_WIDTH, 1*WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &window_close, &data);
	//mlx_hook(data.win_ptr, FocusOut, 0, 0, &data);

	mlx_loop(data.mlx_ptr);

	//mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	//mlx_destroy_display(data.mlx_ptr);

	//free(data.mlx_ptr);
	//of_free_two_d_arr((void ***)data.map_double, 1);
	//of_free_two_d_arr((void ***)data.map_str, 1);
	return (0);
}