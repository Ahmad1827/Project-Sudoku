#include "Map.h"
#include "game.h"
#include <fstream>
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric> 

const Uint8* keystates = SDL_GetKeyboardState(NULL);
int keypressed[50];
int distY = -80,count=0;
int success = 0;
int linecnt = 0;
int mouseX, mouseY;
int tileselected = -1;
int numbersput[12];
int numselected = 0;
int newgame = 1;
int fail = 0;
int GameBoard[100][100], FakeBoard[100][100];
int tileused[100];
int Tracker[100][100];

Map::Map()
{

	number[1] = TextureManager::LoadTexture("pics\\blackone.png");
	number[2] = TextureManager::LoadTexture("pics\\blacktwo.png");
	number[3] = TextureManager::LoadTexture("pics\\blackthree.png");
	number[4] = TextureManager::LoadTexture("pics\\blackfour.png");
	number[5] = TextureManager::LoadTexture("pics\\blackfive.png");
	number[6] = TextureManager::LoadTexture("pics\\blacksix.png");
	number[7] = TextureManager::LoadTexture("pics\\blackseven.png");
	number[8] = TextureManager::LoadTexture("pics\\blackeight.png");
	number[9] = TextureManager::LoadTexture("pics\\blacknine.png");

	selected = TextureManager::LoadTexture("pics\\blackselected.png");
	wrong = TextureManager::LoadTexture("pics\\blackwrong.png");
	undo = TextureManager::LoadTexture("pics\\blackundo.png");
	undohover = TextureManager::LoadTexture("pics\\blackundohover.png");
	newone = TextureManager::LoadTexture("pics\\blacknew.png");
	won = TextureManager::LoadTexture("pics\\blackwon.png");
	newonehover = TextureManager::LoadTexture("pics\\blacknewhover.png");

	tile[1] = TextureManager::LoadTexture("pics\\blackleft.png");
	tile[2] = TextureManager::LoadTexture("pics\\blacktopleft.png");
	tile[3] = TextureManager::LoadTexture("pics\\blacktop.png");
	tile[4] = TextureManager::LoadTexture("pics\\blacktopright.png");
	tile[5] = TextureManager::LoadTexture("pics\\blackright.png");
	tile[6] = TextureManager::LoadTexture("pics\\blackbottomright.png");
	tile[7] = TextureManager::LoadTexture("pics\\blackbottom.png");
	tile[8] = TextureManager::LoadTexture("pics\\blackbottomleft.png");
	tile[9] = TextureManager::LoadTexture("pics\\blackno.png");
	for (int i = 0; i < 81; ++i)
	{
		if (i % 9 == 0) distY += 80;
		src[i].x = src[i].y = 0;
		src[i].w = src[i].h = 80;
		dest[i].w = dest[i].h = 80;
		dest[i].x = 80 * (i % 9)+40;
		dest[i].y = distY;
	}
	for (int j = 1; j <= 10; ++j)
	{
		for (int i = 0; i < 81; ++i)
		{
			numsrc[j][i].x = numsrc[j][i].y = 0;
			numsrc[j][i].w = numsrc[j][i].h = 50;
			numdest[j][i].w = numdest[j][i].h = 50;
			numdest[j][i].x = -100;
			numdest[j][i].y = -100;
		}
	}

	src[90].x = src[90].y = 0;
	src[90].w = src[90].h = 78;
	dest[90].w = dest[90].h = 72;
	dest[90].x = -100;
	dest[90].y = 0;

	src[91].x = src[91].y = 0;
	src[91].h = 50;
	src[91].w = 300;
	dest[91].h = 50;
	dest[91].w = 300;
	dest[91].x = -400;
	dest[91].y = 730;

	src[92].x = src[92].y = 0;
	src[92].h = 50;
	src[92].w = 200;
	dest[92].h = 50;
	dest[92].w = 200;
	dest[92].x = -400;
	dest[92].y = 730;

	src[93].x = src[93].y = 0;
	src[93].h = 50;
	src[93].w = 200;
	dest[93].h = 50;
	dest[93].w = 200;
	dest[93].x = -400;
	dest[93].y = 730;

	src[94].x = src[94].y = 0;
	src[94].h = 50;
	src[94].w = 150;
	dest[94].h = 50;
	dest[94].w = 150;
	dest[94].x = 100;
	dest[94].y = 730;

	src[95].x = src[95].y = 0;
	src[95].h = 50;
	src[95].w = 400;
	dest[95].h = 50;
	dest[95].w = 400;
	dest[95].x = -500;
	dest[95].y = 730;

	src[96].x = src[96].y = 0;
	src[96].h = 50;
	src[96].w = 150;
	dest[96].h = 50;
	dest[96].w = 150;
	dest[96].x = -300;
	dest[96].y = 730;
}

