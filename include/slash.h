//https://www.youtube.com/watch?v=JPAyj85tJ5E&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=1

#ifndef SLASH_H
# define SLASH_H

#include <SDL.h>
#include <SDL_image.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int width, height;
	char *name;
	SDL_Window *window;
} t_window;


typedef struct
{
	int	x;
	int	y;
	int size;
	short	health;
	char	*name;
} t_player;

typedef struct
{
	int x, y;
} Star;


typedef struct
{
	//Players
	t_player player;
	t_window window;

	//Stars
	Star stars[100];

	//Images
	SDL_Texture *star;
	SDL_Renderer *renderer;
} GameState;

/* PUT FUNCTIONS */

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putstr_fd(char *s, int fd);


#endif
