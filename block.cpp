
#include "block.hpp"

#include <iostream>
#include <bitset>

Block::Block(int x, int y, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    health = h;
}

void Block::render(SDL_Renderer* renderer) {
    if (health > 0) SDL_RenderDrawRect(renderer, &rect);
}

void Block::hit() {
    health--;
}

void BlockMaster::next(int level) {
    // move blocks down
    for (auto &block: blocklist) {
        block.rect.y += 40;
    }
    for (int i = 0; i < 12; i++) {
        if (rand() % 2) {
            blocklist.push_back(Block(5 + 40 * i, 10, level));
        }
    }
    blocklist.remove_if([](Block b){ return b.health == 0;});
}

void BlockMaster::render(SDL_Renderer *renderer) {
    for (auto &block : blocklist) {
        block.render(renderer);
    }
}