void Map::CreateMap()
{
	int base = 3;
	int side = base * base;

	auto pattern = [base, side](int r, int c) {
		return (base * (r % base) + r / base + c) % side;
		};

	std::vector<int> rBase(base);
	std::iota(rBase.begin(), rBase.end(), 0);
	std::random_device rd;
	std::mt19937 g(rd());

	auto shuffle = [&g](std::vector<int>& s) {
		std::shuffle(s.begin(), s.end(), g);
		};

	std::vector<int> rows;
	for (int g : rBase) {
		for (int r : rBase) {
			rows.push_back(g * base + r);
		}
	}
	shuffle(rows);

	std::vector<int> cols;
	for (int g : rBase) {
		for (int c : rBase) {
			cols.push_back(g * base + c);
		}
	}
	shuffle(cols);

	std::vector<int> nums(base * base);
	std::iota(nums.begin(), nums.end(), 1);
	shuffle(nums);

	std::vector<std::vector<int>> board(base * base, std::vector<int>(base * base));
	for (int r = 0; r < rows.size(); ++r) {
		for (int c = 0; c < cols.size(); ++c) {
			board[r][c] = nums[pattern(r, c)];
		}
	}
	for (int r = 0; r < rows.size(); ++r) {
		for (int c = 0; c < cols.size(); ++c) {
			GameBoard[r][c] = board[r][c];
			Tracker[r][c] = board[r][c];
			FakeBoard[r][c] = board[r][c];
		}
	}
	int counters = 0;
	int counterI = 0,counterJ=0;
	int trues = 1;
	while (trues)
	{
		counterI = rand() % 10;
		counterJ = rand() % 10;
		if (GameBoard[counterI][counterJ])
		{
			counters++;
			GameBoard[counterI][counterJ] = 0;
			Tracker[counterI][counterJ] = 0;
			if (counters == 45)
			{
				trues = 0;
			}
		}
	}
	for (const auto& line : board) {
		for (int num : line) {
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
}

void Map::Updater()
{
	if (success == 1)
	{
		dest[95].x = 350;
	}
	if (newgame == 1)
	{
		CreateMap();
		dest[95].x = -550;
		int aux = -8;
		for (int r = 0; r < 9; ++r) 
		{
			aux += 8;
			for (int c = 0; c < 9; ++c) 
			{
				if (GameBoard[r][c])
				{
					numdest[GameBoard[r][c]][numbersput[GameBoard[r][c]] + 1].x = dest[r+c+aux].x + dest[r + c + aux].w / 2 - numdest[GameBoard[r][c]][numbersput[GameBoard[r][c]] + 1].w / 2;
					numdest[GameBoard[r][c]][numbersput[GameBoard[r][c]] + 1].y = dest[r + c + aux].y + dest[r + c + aux].h / 2 - numdest[GameBoard[r][c]][numbersput[GameBoard[r][c]] + 1].h / 2;
					numbersput[GameBoard[r][c]]++;
					tileused[r + c + aux] = 1;
				}
			}
		}
		newgame = 0;
	}
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > dest[94].x && mouseX<dest[94].x + dest[94].w && mouseY>dest[94].y && mouseY < dest[94].y + dest[94].h)
	{
		dest[96].x = 100;
	}
	else
	{
		dest[96].x = -500;
	}

		if (mouseX > dest[92].x && mouseX<dest[92].x + dest[92].w && mouseY>dest[92].y && mouseY < dest[92].y + dest[92].h)
		{
			dest[93].x=500;
		}
		else
		{
			dest[93].x = -500;
		}
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LMASK)
	{
		if (mouseX > dest[94].x && mouseX<dest[94].x + dest[94].w && mouseY>dest[94].y && mouseY < dest[94].y + dest[94].h)
		{
			dest[95].x = -550;
			for (int i = 1; i <= 90; ++i)
			{
				tileused[i] = 0;
			}
			for (int i = 1; i <= 9; ++i)
			{
				keypressed[i] = 0;
				numbersput[i] = 0;
			}
			for (int i = 1; i <= 9; ++i)
			{
				for (int j = 1; j <= 90; ++j)
				{
					numdest[i][j].x = -500;
				}
			}
			dest[90].x = -500;
			numselected = 0;
			newgame = 1;
			return;
		}
		for(int i=0;i<81;++i)
		{ 
			if (mouseX > dest[92].x && mouseX<dest[92].x + dest[92].w && mouseY>dest[92].y && mouseY < dest[92].y + dest[92].h && fail == 1)
			{
				dest[90].x = -100;
				dest[90].y = -100;
				fail = 0;
				numdest[numselected][numbersput[numselected]].x = -100;
				numdest[numselected][numbersput[numselected]].y = -100;
				numbersput[numselected]--;
				dest[91].x = -500;
				dest[92].x = -500;
			}
			if (mouseX > dest[i].x && mouseX<dest[i].x + dest[i].w && mouseY>dest[i].y && mouseY < dest[i].y + dest[i].h && tileused[i]==0 && fail == 0)
			{
				dest[90].x = dest[i].x + 4;
				dest[90].y = dest[i].y + 4;
				for (int i = 1; i <= 9; ++i)
				{
					keypressed[i] = 0;
				}
				numselected = 0;
				tileselected = i;
			}
		}
	}
	if (fail == 1)
	{
		dest[94].x = -500;
		dest[96].x = -500;
	}
	else
	{
		dest[94].x = 100;
	}
	if (fail == 0)
	{
		if (keystates[SDL_SCANCODE_1])
		{
			numselected = 1;
		}
		else if (keystates[SDL_SCANCODE_2])
		{
			numselected = 2;
		}
		else if (keystates[SDL_SCANCODE_3])
		{
			numselected = 3;
		}
		else if (keystates[SDL_SCANCODE_4])
		{
			numselected = 4;
		}
		else if (keystates[SDL_SCANCODE_5])
		{
			numselected = 5;
		}
		else if (keystates[SDL_SCANCODE_6])
		{
			numselected = 6;
		}
		else if (keystates[SDL_SCANCODE_7])
		{
			numselected = 7;
		}
		else if (keystates[SDL_SCANCODE_8])
		{
			numselected = 8;
		}
		else if (keystates[SDL_SCANCODE_9])
		{
			numselected = 9;
		}
	}
	
		if (tileselected!=-1 && keypressed[numselected]==0 && numselected && fail == 0)
		{
			//  0--8  9--17 18--26
			keypressed[numselected] = 1;
			numdest[numselected][numbersput[numselected]+1].x = dest[tileselected].x+dest[tileselected].w/2- numdest[numselected][numbersput[numselected] + 1].w/2;
			numdest[numselected][numbersput[numselected] + 1].y = dest[tileselected].y + dest[tileselected].h / 2 - numdest[numselected][numbersput[numselected] + 1].h / 2;
			numbersput[numselected]++;
			std::cout << numbersput[numselected] << std::endl;
			Tracker[tileselected / 9][tileselected % 9] = numselected;
			if (FakeBoard[tileselected/9][tileselected%9] != numselected)
			{
				Tracker[tileselected / 9][tileselected % 9] = 0;
				dest[91].x = 100;
				dest[92].x = 500;
				fail = 1;
			}
		}
		int track = 1;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (Tracker[i][j] == 0)
				{
					track = 0;
				}
			}
		}
		if (track == 1)
		{
			success = 1;
		}

	DrawMap();
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 25; ++column)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
		for (int i = 0; i < 9; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[2], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[3], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[4], src[i], dest[i]);
			}
		}
		//2
		for (int i = 9; i < 18; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[1], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[9], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[5], src[i], dest[i]);
			}
		}
		//3
		for (int i = 18; i < 27; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[8], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[7], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[6], src[i], dest[i]);
			}
		}
		//4
		for (int i = 27; i < 36; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[2], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[3], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[4], src[i], dest[i]);
			}
		}
		//5
		for (int i = 36; i < 45; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[1], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[9], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[5], src[i], dest[i]);
			}
		}
		//6
		for (int i = 45; i < 54; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[8], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[7], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[6], src[i], dest[i]);
			}
		}
		//7
		for (int i = 54; i < 63; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[2], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[3], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[4], src[i], dest[i]);
			}
		}
		//8
		for (int i = 63; i < 72; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[1], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[9], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[5], src[i], dest[i]);
			}
		}
		//9
		for (int i = 72; i < 81; ++i)
		{
			if (i % 3 == 0)
			{
				TextureManager::Draw(tile[8], src[i], dest[i]);
			}
			else if (i % 3 == 1)
			{
				TextureManager::Draw(tile[7], src[i], dest[i]);
			}
			else if (i % 3 == 2)
			{
				TextureManager::Draw(tile[6], src[i], dest[i]);
			}
		}
		TextureManager::Draw(selected, src[90], dest[90]);
		TextureManager::Draw(wrong, src[91], dest[91]);
		TextureManager::Draw(undo, src[92], dest[92]);
		TextureManager::Draw(undohover, src[93], dest[93]);
		TextureManager::Draw(newone, src[94], dest[94]);
		TextureManager::Draw(won, src[95], dest[95]);
		TextureManager::Draw(newonehover, src[96], dest[96]);
		for (int j = 1; j <= 9; ++j)
		{
			for (int i = 1; i <= 90; ++i)
			{
				TextureManager::Draw(number[j], numsrc[j][i], numdest[j][i]);
			}
		}
}

