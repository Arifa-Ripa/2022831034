#include<iostream>
#include<SDL2/SDL.h>

using namespace std;

SDL_Window *Window = nullptr;
SDL_Renderer *renderer = nullptr;

bool windowisrunning=false;

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH  500

int centerX = SCREEN_WIDTH/2;
int centerY = SCREEN_HEIGHT/2;
int Radius = 10;
int Speed = 1;

bool initialization(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"SDL Failed To Initialize! SDL Error :"<<SDL_GetError()<<endl;
        return false;
    }
    Window = SDL_CreateWindow ("Move Circle", SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_HEIGHT , SCREEN_WIDTH , SDL_WINDOW_SHOWN);

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


void drawCircle(int x , int y , int r){
    int centerx = x;
    int centery = y;
    int radius = r;

    for(int dx = -r ; dx <= r ; dx++){
        for(int dy = -r ; dy <= r ; dy++){
            if(dx*dx + dy*dy <= r*r){
                SDL_RenderDrawPoint(renderer , centerx+dx , centery+dy);
            }
        }
    }

    return ;
}

void moveCircle(){
    centerX +=Speed;
    if(centerX == SCREEN_WIDTH){
        centerX = 0;
    }
}
/*void moveCircle(SDL_Event &e){
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_RIGHT: 
                if(centerX+Speed+Radius<=SCREEN_WIDTH){
                    centerX+=Speed;
                }
                break;
            
            case SDLK_LEFT: 
                if(centerX-Speed -Radius>=0){
                    centerX-=Speed;
                }
                break;
            
            default :
                break;
        }
    }

    return;
}*/

void close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(Window);
    Window = nullptr;
    renderer = nullptr;

    SDL_Quit();
}

int main(int argc, char* argv[]){
    
    windowisrunning = initialization();

    bool quit = false;
    SDL_Event e;
    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT){
                quit = true;
            }

            
        }

        SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 ,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 ,255);
        drawCircle(centerX , centerY , Radius);
        moveCircle();
        SDL_RenderPresent(renderer);

    }

    

    close();

    return 0;
}