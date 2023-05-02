/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:52:11 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/01 20:22:46 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//double	scale_x(t_data *data, double x)
//{
//	double	scaled_x;
//
//	//scaled_x = ((WINDOW_WIDTH - data->max_distance_x * data->scale)
//	//		/ 2) + data->scale * x + (data->max_distance_x * data->scale / 2) + data->shift_x;
//	scaled_x = WINDOW_WIDTH / 2 + data->scale * x
//		+ fabs((data->map_double[data->map_rows - 1][0][0] * data->scale))
//		- (data->max_distance_x * data->scale / 2) + data->shift_x ;
//	return (scaled_x);
//}

double	scale_x(t_data *data, double x)
{
	double	scaled_x;

	scaled_x = (fabs(data->lowest_x) * data->scale) + ((data->win_width - data->max_distance_x * data->scale) / 2) + data->scale * x + data->shift_x;
	return (scaled_x);
}
double	scale_y(t_data *data, double y)
{
	double	scaled_y;

	scaled_y = (fabs(data->highest_y) * data->scale) + ((data->win_height - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//if (data->x_rotation_rad < 1.5708 && data->x_rotation_rad >= 0)
	//	scaled_y = (fabs(data->highest_y) * data->scale) + ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//else if ((data->x_rotation_rad > 0 && (int)((data->x_rotation_rad - 1.5708)/3.14159)%2 < 1))
	//	scaled_y = (fabs(data->highest_y) * data->scale) + ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//else if (data->x_rotation_rad > 0 && data->x_rotation_rad > 1.5708)
	//	scaled_y = (fabs(data->highest_y) * data->scale) + ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//else if (data->x_rotation_rad > -1.5708 && data->x_rotation_rad <= 0)
	//	scaled_y = (fabs(data->highest_y) * data->scale) - ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//else if ((data->x_rotation_rad < 0 && (int)((data->x_rotation_rad + 1.5708)/-3.14159)%2 < 1))
	//	scaled_y = (-fabs(data->highest_y) * data->scale) + ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;
	//else if (data->x_rotation_rad < 0 && data->x_rotation_rad > -1.5708)
	//	scaled_y = (-fabs(data->highest_y) * data->scale) + ((WINDOW_HEIGHT - data->max_distance_y * data->scale) / 2) + data->scale * y + data->shift_y;

	//if (data->x_rotation_rad < 1.5708 && data->x_rotation_rad >= 0)
	//	scaled_y = ((WINDOW_HEIGHT - data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;
	//else if ((data->x_rotation_rad > 0 && (int)((data->x_rotation_rad - 1.5708)/3.14159)%2 < 1))
	//	scaled_y = ((WINDOW_HEIGHT + data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;
	//else if (data->x_rotation_rad > 0 && data->x_rotation_rad > 1.5708)
	//	scaled_y = ((WINDOW_HEIGHT - data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;

	//else if (data->x_rotation_rad > -1.5708 && data->x_rotation_rad <= 0)
	//	scaled_y = ((WINDOW_HEIGHT - data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;
	//else if (((int)((data->x_rotation_rad + 1.5708)/-3.14159)%2 < 1 && data->x_rotation_rad < 0))
	//	scaled_y = ((WINDOW_HEIGHT + data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;
	//else if (data->x_rotation_rad < 0 && data->x_rotation_rad < -1.5708)
	//	scaled_y = ((WINDOW_HEIGHT - data->max_distance_y * data->scale)
	//			/ 2) + data->scale * y + data->shift_y;

	return (scaled_y);
}

static void	set_line_val(t_data *data, t_line *line_val, int i, int j)
{
	if (j > 0 && line_val->direction == 0)
	{
		line_val->x0 = scale_x(data, data->map_double[i][j - 1][0]);
		line_val->y0 = scale_y(data, data->map_double[i][j - 1][1]);
		line_val->x1 = scale_x(data, data->map_double[i][j][0]);
		line_val->y1 = scale_y(data, data->map_double[i][j][1]);
		line_val->color = data->map_double[i][j][3];
	}
	if (i > 0 && line_val->direction == 1)
	{
		line_val->x0 = scale_x(data, data->map_double[i - 1][j][0]);
		line_val->y0 = scale_y(data, data->map_double[i - 1][j][1]);
		line_val->x1 = scale_x(data, data->map_double[i][j][0]);
		line_val->y1 = scale_y(data, data->map_double[i][j][1]);
		line_val->color = data->map_double[i][j][3];
	}
}

static void	set_start_calc(t_line *line_val)
{
	line_val->dx = abs(line_val->x1 - line_val->x0);
	if (line_val->x0 < line_val->x1)
		line_val->sx = 1;
	else
		line_val->sx = -1;
	line_val->dy = -abs(line_val->y1 - line_val->y0);
	if (line_val->y0 < line_val->y1)
		line_val->sy = 1;
	else
		line_val->sy = -1;
	line_val->err = line_val->dx + line_val->dy;
}

void	draw_line(t_data *data, t_line *line_val, int i, int j)
{
	set_line_val(data, line_val, i, j);
	set_start_calc(line_val);
	while (1)
	{
		if (line_val->x0 >= 0 && line_val->x0 < data->win_width
			&& line_val->y0 >= 0 && line_val->y0 < data->win_height)
			img_pix_put(&data->img, line_val->x0,
				line_val->y0, line_val->color);
		if (line_val->x0 == line_val->x1 && line_val->y0 == line_val->y1)
			break ;
		line_val->e2 = 2 * line_val->err;
		if (line_val->e2 > line_val->dy)
		{
			line_val->err += line_val->dy;
			line_val->x0 += line_val->sx;
		}
		if (line_val->e2 < line_val->dx)
		{
			line_val->err += line_val->dx;
			line_val->y0 += line_val->sy;
		}
	}
}
