#include<iostream>
#include<SDL2/SDL.h>

using namespace std;

SDL_Window *Window = nullptr;
SDL_Renderer *renderer = nullptr;

bool windowisrunning=false;

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH  500

bool initialization(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"SDL Failed To Initialize! SDL Error :"<<SDL_GetError()<<endl;
        return false;
    }
    Window = SDL_CreateWindow ("Draw Circle", SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_HEIGHT , SCREEN_WIDTH , SDL_WINDOW_SHOWN);

    if(!Window){
        cout<<"Failed To Open Window! SDL Error :"<<SDL_GetError()<<endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(Window , -1 , SDL_RENDERER_ACCELERATED);

    if(!renderer){
        cout<<"Failed To Create Renderer! SDL Error :"<<SDL_GetError()<<endl;
        return false;
    }


    return true;
}

int main(int argc, char* argv[]){
    windowisrunning = initialization();

    SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 ,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 ,255);
    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    return 0;
}