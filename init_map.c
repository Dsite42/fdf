/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:04:27 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/06 18:26:28 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	two_d_arr_len(char ***arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	define_window_size(t_data *data)
{
	if (data->map_colunms < 100 || data->map_rows < 100)
	{
		data->win_width = 800;
		data->win_height = 400;
	}
	else if (data->map_colunms < 200 || data->map_rows < 200)
	{
		data->win_width = 1200;
		data->win_height = 800;
	}
	else
	{
		data->win_width = 1800;
		data->win_height = 1200;
	}
}

void	init_map(t_data	*data, char *file_path)
{
	data->map_str = init_map_str(file_path);
	if (data->map_str == NULL)
	{
		perror("No file found or empty\n");
		exit(FILE_ERROR);
	}
	data->map_colunms = arr_len(data->map_str[0]);
	data->map_rows = two_d_arr_len(data->map_str);
	if (is_map_valid(data) == 0)
	{
		of_free_two_d_arr((void ***)data->map_str, 1);
		perror("Invalid map\n");
		exit(MAP_ERROR);
	}
	data->map_double = transform_map_to_int(data->map_str);
	data->shift_x = 0;
	data->shift_y = 0;
	data->x_rotation_rad = 0;
	define_window_size(data);
}
