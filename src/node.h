#pragma once
#include <SDL2/SDL.h>
#include "texture.h"
#include <string>
using namespace std;

struct Position {
    int x;
    int y;
};

class Node{
    private:
        SDL_Renderer * renderer;
        SDL_Color color;
        SDL_Texture * texture = nullptr;
        ~Node();

    public:
        SDL_Rect area;
        Position last_pos;
        Position current_pos;
        Node(TextureCache * cache, int x, int y, int w, int h, SDL_Color c = {0, 0, 0, 0}, string filepath = "");
        void Update(int x, int y);
        void Render();
};