#include "node.h"
#include "clock.h"

class Snake{
    private:
        //private variables
        double seconds_passed;
        double update_time;
        double update_rate;
        Clock * clock;
        SDL_Color body_color;
        TextureCache * cache;
        int limit;
        int move_px;
        //private functions
        void Move();
        void SpeedUp();

    public:
        //public variables
        vector<Node *> body;
        Node * head;
        int size;
        bool movement = false;
        string direction;

        //public functions
        Snake(Clock * c, TextureCache* ca, int s, int x, int y, string d, SDL_Color head_color, int movement_space = NULL);
        void Process(bool wall, int bound_width, int bound_height);
        void Grow(int amount = 1);
        void Render();
        bool TouchingItself();
};