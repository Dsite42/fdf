/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:02 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/29 20:56:43 by cgodecke         ###   ########.fr       */
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

void	calc_start_scale(t_data *data)
{
	double	max_distance_x;
	double	max_distance_y;

	max_distance_x = max_distance(data, 0);
	max_distance_y = max_distance(data, 1);
	data->scale = WINDOW_WIDTH * 0.8 / max_distance_x;
	if (WINDOW_HEIGHT * 0.8 / max_distance_y < data->scale)
		data->scale = WINDOW_HEIGHT * 0.8 / max_distance_y;
}

int	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error_start_mlx;

	if (argc != 2)
		return (0);
	init_map(&data, argv[1]);
	isometric_transformation(&data);
	calc_start_scale(&data);
	error_start_mlx = start_mlx(&data);
	if (error_start_mlx != 0)
		return (error_start_mlx);
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify,
		StructureNotifyMask, &window_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}