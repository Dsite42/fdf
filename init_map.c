/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:04:27 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/01 14:00:35 by cgodecke         ###   ########.fr       */
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

static double	find_abs_max_z(t_data *data)
{
	int		i;
	int		j;
	double	max_abs_z;

	i = 0;
	j = 0;
	max_abs_z = 0;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (fabs(data->map_double[i][j][2]) > max_abs_z)
				max_abs_z = fabs(data->map_double[i][j][2]);
			j++;
		}
		j = 0;
		i++;
	}
	return (max_abs_z);
}

static void	normalize_z(t_data *data)
{
	int		i;
	int		j;
	double	max_abs_z;

	i = 0;
	j = 0;
	max_abs_z = find_abs_max_z(data);
	if (max_abs_z != 0)
	{
		//printf("max_abs_z: %f\n", max_abs_z);
		while (data->map_double[i] != NULL)
		{
			while (j < data->map_colunms)
			{
				data->map_double[i][j][2]
					= data->map_double[i][j][2] / max_abs_z;
				j++;
			}
			j = 0;
			i++;
		}
	}
}

void	init_map(t_data	*data, char *file_path)
{
	data->map_str = init_map_str(file_path);
	if (data->map_str == NULL || is_map_valid(data) == 0)
	{
		if (data->map_str == NULL)
			ft_printf("No file found or empty\n");
		else
		{
			of_free_two_d_arr((void ***)data->map_str, 1);
			ft_printf("Invalid map\n");
		}
		exit(0);
	}
	data->map_colunms = arr_len(data->map_str[0]);
	data->map_rows = two_d_arr_len(data->map_str);

	data->map_double = transform_map_to_int(data->map_str);
	normalize_z(data);
	//printf("scale: %f\n", data->scale);
	data->shift_x = 0;
	data->shift_y = 0;
	data->x_rotation_rad = 0;
}
