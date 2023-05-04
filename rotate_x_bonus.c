/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:28 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:27:39 by cgodecke         ###   ########.fr       */
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
