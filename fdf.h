#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"


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
	int		map_colunms;
	int		map_rows;
	double	max_distance_x;
	double	max_distance_y;
	double	highest_y;
	double	scale;
	int		shift_x;
	int		shift_y;
	double	x_rotation_rad;
}	t_data;

typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	int direction;
}	t_line;

void	init_map(t_data	*data, char *file_path);
void	of_free_arr(void **arr, int self_free);
void	of_free_two_d_arr(void ***arr, int self_free);
int		arr_len(char **arr);
void	isometric_transformation(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		window_close(t_data *data);
int		of_atoi_base(char *str, char *base);
double	max_distance(t_data *data, int axis);
int		is_map_valid(t_data *data);
char	***init_map_str(char *file);
int		two_d_arr_len(char ***arr);
double	***transform_map_to_int(char ***map_str);
int		render_image(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void draw_line(t_data *data, t_line *line_val, int i, int j);
double	highest_y(t_data *data);

double	scale_x(t_data *data, double x);
double	scale_y(t_data *data, double y);

#endif
