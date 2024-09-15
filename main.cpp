#include "game.h"
Game* game = nullptr;

const int FPS = 60;
const int frameDelay = 1000 / 60;
Uint32 frameStart;
int frameTime;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("Project Sudoku",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,800,false);
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		if (keystates[SDL_SCANCODE_ESCAPE])
		{
			return 0;
			std::cout << "Game cleaned" << std::endl;
		}
	}
	game->clean();
	return 0;
}


//
// 5---4
//800---x
//x=
//
