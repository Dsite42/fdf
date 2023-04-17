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
	if (keysym == XK_plus)
	{
		data->scale += 10;
	}
	if (keysym == XK_minus)
	{
		data->scale -= 10;
	}

	return (0);
}

void line(t_data *data, int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
		img_pix_put(&data->img, x0, y0, RED_PIXEL);
        //setPixel(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

double	scale_x(t_data *data, double x)
{
	double	scaled_x;

	scaled_x = ((WINDOW_WIDTH - (data->map_colunms - 1) * data->scale) / 2) + data->scale * x;
	return (scaled_x);
}

double	scale_y(t_data *data, double y)
{
	double	scaled_y;

	scaled_y = ((WINDOW_HEIGHT - (data->map_rows - 1) * data->scale) / 2) + data->scale * y;
	return (scaled_y);
}

void	render_row(t_data *data)
{
	int i = 0;
	int j = 0;
	double x = 0;
	double y = 0;

	of_free_two_d_arr((void ***)data->map_double, 1);
	init_map(data);
	printf("scale: %i\n", data->scale);
	while (data->map_double[i] != NULL)
	{
		while (j < data->map_colunms)
		{
			//printf("%f\n", (data->map_double[i][j] / max_value *scale));
			x = ((data->map_double[i][j][1] * cos(-45) - data->map_double[i][j][2] * sin(-45)) * cos(35.264) + data->map_double[i][j][0] * sin(35.264) * cos(30));
			y = (-((data->map_double[i][j][1] * cos(-45) - data->map_double[i][j][2] * sin(-45)) * sin(35.264) - data->map_double[i][j][0] * cos(35.264)) * sin(30));
				//printf("i: %i j: %i x: %f, y: %f\n", i, j, x, y);
			//x = data->map_double[i][j][0];
			//y = data->map_double[i][j][1];
			data->map_double[i][j][0] = x;
			data->map_double[i][j][1] = y;
			
				//printf("i: %i j: %i x2: %f, y2: %f\n", i, j, data->map_double[i][j][0], data->map_double[i][j][1]);
			
			//img_pix_put(&data->img, ((int)(WINDOW_WIDTH - data->map_colunms * scale) / 2) + scale * x, (int)((WINDOW_HEIGHT - data->map_rows * scale) / 2) + scale * (y / max_value), RED_PIXEL);
			if (j > 0)
			{
				line(data, scale_x(data, data->map_double[i][j - 1][0]), scale_y(data, data->map_double[i][j - 1][1]), scale_x(data, x), scale_y(data, y));
			}
			
			if (i > 0)
			{
				line(data, scale_x(data, data->map_double[i - 1][j][0]), scale_y(data, data->map_double[i - 1][j][1]), scale_x(data, x), scale_y(data, y));
			}

			//x = scale * ((j - data->map_colunms + 1) * cos(330) - (data->map_rows - 1 - i) * sin(330));
			//y = scale * (i - data->map_double[i][j] / max_value);
			//printf("%f\n", x);
			//if (i != data->map_rows - 1 || (i == data->map_rows - 1 && j != data->map_colunms -1))
			//	img_pix_put(&data->img, x + (x - (x * cos(30) - y * sin(30))),
			//	 y ,
			//	  RED_PIXEL);
			//else
			  //img_pix_put(&data->img, x, y, RED_PIXEL);
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
	data.scale = 50;
	init_map(&data);

	//int i = 0;
	//int j = 0;
	//while (data.map_double[j] != NULL)
	//{
	//	while (i < data.map_colunms)
	//	{
	//		printf("%f\n", (data.map_double)[j][i][0]);
	//		printf("%f\n", (data.map_double)[j][i][1]);
	//		printf("%f\n", (data.map_double)[j][i][2]);
	//		i++;
	//	}
	//	i = 0;
	//	j++;
	//	printf("\n");
	//}

	
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
	
	of_free_two_d_arr((void ***)data.map_double, 1);
	of_free_two_d_arr((void ***)data.map_str, 1);

}