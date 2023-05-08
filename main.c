/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:02 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/08 14:26:54 by cgodecke         ###   ########.fr       */
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
	exit (0);
}

void	calc_start_scale(t_data *data)
{
	double	max_distance_x;
	double	max_distance_y;

	max_distance_x = max_distance(data, 0);
	max_distance_y = max_distance(data, 1);
	data->scale = data->win_width * 0.8 / max_distance_x;
	if (data->win_height * 0.8 / max_distance_y < data->scale)
		data->scale = data->win_height * 0.8 / max_distance_y;
}

int	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "my window");
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			data->win_width, data->win_height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->mlx_ptr == NULL || data->win_ptr == NULL
		|| data->img.mlx_img == NULL || data->img.addr == NULL)
	{
		if (data->mlx_ptr != NULL)
			free(data->mlx_ptr);
		if (data->win_ptr != NULL)
			free(data->win_ptr);
		if (data->img.mlx_img != NULL)
			free(data->img.mlx_img);
		if (data->img.addr != NULL)
			free(data->img.addr);
		of_free_two_d_arr((void ***)data->map_double, 1);
		of_free_two_d_arr((void ***)data->map_str, 1);
		perror("Error while initializing the mlx\n");
		exit (MLX_ERROR);
	}
	return (0);
}

void	zero_struct_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img = (t_img){NULL, NULL, 0, 0, 0};
	data->cur_img = 0;
	data->map_str = NULL;
	data->map_double = NULL;
	data->map_colunms = 0;
	data->map_rows = 0;
	data->max_distance_x = 0;
	data->max_distance_y = 0;
	data->highest_y = 0;
	data->scale = 0;
	data->shift_x = 0;
	data->shift_y = 0;
	data->x_rotation_rad = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		perror("Error: wrong number of arguments\n");
		return (0);
	}
	zero_struct_data(&data);
	init_map(&data, argv[1]);
	isometric_transformation(&data);
	calc_start_scale(&data);
	start_mlx(&data);
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify,
		StructureNotifyMask, &window_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
