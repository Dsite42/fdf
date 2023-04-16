#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#include "fdf.h"


void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}


void	render_row(t_data *data)
{
	int i = 0;
	int j = 0;
	int	scale = 50;
	double max_value = 31;
	double x = 0;
	double y = 0;

	while (data->map_int[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			//printf("%f\n", (data->map_int[i][j] / max_value *scale));
			//img_pix_put(&data->img, ((WINDOW_WIDTH - data->map_colunms * scale) / 2) + scale * j, ((WINDOW_HEIGHT - data->map_rows * scale) / 2) + scale * (i - data->map_int[i][j] / max_value), RED_PIXEL);
			
			x = scale * ((j - data->map_colunms + 1) * cos(330) - (data->map_rows - 1 - i) * sin(330));
			y = scale * (i - data->map_int[i][j] / max_value);
			printf("%f\n", x);
			//if (i != data->map_rows - 1 || (i == data->map_rows - 1 && j != data->map_colunms -1))
			//	img_pix_put(&data->img, x + (x - (x * cos(30) - y * sin(30))),
			//	 y ,
			//	  RED_PIXEL);
			//else
			  img_pix_put(&data->img, x, y, RED_PIXEL);
			j++;
		}
		j = 0;
		i++;
	}
}


int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLACK_PIXEL);
	render_row(data);
	
	

	//render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	//render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;

	init_map(&data);

	int i = 0;
	int j = 0;
	while (data.map_int[j] != NULL)
	{
		while (i < data.map_colunms)
		{
			printf("%i\n", (data.map_int)[j][i]);
			i++;
		}
		i = 0;
		j++;
		printf("\n");
	}


	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	of_free_arr((void **)data.map_int, 1);
	of_free_two_d_arr((void ***)data.map_str, 1);

}