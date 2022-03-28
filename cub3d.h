/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:26:06 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 09:35:41 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define NONE 			0xFF000000
# define WHITE 			0x00FFFFFF
# define BLACK 			0x00000000
# define RED 			0x00FF0000
# define GREEN 			0x0000FF00
# define BLUE 			0x000000FF
# define MAGENTA 		0x00FF00FF
# define YELLOW			0x00FFFF00
# define CYAN 			0x0000FFF
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_ESC		53
# define BUFFER_SIZE	4096

typedef struct		s_sxy
{
	double			x;
	double			y;
}					t_sxy;

typedef struct		s_sprite
{
	int				nbrsprites;
	int				*order;
	double			*distance;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
	int				texx;
	int				texy;
}					t_sprite;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				width;
	int				height;
	void			*img2;
	int				*addr2;
}					t_data;

typedef struct		s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;

	int				color;

	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				x;
	int				texture;
}					t_ray;

typedef struct		s_texture
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

typedef struct		s_global
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				f;
	int				c;
	int				nbrlines;
	int				sizeline;
	char			**map;
	int				emptyline;
	int				insidemap;
	int				count;
	int				wrongcharmap;
	int				dx;
	int				dy;
	int				toomuchplayers;
	int				ry;
	int				rx;
	int				save;
	int				error;
	int				i;
	int				sum;
	int				nsew;
	int				ind;
	int				ind2;
	int				ind3;
	int				fred;
	int				fgreen;
	int				fblue;
	int				fcont;
	int				cred;
	int				cgreen;
	int				cblue;
	int				ccont;
	int				forc;
	t_sxy			*sxy;
	t_sprite		s;
	t_texture		t;
	t_data			texture[5];
	t_ray			ray;
	t_data			data;
}					t_global;

void	ft_error(t_global *global, char *str);
int		ft_iscub(char *str, t_global *global);
void	ft_parsing(char *file, t_global *global);
int		ft_parsing_map(char *file, t_global *global);
void	ft_map(char *str, t_global *global);
int		ft_is_map(char *str, t_global *global);
int		ft_copy_map(char *str, t_global *global);
int		ft_findchar(char *str, char c);
int		ft_emptyline(char *str);
void	ft_init(t_global *global);
void	ft_init_more(t_global *global);
int		get_next_line(int fd, char **line, t_global *global);
int		ft_free_buff(char **buff, t_global *global);
int		ft_eof(int ret, char **buff, char **line);
int		ft_copy(char **line, char **buff);
int		ft_check(char *str);
char	*ft_subbuff(char *buff, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(char *str);
int		ft_nsew(char c, t_global *global, int i, int j);
int		ft_atoif(const char *str, t_global *global);
int		ft_atoic(const char *str, t_global *global);
int		ft_atoir(const char *str, t_global *global);
void	ft_premap(char **str, t_global *global);
int		ft_strlen2(char *str);
void	ft_texture(char *str, t_global *global);
void		ft_path_texture(char *str, char **texture, t_global *global, int j);
int		ft_nbr_commas(const char *str);
int		ft_walls(t_global *global);
int		ft_walls_util(char *str);
int		ft_exit(t_global *global);
int		ft_check_save(char *str);
int		ft_imprimidor(t_global *global);
void	ft_verify_errors(t_global *global);
void	ft_init_ray2(t_global *global);
void	ft_drawstartend(t_global *global);
void	ft_incrementray(t_global *global);
void	ft_stepsidedist(t_global *global);
int		ft_mlx(t_global *global);
void	ft_left_right(t_global *global);
void	ft_forward_back(t_global *global);
void	ft_rotate_right_left(t_global *global);
void	ft_rotate_left(t_global *global, double olddirx);
void	ft_init_data_ray(t_global *global);
void	ft_init_ray(t_global *global);
void	ft_init_more(t_global *global);
int		ft_key_press(int keycode, t_global *global);
int		ft_key_release(int keycode, t_global *global);
void	ft_init_nsew(t_global *global);
void	my_mlx_pixel_put(t_global *global, int j);
int		ft_draw_lines(t_global *global);
int		ft_raycasting(t_global *global);
void	my_mlx_pixel_putc(t_global *global, int j);
void	my_mlx_pixel_putf(t_global *global, int j);
void	ft_get_texture(t_global *global);
void	ft_get_texture_address(t_global *global);
void	ft_draw_texture(t_global *global, int x, int y);
void	ft_init_texture(t_global *global);
void	ft_sprite(t_global *global);
void	ft_sort_sprite(t_global *global);
void	ft_sort(t_global *global);
void	ft_init_sprite(t_global *global);
void	ft_init_sprite_where(t_global *global, int i, int j, int v);
void	ft_sprite_calc(t_global *global, int i);
void	ft_draw_sprite(int y, int stripe, int texx, t_global *global);
void	ft_save (t_global *global);
int		ft_translate_color(int r, int g, int b);
void	ft_header (t_global *global, int fd);
void	ft_premap_checker(t_global *global);
int		 ft_walls2(t_global *global, int i, int j);
void	ft_c_switcher(t_global *global, int verify);
void 	ft_f_switcher(t_global *global, int verify);
void	ft_atoifc_check(const char *str, t_global *global);
int		ft_empty_checker(char *str, t_global *global);
void 	ft_flood_fill(int x, int y, t_global *global);

#endif
