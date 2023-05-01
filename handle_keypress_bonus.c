/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:37 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/01 20:19:38 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int keysym, t_data *data)
{
	int		i;
	int		j;
	double	previous_y;
	double	alpha;

	i = 0;
	if (keysym == XK_w)
		alpha = 0.1;
	else
		alpha = -0.1;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			previous_y = data->map_double[i][j][1];
			data->map_double[i][j][1] = previous_y * cos(alpha)
				- data->map_double[i][j][2] * sin(alpha);
			data->map_double[i][j][2] = previous_y * sin(alpha)
				+ data->map_double[i][j][2] * cos(alpha);
			j++;
		}
		i++;
	}
	data->x_rotation_rad += alpha;
}

void	rotate_y(int keysym, t_data *data)
{
	int		i;
	int		j;
	double	previous_x;
	double	alpha;

	i = 0;
	if (keysym == XK_a)
		alpha = -0.1;
	else
		alpha = 0.1;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			previous_x = data->map_double[i][j][0];
			data->map_double[i][j][0] = previous_x * cos(alpha)
				+ data->map_double[i][j][2] * sin(alpha);
			data->map_double[i][j][2] = -previous_x * sin(alpha)
				+ data->map_double[i][j][2] * cos(alpha);
			j++;
		}
		i++;
	}
	data->y_rotation_rad += alpha;
}

void	set_map_to_original(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			data->map_double[i][j][0] = (double)j;
			data->map_double[i][j][1] = (double)i;
			data->map_double[i][j][2] = (double)ft_atoi(data->map_str[i][j]);
			j++;
		}
		i++;
	}
}

void 	parallel_projection(t_data *data)
{
	int		i;
	int		j;
	double	previous_y;
	double	alpha;

	i = 0;
	alpha = 1.5708;
	while (data->map_double[i] != NULL)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			previous_y = data->map_double[i][j][1];
			data->map_double[i][j][1] = previous_y * cos(alpha)
				- data->map_double[i][j][2] * sin(alpha);
			data->map_double[i][j][2] = previous_y * sin(alpha)
				+ data->map_double[i][j][2] * cos(alpha);
			j++;
		}
		i++;
	}
	data->x_rotation_rad += alpha;
}


void	adjust_hight(int keysym, t_data *data)
{
	int	i;
	int	j;
	double	hight_change;

	i = 0;
	j = 0;
	if (keysym == XK_h)
		hight_change = 2.0;
	else
		hight_change = 0.5;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (*(data->map_str[i][j]) != '0')
			{
				data->map_double[i][j][1] = data->map_double[i][j][1] - data->map_double[i][j][2] * (hight_change-1);
				data->map_double[i][j][2] = data->map_double[i][j][2] * hight_change;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		window_close(data);
	if (keysym == XK_plus)
	{
		data->scale += 1;
	//int	i = 0;
	//int	j = 0;
	//while (data->map_double[j] != NULL)
	//{
	//	while (i < data->map_colunms)
	//	{
	//		printf("x: %f\n", (data->map_double)[j][i][0]);
	//		printf("y: %f\n", (data->map_double)[j][i][1]);
	//		printf("z: %f\n", (data->map_double)[j][i][2]);
	//		i++;
	//	}
	//	i = 0;
	//	j++;
	//	printf("\n");
	printf("x_rotation_rad: %f mod_w: %i mod_s: %i\n", data->x_rotation_rad, (int)((data->x_rotation_rad - 1.5708)/3.14159)%2, (int)((data->x_rotation_rad + 1.5708)/-3.14159)%2);
//
//
	//}
	}
	if (keysym == XK_minus && data->scale > 1)
		data->scale -= 1;
	if (keysym == XK_Right)
		data->shift_x += 20;
	if (keysym == XK_Left)
		data->shift_x -= 20;
	if (keysym == XK_Up)
		data->shift_y -= 20;
	if (keysym == XK_Down)
		data->shift_y += 20;
	if (keysym == XK_o)
		set_map_to_original(data);
	if (keysym == XK_i)
		isometric_transformation(data);
	if (keysym == XK_p)
		parallel_projection(data);
	//if (keysym == XK_h || keysym == XK_l)
	//	adjust_hight(keysym, data);
	if (keysym == XK_w || keysym == XK_s)
		rotate_x(keysym, data);
	if (keysym == XK_a || keysym == XK_d)
		rotate_y(keysym, data);
	if (keysym == XK_h && data->show_help == 0)
		data->show_help = 1;
	else if (keysym == XK_h && data->show_help == 1)
		data->show_help = 0;
	return (0);
}
