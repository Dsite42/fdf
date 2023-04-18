#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 600

# define MLX_ERROR 1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

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
	char	***map_str;
	double	***map_double;
	int 	map_colunms;
	int 	map_rows;
	int		scale;
	int		shift_x;
	int		shift_y;
	char	*file_path;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

void	init_map(t_data	*data, char *file_path);
void	of_free_arr(void **arr, int self_free);
void	of_free_two_d_arr(void ***arr, int self_free);
int		arr_len(char **arr);

#endif
