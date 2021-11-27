/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:23:04 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:23:08 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAINING_CUB3D_H
# define TRAINING_CUB3D_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../gnl/get_next_line.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_map {
	char			**map;
	int				step_x;
	int				step_y;
	int				x;
	int				y;
	int				start;
	int				start_x;
	int				start_y;
	int				startdir_x;
	int				startdir_y;
	int				dir_x;
	int				dir_y;
	int				rh_x;
	int				rh_y;
}					t_map;

typedef struct		s_win {
	int				x;
	int				wight;
	int				high;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				l_high;
	int				l_start;
	int				l_end;
	int				c_color;
	int				f_color;
	int				screen_h;
	int				screen_w;
}					t_win;

typedef struct		s_plr {
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
}					t_plr;

typedef struct		s_ray {
	double			dir_x;
	double			dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			walldist;
	char			walldir;
	char			*txt_data;
	int				txt_h;
	int				txt_w;
	int				txt_bpp;
	int				txt_ll;
	int				wall_side;
}					t_ray;

typedef struct		s_spritepos
{
	double			x;
	double			y;
}					t_spritepos;

typedef struct		s_sprite
{
	int				sprite_count;
	int				*order;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				tex_y;
	t_spritepos		*spritepos;
}					t_sprite;

typedef struct		s_text
{
	char			*txt1_path;
	void			*txt1;
	char			*txt1_data;
	int				txt1_h;
	int				txt1_w;
	int				txt1_bpp;
	int				txt1_ll;
	int				txt1_ed;
	char			*txt2_path;
	void			*txt2;
	char			*txt2_data;
	int				txt2_h;
	int				txt2_w;
	int				txt2_bpp;
	int				txt2_ll;
	int				txt2_ed;
	char			*txt3_path;
	void			*txt3;
	char			*txt3_data;
	int				txt3_h;
	int				txt3_w;
	int				txt3_bpp;
	int				txt3_ll;
	int				txt3_ed;
	char			*txt4_path;
	void			*txt4;
	char			*txt4_data;
	int				txt4_h;
	int				txt4_w;
	int				txt4_bpp;
	int				txt4_ll;
	int				txt4_ed;
	char			*spr_path;
	void			*spr;
	char			*spr_data;
	int				spr_h;
	int				spr_w;
	int				spr_bpp;
	int				spr_ll;
	int				spr_ed;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				r;
	int				g;
	int				b;
}					t_text;

typedef struct		s_scrshot
{
	char			file_type[2];
	unsigned int	file_size;
	unsigned int	reserved;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	int				image_width;
	int				image_height;
	unsigned int	planes;
	unsigned int	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				x_pixels_per_meter;
	int				y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}					t_scrshot;

typedef struct		s_all {
	t_win			*win;
	t_map			*map;
	t_plr			*plr;
	t_ray			*ray;
	t_text			*text;
	t_sprite		*spr;
	t_scrshot		*scrshot;
}					t_all;

int					key_press(int key, t_all *all);
void				raycast(t_all *all);
void				ft_parser(int fd, t_all *all);
void				ft_sprites(t_all *all, const double *buffer);
int					get_rgb(int r, int g, int b);
void				get_sprite (t_sprite *spr, t_map *map);
void				take_screenshot(t_all *all);
int					check_arg(char **argv);
void				init_text(t_text *text, t_win *win);
void				check_map(t_map *map, t_plr *plr);
void				ft_error(char *str);
void				ft_destroy_win(t_win *win);
void				init_win(t_win *win);
int					prog_exit(t_all *all);
void				init_param(t_win *win, t_text *text);
void				get_start_map(t_map *map);
char				*get_txt_path(char *str, const char *check, int i);
int					get_color(char *str, t_text *txt, int check);
void				get_resolution(char *str, t_win *win);
void				init_plane(t_map *map, int plane);
void				init_dir(char dir, t_plr *plr);
void				sort_sprites(t_sprite *spr, t_plr *plr);
void				calc_spr_dist(t_sprite *spr, t_plr *plr, t_win *win, int i);
void				get_wall_text(t_ray *ray, t_text *text);
void				ft_init_ray(t_ray *ray, t_plr *plr, t_map *map);
void				check_map_parameters(t_map *map, int map_start);
int					counter(const char *str, int i);
void				make_map(t_list **head, int size, t_map *map);

#endif
