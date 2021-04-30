#include "Game.h"

Game::Game()
{
	snake_[0].x = 20;
	snake_[0].y = 20;
	status = 0;
	oldstatus = -1;
	SC = 0;
	realsizesnake = START_SIZE_SNAKE;
	fruit_.x = 0;
	fruit_.y = 0;
	is_create_fruit = true;
	iswhite = true;
}

Game::~Game()
{
	
}

void Game::Setting(int lv)
{
	score = (lv - 140) / 50;
	if (score == 1) delay = 100;
	else if (score == 2) delay = 90;
	else if (score == 3) delay = 80;
	else if (score == 4) delay = 70;
	else if (score == 5) delay = 50;
}


void Game::createSnake()
{
	for (int i = realsizesnake; i > 0; i--)
	{
		snake_[i].x = snake_[i - 1].x;
		snake_[i].y = snake_[i - 1].y;
	}
}

void Game::Input()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_DOWN:
			status = 0;
			break;
		case SDLK_UP:
			status = 1;
			break;
		case SDLK_RIGHT:
			status = 2;
			break;
		case SDLK_LEFT:
			status = 3;
			break;
		}
	}
}

void Game::movesnake()
{
	if (status == 0) snake_[0].y += 20;
	else if (status == 1) snake_[0].y -= 20;
	else if (status == 2) snake_[0].x += 20;
	else if (status == 3) snake_[0].x -= 20;
}

void Game::createFruit()
{
	if (is_create_fruit == true)
	{
		fruit_.x = rand() % ((SCREEN_WIDTH-20-20)/SIZE_SNAKE) ;
		fruit_.y = rand() % ((SCREEN_HEIGHT-50-40-20)/SIZE_SNAKE) ;
		is_create_fruit = false;
	}
	else if (eating() == true)
	{
		fruit_.x = 2+rand() % ((SCREEN_WIDTH - 20-20) / SIZE_SNAKE);
		fruit_.y = 2 + rand() % ((SCREEN_HEIGHT - 50 - 40-20) / SIZE_SNAKE);
		realsizesnake++;
		SC += score;
	}
}

bool Game::eating()
{
	if (snake_[0].x == fruit_.x * 20 && snake_[0].y == fruit_.y * 20) return true;
	
	return false;
}

void Game::viewScore(SDL_Renderer* renderer)
{
	SDL_Color white = { 255, 255, 255 };
	string result;
	ostringstream convert;
	convert << SC;
	result = convert.str();
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect rect = { 0,600,SCREEN_WIDTH,50 };
	SDL_RenderFillRect(renderer, &rect);
	createText("SCORE: ", renderer, 0, 600, 100, 50,white);
	createText(result, renderer,120, 600, 50, 50,white);
}

bool Game::gameOver()
{
	for (int i = 2; i < realsizesnake; i++)
	{
		if (snake_[0].x == snake_[i].x && snake_[0].y == snake_[i].y) return true;
	}
	if (snake_[0].x >= (SCREEN_WIDTH-20) || snake_[0].y >= (SCREEN_HEIGHT - 50-20) || snake_[0].x < 20|| snake_[0].y < 20) return true;
	return false;
}

