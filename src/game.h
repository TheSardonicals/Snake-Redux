#pragma once
//SDL2
#include <SDL2/SDL.h>
//Game Includes
#include "clock.h"
#include "texture.h"
//Standard
#include <iostream>
using namespace std;


class Game {
    private:
        SDL_Window * window;       // window handle
        SDL_Renderer * renderer;  // renderer handle
        SDL_Event event;          // event handle

        //resolution
        int WIDTH , HEIGHT;

        //game variables
        bool finished = false;

        //game objects
        Clock * clock;      
        TextureCache * cache;
        Framebuffers * framebuffer;
        
        //enums and structs
        enum GameState {
            MAIN_MENU = 0,
            CLASSIC_MODE = 1,
            REDUX_MODE = 2,
        } game_mode;
        enum Difficulty {
            NORMAL = 0,
            HARD = 1,
        } difficulty;

        //private functions
        void Logic();
        void Render();
        ~Game();
    public:
        bool running;
        Game();
        int Start(int argc, char** argv);
        void Loop();
        void End();

};