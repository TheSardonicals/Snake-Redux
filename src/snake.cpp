#include "snake.h"


Snake::Snake(Clock * c, TextureCache* ca, int s, int x, int y, string d, SDL_Color head_color, int movement_space) {
    size = s;
    clock = c;
    direction = d;
    cache = ca;
    body_color = {  head_color.r,
                    head_color.g, 
                    head_color.b,
                    head_color.a};
    if (head_color.r > 100){body_color.r = body_color.r - 50;}
    if (head_color.g > 100){body_color.g = body_color.g - 50;}
    if (head_color.b > 100){body_color.b = body_color.b - 50;}

    //timer related variables initialized
    seconds_passed = 0;
    limit = 0;
    update_time = .07;
    update_rate = 1.6;

    //initialize snake with body.
    body.resize(2); 
    body[0] = new Node(cache, x, y, size, size, head_color);
    if (direction == "LEFT"){
        body[1] = new Node(cache, x + size, y, size, size, body_color);
    }
    else if (direction== "RIGHT") {
        body[1] = new Node(cache, x - size, y, size, size, body_color);
    }
    else if (direction == "UP") {
        body[1] = new Node(cache, x, y + size, size, size, body_color);
    }
    else {
        body[1] = new Node(cache, x, y - size, size, size, body_color);
    }
    
    head = body[0];

    //this determines how many pixels the snake moves on an update period.
    move_px = size;
    if (movement_space)
        move_px = movement_space;
}

void Snake::Process(bool wall, int bound_width, int bound_height) {
    if (movement){
        Move();
    }
}

void Snake::Move() {
    seconds_passed += (clock->dt_sec * update_rate);

    if (seconds_passed >= update_time){
        seconds_passed = 0;
        
        //move the snake head based on the direction.
        if (direction == "LEFT") {
            head->Update(head->area.x - move_px, head->area.y);
        }
        else if (direction == "RIGHT"){
            head->Update(head->area.x + move_px, head->area.y);
        }
        else if (direction == "UP"){
            head->Update(head->area.x, head->area.y - move_px);
        }
        else if (direction == "DOWN") {
            head->Update(head->area.x, head->area.y + move_px);
        }

        //have the body follow the head in the same update period.
        for (int i = 1; i < body.size();  i++){
            body[i]->Update(body[i-1]->last_pos.x, 
                            body[i-1]->last_pos.y);
        }

    }
    
}

void Snake::Grow(int amount) {
    for (int i = 0; i < amount; i++)
        body.push_back(new Node(cache, body.back()->last_pos.x, body.back()->last_pos.y,
                                size, size, body_color));
    limit++;
}

void Snake::Render() {
    for (auto * part : body)
        part->Render();
}

bool Snake::TouchingItself() {
    
}
