/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:13:16 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/04 12:28:58 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	max_distance(t_data *data, int axis)
{
	double	max;
	double	min;
	int		i;
	int		j;

	i = 0;
	j = 0;
	max = DBL_MIN;
	min = DBL_MAX;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (data->map_double[i][j][axis] > max)
				max = data->map_double[i][j][axis];
			if (data->map_double[i][j][axis] < min)
				min = data->map_double[i][j][axis];
			j++;
		}
		j = 0;
		i++;
	}
	return (max - min);
}
