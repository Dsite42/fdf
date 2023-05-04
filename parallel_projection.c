/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:59:00 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:28:26 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
}
