#include "game.h"

int Game::Start(int argc, char** argv) {
    //Initialize SDL2 with appropriate subsystems.
    SDL_Init(SDL_INIT_VIDEO); 

    //process command-line arguments.

    //set the width and height to user set resolution, or set it to constants
    SetResolution();

    //create window
    window = SDL_CreateWindow("Snake Redux - By Sardonicals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
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
    game_mode = CLASSIC_MODE;

    //initialize various objects
    framebuffer = new Framebuffers(window, renderer);
    framebuffer->CreateFramebuffer(WIDTH, HEIGHT);
    clock = new Clock();
    cache = new TextureCache(renderer);

    snake = new Snake(clock, cache, 20, 100, 100, "RIGHT", SDL_Color({0, 255, 0, 255}));

    return 1;
}


void Game::Logic() {
    //no matter how the window is resized, the aspect ratio should remain the same.
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    //timer update
    clock->Tick();
    //event loop
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }
        if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                SetFullscreen();
            }
        }
    }
    cout << clock->dt_sec << '\n' << endl;

    //game logic and state
    keystate = SDL_GetKeyboardState(NULL);
    if (game_mode == CLASSIC_MODE){

        //process the snake.
        snake->Process(false, WIDTH, HEIGHT);

        if (keystate[SDL_SCANCODE_W]) {
            snake->movement = true;
            snake->direction = "UP";
        }
        if(keystate[SDL_SCANCODE_S]){
            snake->movement = true;
            snake->direction = "DOWN";
        }
        if (keystate[SDL_SCANCODE_A]){
            snake->movement = true;
            snake->direction = "LEFT";
        }
        if (keystate[SDL_SCANCODE_D]){
            snake->movement = true;
            snake->direction = "RIGHT";
        }
    }


}

void Game::Render() {
    //state based rendering.
    framebuffer->SetFramebuffer(0);
    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
    SDL_RenderClear(renderer);

    //draw here...
    if (game_mode == CLASSIC_MODE){
        snake->Render();
    }

    framebuffer->UnsetFramebuffer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    framebuffer->RenderBuffer(0, 0, 0, WIDTH, HEIGHT);
    SDL_RenderPresent(renderer);
}

void Game::Loop() {
    while (running){
        Logic();
        Render();

    }
}

void Game::End() {
    delete snake;
    delete cache;
    delete clock;
    delete framebuffer;
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

//allows for the toggling of fullscreen for the game.
void Game::SetFullscreen(){
    if (!fullscreen){
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullscreen = true;
    }
    else if (fullscreen){
        SDL_SetWindowFullscreen(window, 0);
        fullscreen = false;
    }
}

//sets the default resolution when the game starts.
void Game::SetResolution(){
    WIDTH = 1024, HEIGHT = 576;
    SCREEN_W = WIDTH, SCREEN_H = HEIGHT;
    #ifdef MOBILE
    SDL_Rect display;
    SDL_GetDisplayBounds(0, &display);
    if (display.h > display.w)
        SCREEN_W = display.h, SCREEN_H = display.w;
    else
        SCREEN_W = display.w, SCREEN_H = display.h;
    #endif
}