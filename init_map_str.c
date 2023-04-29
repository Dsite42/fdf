/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:19:38 by cgodecke          #+#    #+#             */
/*   Updated: 2023/04/29 18:20:19 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	***add_line_to_map(char ***map, char **splitted_line)
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
