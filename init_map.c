
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

int	**transform_map_to_int(char ***map_str)
{
	int	**map_int;
	int	i;
	int	j;

	i = 0;
	map_int = (int **)malloc(sizeof(int *) * (two_d_arr_len(map_str) + 1));
	if (map_int == NULL)
		return (NULL);
	while (map_str[i] != NULL)
	{
		j = 0;
		map_int[i] = (int *)malloc(sizeof(int) * (arr_len(map_str[i]) + 1));
		if (map_int[i] == NULL)
			return (NULL);
		while (map_str[i][j] != NULL)
		{
			map_int[i][j] = ft_atoi(map_str[i][j]);
			j++;
		}
		map_int[i][j] = '\0';
		i++;
	}
	map_int[i] = NULL;
	return (map_int);
}

void	init_map(t_data	*data)
{
	data->map_str = init_map_str("test.fdf");
	data->map_colunms = arr_len(data->map_str[0]);
	data->map_rows = two_d_arr_len(data->map_str);
	data->map_int = transform_map_to_int(data->map_str);
}
