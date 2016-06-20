#ifndef WOLF_3D
# define WOLF_3D

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <SDL2/SDL.h>

# define WIN_X	1600
# define WIN_Y	900
# define TEX_X	1024
# define TEX_Y	1024

typedef struct			s_v2d
{
	float				x;
	float				y;
}						t_v2d;

typedef struct			s_v2dint
{
	int					x;
	int				 	y;
}						t_v2dint;

typedef struct			s_ent
{
	t_v2d				loc;
	t_v2d				rot;
}						t_ent;

typedef struct			s_keys
{
	int					w_key;
	int					a_key;
	int					s_key;
	int					d_key;
}						t_keys;

typedef struct			s_env
{
	t_ent				player;
	t_ent				ray;
	t_v2d				plane;
	t_v2d				camera;
	float				total_dist;
	int					line_height;
	t_v2dint			step;
	t_v2dint			map;
	t_v2d				dist;
	t_v2d				delta_dist;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*img;
	void				*pixels;
	int					px_pitch;
	int					start;
	int					end;
	size_t				side;
	t_keys				key;
	int					exit;
	int					**world;
	size_t				run_time;
	size_t				run_cooldown;
	size_t				rows;
	size_t				cols;
	float				top_bottom;
	float				rot;
	clock_t				time_old;
	clock_t				clocks;
	unsigned char		**tex;
}						t_env;

/*
** src/main.c
*/
size_t					ft_get_time(void);
void					fill_map(t_env *e);

/*
** src/dda.c
*/
void					calc_ray_loc_rot(t_env *e, size_t x);
void					calc_init_dist(t_env *e);
void					dda(t_env *e);
void					calc_line(t_env *e);

/*
** src/game_loop.c
*/
void					game_loop(t_env *e);
void					rotate(t_env *e, float rot);
void					set_run(t_env *e);
/*
** src/mouse.c
*/
void					mouse_move(int x);

/*
** src/env_init.c
*/
void					init_env(t_env *e);

/*
** src/key_events.c
*/
void					key_down(SDL_Keycode key, t_env *e);
void					key_up(SDL_Keycode key, t_env *e);
void					move_player(t_env *e);

/*
** src/draw.c
*/
void					redraw(t_env *e);
void					draw_frame(t_env *e);

#endif
