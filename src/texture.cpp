#include "texture.h"

// Texture Cache

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

// Framebuffer

Framebuffers::Framebuffers(SDL_Window * window, SDL_Renderer * target) {
    renderer = target;
    pixel_format = SDL_GetWindowPixelFormat(window);
}

Framebuffers::~Framebuffers() {
    for (auto  & buffer: buffers){
        SDL_DestroyTexture(buffer);
    }
}

void Framebuffers::CreateFramebuffer(int width, int height) {
    buffers.push_back(SDL_CreateTexture(renderer, pixel_format, SDL_TEXTUREACCESS_TARGET, width, height));
}

int Framebuffers::SetFramebuffer(int i) {
    if (0 <= i < buffers.size()){
        SDL_SetRenderTarget(renderer, buffers[i]);
        return 1;
    }
    return 0;
}

void Framebuffers::UnsetFramebuffer() {
    SDL_SetRenderTarget(renderer, NULL);
}

int Framebuffers::RenderBuffer(int i, int x, int y, int w, int h) {
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
    if (0 <= i < buffers.size()){
        if (x==y==w==h==0){
            SDL_RenderCopy(renderer,buffers[i], NULL, NULL);
        } else{
            SDL_RenderCopy(renderer,buffers[i], NULL, &destination);
        }
        return 1;
    }
    return 0;
}
