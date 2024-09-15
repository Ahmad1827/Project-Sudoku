#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Map {
public:
	Map();
	

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Updater();
	void CreateMap();
private:
	SDL_Rect src[200], dest[200];
	SDL_Rect numsrc[12][100], numdest[12][100];
	SDL_Texture* tile[100];
	SDL_Texture* number[15];
	SDL_Texture* selected;
	SDL_Texture* wrong;
	SDL_Texture* undo;
	SDL_Texture* newone;
	SDL_Texture* newonehover;
	SDL_Texture* won;
	SDL_Texture* undohover;
	int map[20][25];
};