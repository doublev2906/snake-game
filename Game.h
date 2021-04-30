#include"CommonFunction.h"
#include"SDL_setup.h"
#include"StartGame.h"

class Game: public StartGame
{
public:
	Game();
	~Game();
	void createSnake();
	void Input();
	void createFruit();
	bool eating();
	void movesnake();
	void viewScore(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	bool gameOver();
	void play(SDL_Renderer* renderer);
	void Setting(int lv);
	void refresh();
	void audio();

private:
	Snake snake_[1000];
	Fruit fruit_;
	SDL_Event event;
	int status;
	int oldstatus;
	int SC;
	int realsizesnake;
	bool is_create_fruit;
	int score;
	int delay;
	bool iswhite;
};

