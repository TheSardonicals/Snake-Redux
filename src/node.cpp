#include "node.h"


Node::~Node() {
}

Node::Node(TextureCache * cache, int x, int y, int w, int h, SDL_Color c, string filepath) {
    current_pos = {x, y};
    last_pos = {x, y};
    area = {x, y, w, h};
    color = c;
    renderer = cache->renderer;
    if (filepath != ""){
        texture = cache->LoadTexture(filepath);
    }
}

void Node::Update(int x, int y){
    last_pos.x = current_pos.x;
    last_pos.y = current_pos.y;

    area.x = x;
    area.y = y;
    current_pos.x = area.x;
    current_pos.y = area.y;
}

void Node::Render(){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &area);
    if (texture)
        SDL_RenderCopy(renderer, texture, NULL, &area);
}

