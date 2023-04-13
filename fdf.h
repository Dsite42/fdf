#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

# define MLX_ERROR 1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
	char ***map_str;
	int **map_int;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

void	init_map(t_data	*data);
void	of_free_arr(void **arr, int self_free);
void	of_free_two_d_arr(void ***arr, int self_free);
int		arr_len(char **arr);

#endif
