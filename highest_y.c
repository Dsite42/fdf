/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highest_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:56:45 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/29 18:57:38 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	highest_y(t_data *data)
{
	int		i;
	int		j;
	double	highest_y;

	i = 0;
	highest_y = DBL_MIN;
	while (i < data->map_rows)
	{
		j = 0;
		while (j < data->map_colunms)
		{
			if (data->map_double[i][j][1] < highest_y)
				highest_y = data->map_double[i][j][1];
			++j;
		}
		++i;
	}
	return (highest_y);
}
