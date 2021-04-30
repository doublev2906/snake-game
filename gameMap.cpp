#include"gameMap.h"

void buildMap(SDL_Renderer* renderer)
{
    SDL_Texture* white = loadTexture("white.bmp",renderer);
    if(white == nullptr)
    {
        SDL_DestroyTexture(white);
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    for(int i = 0;i<SCREEN_WIDTH;i+=SIZE_SNAKE)
    {
     for(int j = 0;j<SCREEN_HEIGHT;j+=SIZE_SNAKE)
     {
         renderTexture(white,renderer,i,j,SIZE_SNAKE,SIZE_SNAKE);
     }
    }

}
