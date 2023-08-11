#include "config.h"
#include "block.hpp"

#include <iostream>
#include <bitset>

Block::Block(int x, int y, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = BLOCK_SIZE;
    rect.h = BLOCK_SIZE;
    health = h;
}

void Block::render(SDL_Renderer* renderer) {
    if (health > 0) SDL_RenderDrawRect(renderer, &rect);
}

void Block::hit() {
    health--;
}

BlockMaster::BlockMaster() {
    block_gap = (WINDOW_WIDTH - BLOCK_COLS * BLOCK_SIZE) / (BLOCK_COLS + 1);
    block_interval = BLOCK_SIZE + block_gap;
}

void BlockMaster::next(int level) {
    // move blocks down
    for (auto &block: blocklist) {
        block.rect.y += block_interval;
    }
    for (int i = 0; i < BLOCK_COLS; i++) {
        if (rand() % 2) {
            blocklist.push_back(Block(block_gap + block_interval * i, 10, level));
        }
    }
    blocklist.remove_if([](Block b){ return b.health == 0;});
}

void BlockMaster::render(SDL_Renderer *renderer) {
    for (auto &block : blocklist) {
        block.render(renderer);
    }
}
