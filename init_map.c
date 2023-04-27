/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:04:27 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/27 14:35:30 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	two_d_arr_len(char ***arr)
{
	int i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	***add_line_to_map(char ***map, char **splitted_line)
{
	char	***new_map;
	int		i;

	i = 0;
	new_map = (char ***)malloc(sizeof(char **) * (two_d_arr_len(map) + 2));
	if (new_map == NULL)
		return (NULL);
	if (map != NULL)
	{
		while (map[i] != NULL)
		{
			new_map[i] = map[i];
			i++;
		}
		free(map);
	}
	new_map[i] = splitted_line;
	new_map[i + 1] = NULL;
	return (new_map);
}

char	***init_map_str(char *file)
{
	char	***map;
	char	*new_line;
	int		fd;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	new_line = get_next_line(fd);
	while (new_line != NULL)
	{
		map = add_line_to_map(map, ft_split(new_line, ' '));
		free(new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

double	find_abs_max_z(t_data *data)
{
	int		i;
	int		j;
	double	max_abs_z;

	i = 0;
	j = 0;
	max_abs_z = 0;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			if (fabs(data->map_double[i][j][2]) > max_abs_z)
				max_abs_z = fabs(data->map_double[i][j][2]);
			j++;
		}
		j = 0;
		i++;
	}
	return (max_abs_z);
}

void	normalize_z(t_data *data)
{
	int		i;
	int		j;
	double	max_abs_z;

	i = 0;
	j = 0;
	max_abs_z = find_abs_max_z(data);
	if(max_abs_z != 0)
	{
		printf("max_abs_z: %f\n", max_abs_z);
		while (data->map_double[i] != NULL)
		{
			while (j < data->map_colunms)
			{
				data->map_double[i][j][2] = data->map_double[i][j][2] / max_abs_z;
				j++;
			}
			j = 0;
			i++;
	}
	}
}


double	***transform_map_to_int(char ***map_str)
{
	double	***map_double;
	int	i;
	int	j;

	i = 0;

	map_double = (double ***)malloc(sizeof(double **) * (two_d_arr_len(map_str) + 1));
	if (map_double == NULL)
		return (NULL);
	while (map_str[i] != NULL)
	{
		j = 0;
		map_double[i] = (double **)malloc(sizeof(double *) * (arr_len(map_str[i]) + 1));
		if (map_double[i] == NULL)
			return (NULL);
		while (map_str[i][j] != NULL)
		{
			map_double[i][j] = (double *)malloc(sizeof(double) * 4);
			if (map_double[i][j] == NULL)
				return (NULL);
			map_double[i][j][0] = (double)j;
			map_double[i][j][1] = (double)i;
			map_double[i][j][2] = (double)ft_atoi(map_str[i][j]);
			if (ft_strchr(map_str[i][j], ',') != NULL)
			printf("test: %i\n", of_atoi_base(ft_strchr(map_str[i][j], ',') + 3, "0123456789ABCDEF"));
			if (ft_strchr(map_str[i][j], ',') != NULL)
				map_double[i][j][3] = (double)abs(of_atoi_base(ft_strchr(map_str[i][j], ',') + 3, "0123456789ABCDEF"));
			else
				map_double[i][j][3] = WHITE_PIXEL;
			j++;
		}
		map_double[i][j] = NULL;
		i++;
	}
	map_double[i] = NULL;
	return (map_double);
}

// checks if the map coloumns have the same length and if the values are valid numbers. 
int	is_map_valid(t_data *data)
{
	int	i;
	int	j;
	int k;
	int	map_coloumns;

	i = 0;
	j = 0;
	map_coloumns = arr_len(data->map_str[0]);
	while (data->map_str[i] != NULL)
	{
		while (data->map_str[i][j] != NULL)
		{
			if (arr_len(data->map_str[i]) != map_coloumns)
			{
				if (data->map_str[i][arr_len(data->map_str[i])] != NULL)
					return (0);
			}
			k = 0;
			while (data->map_str[i][j][k] != ',' && data->map_str[i][j][k] != '\n' && data->map_str[i][j][k] != '\0' )
			{
				if (ft_isdigit(data->map_str[i][j][k]) == 0)
					return (0);
				k++;
			}			
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	init_map(t_data	*data, char *file_path)
{
	data->file_path = file_path;
	data->map_str = init_map_str(file_path);
	if(data->map_str == NULL || is_map_valid(data) == 0)
	{
		ft_printf("Invalid map\n");
		exit(0);
	}
	data->map_colunms = arr_len(data->map_str[0]);
	data->map_rows = two_d_arr_len(data->map_str);
	data->map_double = transform_map_to_int(data->map_str);
	normalize_z(data);
	data->scale = 10;
	data->shift_x = 0;
	data->shift_y = 0;
	data->x_rotation_rad = -1.5708;

}
