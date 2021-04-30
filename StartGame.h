#ifndef START_GAME_H_
#define	START_GAME_H_

#include"CommonFunction.h"
#include"SDL_setup.h"


class StartGame
{
public:
	StartGame();
	~StartGame();

	bool quitgame;
	bool start;
	int lv;
	void loadBackGround(SDL_Renderer* ren);
	void mainMenu(SDL_Renderer* renderer);
	void select(SDL_Renderer* renderer);
	void createLevel(SDL_Renderer* renderer);
	void Refresh();
protected:
	bool check;
	SDL_Texture* BG;
	SDL_Event ev;
	SDL_Texture* white;
	SDL_Texture* red;
	
};



#endif // !START_GAME_H_
