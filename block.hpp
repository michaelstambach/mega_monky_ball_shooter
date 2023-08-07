#pragma once

#include <SDL2/SDL.h>

class Block {
    public:
        static const int BLOCK_WIDTH = 32;
        static const int BLOCK_HEIGHT = 32;
        Block(int x, int y, int h);
        SDL_Rect rect;
        int health;
        void render(SDL_Renderer* renderer);
        void hit();
};