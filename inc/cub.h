/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:19:17 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/12 11:45:22 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../Libft/libft.h"
# define GREY 0xd1dddd
# define WHITE 0xffffff
# define FOV 0.66
# define SCALE 16
# include "../minilibx_mms_20200219/mlx.h"
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define SPACE 49
# define CTRL 256 || 269
# define ESC 53
# define BUFFER_SIZE 1024
# define NO_FLG		0b00000000
# define W_FLG		0b10000000
# define A_FLG		0b01000000
# define D_FLG		0b00100000
# define RIGHT_FLG	0b00010000
# define LEFT_FLG	0b00001000
# define S_FLG		0b00000100
# define ALL_FLG	0b11111111
# define RES_F		0b10000000
# define FLR_F		0b01000000
# define CEL_F		0b00100000
# define SPR_F		0b00010000
# define NRT_F		0b00001000
# define STH_F		0b00000100
# define WST_F		0b00000010
# define EST_F		0b00000001

typedef	struct	s_val
{
	int			col;
	int			row;
	int			plr;
	size_t		len;
}				t_val;

typedef	struct	s_gnl
{
	char		*buf;
	ssize_t		bwr;
	int			fd;
}				t_gnl;

typedef	struct	s_bmp
{
	int			rsv;
	int			off;
	int			hdr;
	int			pln;
	int			bpp;
}				t_bmp;

typedef	struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
}				t_spt;

typedef	struct	s_spt_data
{
	void		*spt_img;
	void		*spt_addr;
	int			spt_amt;
	int			bpp;
	int			ll;
	int			h_res;
	int			w_res;
	int			end;
	t_spt		*spt_arr;
	float		rel_x;
	float		rel_y;
	float		inv;
	float		trns_x;
	float		trns_y;
	int			scrn_x;
	int			height;
	int			width;
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
	int			img_x;
	int			img_y;
}				t_dta;

typedef	struct	s_program
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_prg;

typedef	struct	s_map
{
	uint64_t	width_x;
	uint64_t	height_y;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	int			floor_color;
	int			cell_color;
	int			p_cnt;
	char		**mini_map;
}				t_map;

typedef	struct	s_player
{
	float		x_pos;
	float		y_pos;
	float		x_dir;
	float		y_dir;
	float		plane_x;
	float		plane_y;
	float		speed;
	float		rot_speed;
}				t_plr;

typedef	struct	s_line
{
	int			height;
	int			start;
	int			end;
}				t_lin;

typedef	struct	s_texture
{
	void		*img;
	void		*adr;
	int			bpp;
	int			ll;
	int			x_wd;
	int			y_hg;
	int			end;
	int			textr_x;
	int			side;
	float		start;
	float		ratio;
}				t_tex;

typedef	struct	s_all_textrs
{
	int			curr_x;
	t_tex		nrt;
	t_tex		sth;
	t_tex		wst;
	t_tex		est;
}				t_atex;

typedef	struct	s_drw
{
	char		is_hit;
	t_tex		side;
	float		cam_x;
	float		wall_x;
	float		s_dst_x;
	float		s_dst_y;
	float		d_dst_x;
	float		d_dst_y;
	float		pltowll_dst;
	float		ray_dir_x;
	float		ray_dir_y;
	int			x;
	int			map_x;
	int			map_y;
	int			stp_x;
	int			stp_y;
}				t_drw;

typedef	struct	s_all
{
	t_map		map;
	t_prg		prg;
	t_plr		plr;
	t_atex		tex;
	t_lin		lin;
	t_dta		dta;
	int			fd;
	int			key_flag;
	int			err;
}				t_all;

int				loop_processor(t_all *all);
int				error_handler(char *mes);
int				res_handler(t_all *all);
int				draw_img(t_all *all);
int				draw_wall(int start, int end, t_tex side, t_all *all);
int				draw_line(int start, int end, int color, t_all *all);
int				draw_sprites(t_all *all, t_plr *plr, float *z_buf, t_dta *spr);
int				keypress_handler(int keycode, t_all *all);
int				keyrelease_handler(int keycode, t_all *all);
int				create_rgb(int r, int g, int b);
int				get_next_line(int fd, char **line);
int				create_rgb(int r, int g, int b);
int				valid_map(char **map);
int				create_map(t_map *map, t_list *lst);
int				get_player_start_position(t_all *all);
int				get_sprites_map(t_all *all);
int				parse_file(t_all *all, char *str);
int				parse_color(char flag, char **str, t_all *all, int *flg);
int				parse_resolution(char **str, t_all *all, int *flg);
int				is_num(char *str);
int				free_tmp(char **arr, char flag);
int				calc_line(t_drw *drw, t_all *all);
int				make_screenshot(int	h, int w, t_all *all);
char			*ft_newreminder(char *rem, char *err);
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_nextline(char *rem);
void			cube_init(t_all *all);
int				move_player(t_all *all, float x_off, float y_off);
int				strafe_player(t_all *all, float x_off, float y_off);
int				turn_player(t_all *all, float ang);
void			my_pixel_put(t_prg *data, int x, int y, int color);
int				flags_checker(int flg, char key, t_all *all);
int				valid_file(char *frm, char *arg, int size);

#endif
