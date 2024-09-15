#include "Entities.h"

int z_order = 0, crownkitty = 0, shoot = 0, goright = 0, goleft = 1, timerenemy = 0, shootenemy = 0, validmeat = 0, catright = 0, catleft = 0;
SDL_Renderer* Game::renderer = nullptr;
Map* map;

Manager tmanager;



int touchkeyboard = 0, upgradewalls=0, levelwall=0;

const Uint8* keystate = SDL_GetKeyboardState(NULL);

SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

int cnt = 0;


int valid(float xa,float ya,float ha,float wa,float xb,float yb,float hb, float wb)
{

	if ((xa > xb && xa + wa < xb + wb) || (xa<xb && xa + wa>xb) || (xa<xb + wb && xa + wa>xb + wb) || (xa<xb && xa + wa>xb + wb))
	{
		if ((ya > yb && ya + ha < yb + hb) || (ya<yb && ya + ha>yb) || (ya<yb + hb && ya + ha>yb + hb) || (ya<yb && ya + ha>yb + hb))
		{
			return 1;
		}
	}
	return 0;
}


Game::Game()
{}
Game::~Game()
{}


void Game::init(const char *title,int xpos,int ypos,int width,int height,bool fullscreen)
{
	
	int flags = 0;
	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem init" << std::endl;

		window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer Created!" << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	map = new Map();
}

void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{

	map->Updater();
	
		//tmanager.refresh();
		//tmanager.update();
		
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	//tmanager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(tmanager.addEntity());
	tile.addComponent<TileComponent>(x,y,32,32,id);
}