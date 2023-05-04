/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_y.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:54:23 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 11:54:45 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
