#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <map>
using namespace std;

// used for many texture loading operation. this stores the texture data that we load for reuse.
class TextureCache {
    private:
        map<string, SDL_Texture *> textures;
        ~TextureCache();
    public:
        SDL_Renderer * renderer;
        TextureCache(SDL_Renderer * referenced_renderer);
        SDL_Texture * LoadTexture(string filepath);
};