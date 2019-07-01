#include "texture.h"


TextureCache::TextureCache(SDL_Renderer * referenced_renderer) {
    renderer = referenced_renderer;
}

TextureCache::~TextureCache(){
    for (auto const& texture: textures){
        SDL_DestroyTexture(texture.second);
    }
}

SDL_Texture * TextureCache::LoadTexture(string filepath) {
    if (textures.find(filepath) == textures.end()){
        SDL_Surface * surface = SDL_LoadBMP(filepath.c_str());
        textures[filepath] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        // add support for various blend modes for the texture.
        SDL_SetTextureBlendMode(textures[filepath], SDL_BLENDMODE_BLEND); // alpha blending (transparency)
        SDL_SetTextureBlendMode(textures[filepath], SDL_BLENDMODE_ADD);   // additive blending (from combinations of colors. used for lighting.)
        SDL_SetTextureBlendMode(textures[filepath], SDL_BLENDMODE_MOD);   // color modulation (exaggerated base color).
    }
    return textures[filepath];
}
