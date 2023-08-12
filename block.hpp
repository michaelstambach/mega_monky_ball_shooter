#pragma once

#include <SDL2/SDL.h>
#include <list>
#include "textures.hpp"

class Block {
    public:
        Block(int x, int y, int h);
        SDL_Rect rect;
        int health;
        void render(SDL_Renderer* renderer, Textures* textures);
        void hit();
};


class BlockMaster {
    public:
        BlockMaster();
        void next(int level);
        void render(SDL_Renderer* renderer, Textures* textures);
        std::list<Block> blocklist;
    private:
        int block_gap = 0;
        int block_interval = BLOCK_SIZE;
};
