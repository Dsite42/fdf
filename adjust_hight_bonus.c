/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_hight_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:42:09 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:54:07 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	iso_hight(t_data *data, int keysym, int i, int j)
{
	double	hight_change;

	if (keysym == XK_k)
		hight_change = 1.2;
	else
		hight_change = 0.83;
	data->map_double[i][j][1] = data->map_double[i][j][1]
		- data->map_double[i][j][2] * (hight_change - 1);
	data->map_double[i][j][2] = data->map_double[i][j][2] * hight_change;
}

static void	parallel_hight(t_data *data, int keysym, int i, int j)
{
	double	hight_change;

	hight_change = 0.2;
	if (keysym == XK_k)
		data->map_double[i][j][1] += data->map_double[i][j][1] * hight_change;
	else
		data->map_double[i][j][1] -= data->map_double[i][j][1] * hight_change;
}

static void	ori_hight(t_data *data, int keysym, int i, int j)
{
	double	hight_change;

	if (keysym == XK_k)
	{
		hight_change = 1.2;
		data->map_double[i][j][2] = data->map_double[i][j][2] * hight_change;
	}
	else
	{
		hight_change = 0.83;
		data->map_double[i][j][2] = data->map_double[i][j][2] * hight_change;
	}
}

void	adjust_hight(int keysym, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_double[i] != NULL )
	{
		j = 0;
		while (j < data->map_colunms)
		{
			if (*(data->map_str[i][j]) != '0')
			{
				if (data->view == 'i' && data->x_rotation_rad == 0
					&& data->y_rotation_rad == 0)
					iso_hight(data, keysym, i, j);
				else if (data->view == 'o' && data->x_rotation_rad == 0
					&& data->y_rotation_rad == 0)
					ori_hight(data, keysym, i, j);
				else if (data->view == 'p' && data->x_rotation_rad == 1.5708
					&& data->y_rotation_rad == 0)
					parallel_hight(data, keysym, i, j);
			}
			j++;
		}
		i++;
	}
}
