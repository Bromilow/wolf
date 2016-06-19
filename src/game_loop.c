#include "wolf3d.h"

void	game_loop(t_env *e)
{
	SDL_Event	event;
	int			loop;

	loop = 42;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = -42;
			else if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					loop = -42;
				else
					key_down(event.key.keysym, e);
			else if (event.type == SDL_KEYUP)
				key_up(e.key.keysym, e);
			else if (event.type == SDL_MOUSEMOTION)
				rotate(e, event.motion.xrel >> 3);
		}
		redraw(e);
	}
}
