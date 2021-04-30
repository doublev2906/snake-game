#ifndef SDL_SETUP_H_
#define SDL_SETUP_H_

#include <iostream>
#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include <SDL.h>
#include<SDL_image.h>
#include<string>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<sstream>

#define SIZE_SNAKE 20
#define START_SIZE_SNAKE 6

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "SNAKE";



typedef struct
{
	int x;
	int y;
}Fruit;

typedef struct
{
	int x;
	int y;
}Snake;



//************************************

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();


#endif // SDL_SETUP_H_