void Game::draw(SDL_Renderer* renderer)
{
	
	SDL_Texture* background = loadTexture("background.bmp", renderer);
	SDL_Texture* sprite = loadTexture("snake.png", renderer);
	SDL_Texture* wall = loadTexture("wall.png", renderer);

	//draw background
	renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 50);
	for (int i = 0; i < SCREEN_WIDTH; i += 20)
	{
		renderTexture(wall, renderer, i, 0, 20, 20);
		renderTexture(wall, renderer, i, 580, 20, 20);
	}
	for (int i = 0; i < (SCREEN_HEIGHT-50-20); i += 20)
	{
		renderTexture(wall, renderer, 0, i, 20, 20);
		renderTexture(wall, renderer, 780, i, 20, 20);
	}


	SDL_Rect FR1 = { 0,192,64,64 };
	SDL_Rect FR2 = { fruit_.x*20,fruit_.y*20,20,20 };
	SDL_RenderCopy(renderer, sprite, &FR1, &FR2);

	//draw//

	for (int i = 0; i < realsizesnake; i++)
	{
		int segx = snake_[i].x;
		int segy = snake_[i].y;

		int tx = 0;
		int ty = 0;

		//head
		if (i == 0)
		{
			int nsegx = snake_[i + 1].x;
			int nsegy = snake_[i + 1].y;
			if (segy < nsegy) {
				// Up
				tx = 3; ty = 0;
			}
			else if (segx > nsegx) {
				// Right
				tx = 4; ty = 0;
			}
			else if (segy > nsegy) {
				// Down
				tx = 4; ty = 1;
			}
			else if (segx < nsegx) {
				// Left
				tx = 3; ty = 1;
			}
		}

		else if (i == realsizesnake - 1)
		{
			int psegx = snake_[i - 1].x;
			int psegy = snake_[i - 1].y;

			if (psegy < segy) {
				// Up
				tx = 3; ty = 2;
			}
			else if (psegx > segx) {
				// Right
				tx = 4; ty = 2;
			}
			else if (psegy > segy) {
				// Down
				tx = 4; ty = 3;
			}
			else if (psegx < segx) {
				// Left
				tx = 3; ty = 3;
			}
		}

		else
		{
			int nsegx = snake_[i + 1].x;
			int nsegy = snake_[i + 1].y;

			int psegx = snake_[i - 1].x;
			int psegy = snake_[i - 1].y;

			if (psegx < segx && nsegx > segx || nsegx < segx && psegx > segx) {
				// Horizontal Left-Right
				tx = 1; ty = 0;
			}
			else if (psegx < segx && nsegy > segy || nsegx < segx && psegy > segy) {
				// Angle Left-Down
				tx = 2; ty = 0;
			}
			else if (psegy < segy && nsegy > segy || nsegy < segy && psegy > segy) {
				// Vertical Up-Down
				tx = 2; ty = 1;
			}
			else if (psegy < segy && nsegx < segx || nsegy < segy && psegx < segx) {
				// Angle Top-Left
				tx = 2; ty = 2;
			}
			else if (psegx > segx && nsegy < segy || nsegx > segx && psegy < segy) {
				// Angle Right-Up
				tx = 0; ty = 1;
			}
			else if (psegy > segy && nsegx > segx || nsegy > segy && psegx > segx) {
				// Angle Down-Right
				tx = 0; ty = 0;
			}
		}


		SDL_Rect src = { tx * 64,ty * 64,64,64 };
		SDL_Rect dst = { snake_[i].x,snake_[i].y,20,20 };
		SDL_RenderCopy(renderer, sprite, &src, &dst);
	}


	viewScore(renderer);
	if (gameOver())
	{
		SDL_Texture* endgame = loadTexture("gameover.bmp", renderer);
		renderTexture(endgame, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	SDL_RenderPresent(renderer);
	iswhite = !iswhite;
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(sprite);
	SDL_DestroyTexture(wall);
}

void Game::audio()
{
	
}


void Game::play(SDL_Renderer* renderer)
{
	bool is_quit = false;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	
	Mix_Music* music = NULL;
	Mix_Music* gameover = NULL;
	Mix_Music* eat = NULL;


	
	music = Mix_LoadMUS("background_music.mp3");
	gameover = Mix_LoadMUS("game_over.mp3");
	eat = Mix_LoadMUS("eat.mp3");

	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}

	Mix_ResumeMusic();
	
	//if (gameOver()) Mix_PauseMusic();
	
	while (!is_quit)
	{
		if (Mix_PlayingMusic() == 0) Mix_PlayMusic(music, -1);
		oldstatus = status;
		srand((int) time(0));
		SDL_Delay(delay);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			Input();
		}
		if (oldstatus == 2 && status == 3 || oldstatus == 3 && status == 2 || oldstatus == 0 && status == 1 || oldstatus == 1 && status == 0) status = oldstatus;
		createSnake();
		movesnake();
		createFruit();
		draw(renderer);
		if (gameOver())
		{
			if (Mix_PlayingMusic() == 1) Mix_PlayMusic(gameover, 0);
			SDL_RenderClear(renderer);
			//Mix_HaltMusic();
			break;
		}
		SDL_RenderClear(renderer);
	}
}

void Game::refresh()
{
	snake_[0].x = 20;
	snake_[0].y = 20;
	status = 0;
	oldstatus = -1;
	SC = 0;
	realsizesnake = START_SIZE_SNAKE;
	fruit_.x = 0;
	fruit_.y = 0;
	is_create_fruit = true;
	iswhite = true;
}


