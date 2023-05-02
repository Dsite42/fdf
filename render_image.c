/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:43:20 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/01 19:46:48 by cgodecke         ###   ########.fr       */
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
	return (0);
}
