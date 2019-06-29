#include <SDL2/SDL.h>
//Standard
using namespace std;

//Event Filter (for mobile devices)
int Filter(void* userdata, SDL_Event* event){
    bool * running = static_cast<bool*>(userdata);
    switch(event->type) {
        case SDL_APP_WILLENTERBACKGROUND:
            *running = false;
            return 0;
        case SDL_APP_WILLENTERFOREGROUND:
            *running = true;
            return 0;
        default:
            return 1;
    }
}

//Globals
int WIDTH, HEIGHT;

int main(int argc, char** argv){

    SDL_Init(SDL_INIT_VIDEO);

     int WIDTH, HEIGHT;
    //SDL
    SDL_Window * window;      // window handle
    SDL_Renderer * renderer;  // renderer handle
    SDL_Event event;         // event handle

    WIDTH, HEIGHT = 640, 480;
    window = SDL_CreateWindow("Snake Redux", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                WIDTH, HEIGHT, 0);
    
    if (!window){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Couldn't create window!", SDL_GetError(), NULL);
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    event = SDL_Event();
    bool running = true;

    SDL_SetEventFilter(Filter, (void *)running);

    //Game Loop
    while (running){
        //Event Loop
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
                break;
            }
        }
        //LOGIC
        //Any game logic goes right over here


        //RENDERING
        SDL_RenderClear(renderer);

        //Any rendering code goes in here

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;   
}