#include "game.h"

int Game::Start(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO); //Initializes SDL2 with appropriate subsystems.

    //process command arguments

    //set the width and height to user set resolution, or set it to constants
    WIDTH = 640, HEIGHT = 480;

    //create window
    window = SDL_CreateWindow("Snake Redux", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT, 0);
    if (!window){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Couldn't create window!", SDL_GetError(), NULL);
        return 0;
    }

    //create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
         SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Couldn't create renderer!", SDL_GetError(), NULL);
        return 0;
    }

    //create event queue
    event = SDL_Event();

    //set defaults for various variables (alliteration ftw)
    running = true;

    //initialize various objects
    clock = new Clock();

}


void Game::Logic() {
    //timer update
    clock->Tick();
    //event loop
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }
    }
    cout << clock->dt << '\n' << endl;
    //game logic and state

}

void Game::Render() {
    //state based rendering.
    SDL_RenderClear(renderer);

    //draw here...

    SDL_RenderPresent(renderer);
}

void Game::Loop() {
    while (running){
        Logic();
        Render();
        // SDL_Delay(10);
    }
}

void Game::End() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    finished = true;
}

Game::Game() {
    
}

Game::~Game() {
    if (!finished)
        End();
}
