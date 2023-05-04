/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:37 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:10:47 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	data->x_rotation_rad = 0;
	data->y_rotation_rad = 0;
	data->view = 'o';
}

void	parallel_projection(t_data *data)
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
	data->view = 'p';
}

void	keypress_map_manipulation(int keysym, t_data *data)
{
	if (keysym == XK_o)
		set_map_to_original(data);
	else if (keysym == XK_i)
		isometric_transformation(data);
	else if (keysym == XK_p)
		parallel_projection(data);
	else if (keysym == XK_k || keysym == XK_l)
		adjust_hight(keysym, data);
	else if (keysym == XK_w || keysym == XK_s)
		rotate_x(keysym, data);
	else if (keysym == XK_a || keysym == XK_d)
		rotate_y(keysym, data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		window_close(data);
	else if (keysym == XK_plus)
		data->scale += 1;
	else if (keysym == XK_minus && data->scale > 1)
		data->scale -= 1;
	else if (keysym == XK_Right)
		data->shift_x += 20;
	else if (keysym == XK_Left)
		data->shift_x -= 20;
	else if (keysym == XK_Up)
		data->shift_y -= 20;
	else if (keysym == XK_Down)
		data->shift_y += 20;
	else if (keysym == XK_h && data->show_help == 0)
		data->show_help = 1;
	else if (keysym == XK_h && data->show_help == 1)
		data->show_help = 0;
	else
		keypress_map_manipulation(keysym, data);
	return (0);
}
