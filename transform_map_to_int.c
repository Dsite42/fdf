/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map_to_int.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:22:16 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/05 11:53:05 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	transform_row_to_int(double	***map_double, char ***map_str, int i, int *j)
{
	while (map_str[i][*j] != NULL)
	{
		map_double[i][*j] = (double *)malloc(sizeof(double) * 4);
		if (map_double[i][*j] == NULL)
			return (1);
		map_double[i][*j][0] = (double)*j;
		map_double[i][*j][1] = (double)i;
		map_double[i][*j][2] = (double)ft_atoi(map_str[i][*j]);
		if (ft_strchr(map_str[i][*j], ',') != NULL)
		{
			of_str_to_lower(map_str[i][*j]);
			map_double[i][*j][3] = (double)abs(
					of_atoi_base(ft_strchr(map_str[i][*j], ',')
						+ 3, "0123456789abcdef"));
		}
		else
			map_double[i][*j][3] = WHITE_PIXEL;
		*j = *j + 1;
	}
	return (0);
}

double	***transform_map_to_int(char ***map_str)
{
	double	***map_double;
	int		i;
	int		j;

	i = 0;
	map_double = (double ***)malloc(sizeof(double **)
			* (two_d_arr_len(map_str) + 1));
	if (map_double == NULL)
		return (NULL);
	while (map_str[i] != NULL)
	{
		j = 0;
		map_double[i] = (double **)malloc(sizeof(double *)
				* (arr_len(map_str[i]) + 1));
		if (map_double[i] == NULL)
			return (NULL);
		if (transform_row_to_int(map_double, map_str, i, &j) == 1)
			return (NULL);
		map_double[i][j] = NULL;
		i++;
	}
	map_double[i] = NULL;
	return (map_double);
}
