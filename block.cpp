
#include "block.hpp"

#include <iostream>

Block::Block(int x, int y, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    health = h;
}

void Block::render(SDL_Renderer* renderer) {
    SDL_RenderDrawRect(renderer, &rect);
}

void Block::hit() {
    health--;
}
