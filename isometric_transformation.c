#include "fdf.h"

void	isometric_transformation(t_data *data)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	z;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	z = 0;
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			x = data->map_double[i][j][0];
			y = data->map_double[i][j][1];
			z = data->map_double[i][j][2];
			data->map_double[i][j][0] = (x - y) * cos(0.523599);
			data->map_double[i][j][1] = -z + (x + y) * sin(0.523599);
			j++;
		}
		j = 0;
		i++;
	}
}
