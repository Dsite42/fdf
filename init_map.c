
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

int	arr_len(char **arr)
{
	int i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char***	add_line_to_map(char ***map, char **splitted_line)
	{
		char ***new_map;
		int i;

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

char *** init_map_str(char *file)
{
	char ***map;
	char *new_line;
	int fd;
	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	new_line = get_next_line(fd);
	while (new_line != NULL)
	{
		map = add_line_to_map(map, ft_split(new_line, ' '));
		new_line = get_next_line(fd);
	}
	return (map);
}

int **transform_map_to_int(char ***map_str)
{
	int **map_int;
	int i;
	int j;

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
//int	main(t_data	*data)

{
	char ***map_str;
	int **map_int;

	map_str = init_map_str("test.fdf");
	map_int = transform_map_to_int(map_str);


	printf("%s\n", map_str[1][1]);
	printf("%i\n", (*map_int)[3]);
	printf("depth: %i\n", arr_len(*map_str));

	int i = 0;
	while (*map_int != NULL)
	{
		while (i < arr_len(*map_str))
		{
			printf("%i\n", (*map_int)[i]);
			i++;
		}
		i = 0;
		map_int++;
		printf("\n");
	}

	//int i = 0;
	//while (*map_str != NULL)
	//{
	//	while ((*map_str)[i] != NULL)
	//	{
	//		printf("%s\n", (*map_str)[i]);
	//		i++;
	//	}
	//	i = 0;
	//	map_str++;
	//}
	//return (0);
}