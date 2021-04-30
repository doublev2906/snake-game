#include"StartGame.h"
StartGame::StartGame()
{
	SDL_Texture* BG = NULL;
	start = false;
	quitgame = false;
	check = true;
	lv = 190;
}

StartGame::~StartGame()
{
	;
}



void StartGame::loadBackGround(SDL_Renderer* ren)
{
	BG = loadTexture("images.bmp", ren);
	renderTexture(BG, ren, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}



void StartGame::mainMenu(SDL_Renderer* renderer)
{
	loadBackGround(renderer);
	SDL_Color white = { 255, 255,255 };
	SDL_Color red = { 255, 0,0 };
	createText("S.N.A.K.E", renderer, 80, 80, 300, 100,red);
	createText("New Game", renderer, 140, 200, 150, 80, white);
	createText("Quit Game", renderer, 140, 300, 150, 80, white);
	SDL_RenderPresent(renderer);
}

void StartGame::createLevel(SDL_Renderer* renderer)
{
	red = loadTexture("red.bmp", renderer);
	white = loadTexture("white.bmp", renderer);
	loadBackGround(renderer);
	SDL_Color white_ = { 255, 255,255 };
	createText("level", renderer, 140, 100, 200, 100, white_);
	createText("Start", renderer, 160, 400, 150, 80, white_);
	for (int i = 140; i < 390; i+=50)
	{
		renderTexture(white, renderer, i, 230, 50, 50);
	}
	for (int i = 140; i < lv; i += 50)
	{
		renderTexture(red, renderer, i, 230, 50, 50);
	}
	SDL_RenderPresent(renderer);
	
}
void StartGame::select(SDL_Renderer* renderer)
{
	SDL_Event e;
	SDL_Event ev;
	bool isQuit = false;
	while (!isQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isQuit = true;
			}


			if (check)
			{
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (e.button.x >= 140 && e.button.x <= 300 && e.button.y >= 200 && e.button.y <= 300)
						{
							createLevel(renderer);
							check = false;
						}
					}

				}
			}
			else {
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_LEFT) lv -= 50;
					if (e.key.keysym.sym == SDLK_RIGHT) lv += 50;
					if (lv < 190) lv = 190;
					else if (lv > 390) lv = 390;
					SDL_RenderClear(renderer);
					createLevel(renderer);
				}

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (e.button.x >= 160 && e.button.x <= 310 && e.button.y >= 400 && e.button.y <= 500) {
							start = true;
							isQuit = true;
							SDL_DestroyTexture(BG);
						}
					}
				}
			}

			if (check == true)
			{
				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					if (e.button.x >= 160 && e.button.x <= 310 && e.button.y >= 300 && e.button.y <= 400);
					{
						quitgame = true;
						isQuit = true;
					}
				}
			}
		}
	}
}

void StartGame::Refresh()
{
	SDL_Texture* BG = NULL;
	start = false;
	lv = 190;
	quitgame = false;
	check = true;
}