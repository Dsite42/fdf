
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
			map_double[i][j]= (double *)malloc(sizeof(double) * 3);
			if (map_double[i][j] == NULL)
				return (NULL);
			map_double[i][j][0] = (double)j;
			map_double[i][j][1] = (double)i;
			map_double[i][j][2] = (double)ft_atoi(map_str[i][j]);
			j++;
		}
		map_double[i][j] = NULL;
		i++;
	}
	map_double[i] = NULL;
	return (map_double);
}

void	init_map(t_data	*data, char *file_path)
{
	data->file_path = file_path;
	data->map_str = init_map_str(file_path);
	data->map_colunms = arr_len(data->map_str[0]);
	data->map_rows = two_d_arr_len(data->map_str);
	data->map_double = transform_map_to_int(data->map_str);
	data->scale = 10;
	data->shift_x = 0;
	data->shift_y = 0;

}
