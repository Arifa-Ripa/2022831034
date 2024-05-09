#include<iostream>
#include<SDL2/SDL.h>

using namespace std;

SDL_Window *Window = nullptr;
SDL_Renderer *renderer = nullptr;

bool windowisrunning=false;

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH  720

int centerX = SCREEN_WIDTH/2;
int centerY = SCREEN_HEIGHT/2;

int center2X = SCREEN_WIDTH/2;
int center2Y = 0;

int Radius = 10;
int Speed = 1;

bool initialization(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"SDL Failed To Initialize! SDL Error :"<<SDL_GetError()<<endl;
        return false;
    }
    Window = SDL_CreateWindow ("Circle Collision", SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN);

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

void moveCircle1(){
    centerX +=Speed;
    if(centerX == SCREEN_WIDTH){
        centerX = 0;
    }
    SDL_Delay(11);
}
void moveCircle2(SDL_Event &e){
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_RIGHT: 
                if(center2X+Speed+Radius<=SCREEN_WIDTH){
                    center2X+=Speed;
                }
                break;
            
            case SDLK_LEFT: 
                if(center2X-Speed -Radius>=0){
                    center2X-=Speed;
                }
                break;

            case SDLK_UP:
                if(center2Y-Speed-Radius>=0){
                    center2Y-=Speed;
                }
                break;
            
            case SDLK_DOWN: 
                if(center2Y+Speed+Radius<=SCREEN_HEIGHT){
                    center2Y+=Speed;
                }
                break;

            default :
                break;
        }
    }

    return;
}

bool checkcollision(){
    int x=centerX - center2X;
    int y=centerY - center2Y;
    int d=x*x + y*y;
    int r=(2*Radius)*(2*Radius);

    return d<=r;
}

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
            moveCircle2(e);
            
        }
        if(checkcollision()){
            SDL_SetRenderDrawColor(renderer , 255 , 0 , 0 ,255);
        }
        else {
            SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 ,255);
        }

        
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 ,255);
        drawCircle(centerX , centerY , Radius);
        moveCircle1();
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 ,255);
        drawCircle(center2X , center2Y , Radius);
       
        SDL_RenderPresent(renderer);

    }

    

    close();

    return 0;
}