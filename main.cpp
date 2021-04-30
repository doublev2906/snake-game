#include"SDL_setup.h"
#include"CommonFunction.h"
#include"StartGame.h"
#include"Game.h"




int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer);
	// Your drawing code here
	StartGame gamestart;
	Game PLAY;
	
	bool start = false;
	while (!start)
	{
		PLAY.refresh();
		gamestart.Refresh();
		gamestart.mainMenu(renderer);
		gamestart.select(renderer);
		if (gamestart.quitgame == true)
		{
			break;
		}
		if (gamestart.start == true)
		{
			PLAY.Setting(gamestart.lv);
			PLAY.play(renderer);
			if (PLAY.gameOver())
			{
				SDL_Delay(5000);
				continue;
			}
		}
	}


	// use SDL_RenderPresent(renderer) to show it
	//waitUntilKeyPressed();
	SDL_Delay(300);
	quitSDL(window, renderer);
	return 0;
}

