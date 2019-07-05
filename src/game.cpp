#include "game.h"

int Game::Start(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO); //Initializes SDL2 with appropriate subsystems.

    //process command-line arguments.

    //set the width and height to user set resolution, or set it to constants
    WIDTH = 800, HEIGHT = 600;

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
    framebuffer = new Framebuffers(window, renderer);
    framebuffer->CreateFramebuffer(WIDTH, HEIGHT);
    clock = new Clock();
    cache = new TextureCache(renderer);


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
    cout << clock->dt_sec << '\n' << endl;
    //game logic and state

}

void Game::Render() {
    //state based rendering.
    SDL_RenderClear(renderer);

    framebuffer->SetFramebuffer(0);
    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
    SDL_RenderClear(renderer);

    //draw here...

    framebuffer->UnsetFramebuffer();
    framebuffer->RenderBuffer(0);
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
