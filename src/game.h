#pragma once
//SDL2
#include <SDL2/SDL.h>
//Game Includes
#include "clock.h"
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
        //general variables
        bool finished = false;
        //general objects
        Clock * clock;
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