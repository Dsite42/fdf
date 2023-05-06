/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:05:59 by cgodecke          #+#    #+#             */
/*   Updated: 2023/05/06 18:34:01 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_row_length_equal(t_data *data, int i_row)
{
	if (arr_len(data->map_str[i_row]) != data->map_colunms)
		return (0);
	return (1);
}

static int	is_row_valid(t_data *data, int i, int j, int k)
{
	while (data->map_str[i][j][k] != ','
		&& data->map_str[i][j][k] != '\n' && data->map_str[i][j][k] != '\0')
	{
		if ((ft_isdigit(data->map_str[i][j][k]) == 0
			&& data->map_str[i][j][k] != '-') || (data->map_str[i][j][k] == '-'
			&& ft_isdigit(data->map_str[i][j][k + 1]) == 0))
			return (0);
		k++;
	}
	return (1);
}

// checks if the map coloumns have the same length and if
// the values are valid numbers. 
int	is_map_valid(t_data *data)
{
	int	i;
	int	j;
	int	k;

	if (data->map_colunms == 1)
		return (0);
	i = 0;
	while (data->map_str[i] != NULL)
	{
		j = 0;
		k = 0;
		if (data->map_str[i][j] == NULL)
			return (0);
		while (data->map_str[i][j] != NULL)
		{
			if (is_row_length_equal(data, i) == 0)
				return (0);
			k = 0;
			if (is_row_valid(data, i, j, k) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
