#include "../include/slash.h"

void	loadGame(GameState *game)
{
	SDL_Surface *starSurface = NULL;
	int i = 0;

	game->player.x = 320 - 40;
	game->player.y = 240 - 40;

	//Load images and create textures from them
	starSurface = IMG_Load("textures/star.png");
	if (starSurface == NULL)
	{
		printf("Cannot find star.png!\n\n");
		SDL_Quit();
		exit(1);
	}

	game->star = SDL_CreateTextureFromSurface(game->renderer, starSurface);
	SDL_FreeSurface(starSurface);

	//init stars
	while (i <  100)
	{
		game->stars[i].x = random()%1280;
		game->stars[i].y = random()%720;
		i++;
	}

}

int processEvents(SDL_Window *window, GameState *game)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_WINDOWEVENT_CLOSE:
			{
				if (window)
				{
					SDL_DestroyWindow(window);
					window = NULL;
					done = 1;
				}
			}
			break;
			case SDL_KEYDOWN:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						done = 1;
					break;
				}
			}
			break;
			case SDL_QUIT:
				//quit out of the game
				done = 1;
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		game->player.x -= 5;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		game->player.x += 5;
	}
	if (state[SDL_SCANCODE_UP])
	{
		game->player.y -= 5;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		game->player.y += 5;
	}

	return (done);
}

void	doRender(SDL_Renderer *renderer, GameState *game)
{
	int i = 0;
	//Render display

	//set the drawing color to blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//Clear the screen (to blue)
	SDL_RenderClear(renderer);

	//set the drawing color to while
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = {game->player.x, game->player.y, 80, 80};
	SDL_RenderFillRect(renderer, &rect);

	//draw the star image
	while (i < 100)
	{
		SDL_Rect starRect = {game->stars[i].x, game->stars[i].y, 64, 64};
		SDL_RenderCopy(renderer, game->star, NULL, &starRect);
		i++;
	}

	//We are done drawing, "present" or show to the screen what we've drawn
	SDL_RenderPresent(renderer);

}

int	main(void)
{
	GameState game;
	SDL_Window *window; //Declare a window
	SDL_Renderer *renderer; //Declare a renderer

	SDL_Init(SDL_INIT_VIDEO); //Initialize SDL2

	srandom((int)time(NULL));

	//Create an application window with the following settings:
	window = SDL_CreateWindow("Game Window",		// window title
				SDL_WINDOWPOS_UNDEFINED,	// initial x position
				SDL_WINDOWPOS_UNDEFINED,	// initial y position
				1280,				// width, in pixels
				720,				// height, in pixels
				0				// flags
				);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	game.renderer = renderer;

	loadGame(&game);

	// The window is open: enter program loop (see SDL_PollEvent)
	int done = 0;

	//Event loop
	while (!done)
	{
		//Check for events
		done = processEvents(window, &game);

		doRender(renderer, &game);

		//don't burn up the CPU
		// SDL_Delay(10);
	}

	//Shutdown game and unload all memory
	SDL_DestroyTexture(game.star);

	//Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	//Clean up
	SDL_Quit();
	return (0);
}
