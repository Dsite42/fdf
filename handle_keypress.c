/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:37 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/27 11:05:40 by cgodecke         ###   ########.fr       */
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
	j = 0;
	if (keysym == XK_w)
		alpha = 0.1;
	else
		alpha = -0.1;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			previous_y = data->map_double[i][j][1];
			data->map_double[i][j][1] = previous_y * cos(alpha)
				- data->map_double[i][j][2] * sin(alpha);
			data->map_double[i][j][2] = previous_y * sin(alpha)
				+ data->map_double[i][j][2] * cos(alpha);
			j++;
		}
		j = 0;
		i++;
	}
}

void	adjust_hight(int keysym, t_data *data)
{
	int	i;
	int	j;
	int	hight_change;

	i = 0;
	j = 0;
	if (keysym == XK_h)
		hight_change = 1;
	else
		hight_change = -1;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (*(data->map_str[i][j]) != '0')
			{
				data->map_double[i][j][1] -= hight_change;
				data->map_double[i][j][2] += hight_change;
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
	{
		window_close(data);
	}
	if (keysym == XK_plus)
	{
		data->scale += 1;
	int	i = 0;
	int	j = 0;
	while (data->map_double[j] != NULL)
	{
		while (i < data->map_colunms)
		{
			printf("x: %f\n", (data->map_double)[j][i][0]);
			printf("y: %f\n", (data->map_double)[j][i][1]);
			printf("z: %f\n", (data->map_double)[j][i][2]);
			i++;
		}
		i = 0;
		j++;
		printf("\n");
	}
	}
	if (keysym == XK_minus)
		data->scale -= 1;
	if (keysym == XK_Right)
		data->shift_x += 20;
	if (keysym == XK_Left)
		data->shift_x -= 20;
	if (keysym == XK_Up)
		data->shift_y -= 20;
	if (keysym == XK_Down)
		data->shift_y += 20;
	if (keysym == XK_h || keysym == XK_l)
		adjust_hight(keysym, data);
	if (keysym == XK_w || keysym == XK_s)
		rotate_x(keysym, data);
	return (0);
}
