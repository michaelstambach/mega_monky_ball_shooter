
#include "textures.hpp"

Textures::Textures(SDL_Renderer *rendererer) {
    renderer = rendererer;
}

void Textures::loadTextures() {
    bg = IMG_LoadTexture(renderer, "textures/bg.png");
    ball = IMG_LoadTexture(renderer, "textures/ball.png");
    block = IMG_LoadTexture(renderer, "textures/block.png");
    monkey = IMG_LoadTexture(renderer, "textures/monkey.png");
    arrow = IMG_LoadTexture(renderer, "textures/arrow.png");
    font = IMG_LoadTexture(renderer, "font/font.png");
}

void Textures::renderText(int x, int y, const char* text) {
    int i = 0;
    char c = text[i];
    while(c != '\0'){
        SDL_Rect srcRect = { 8*(c - 32), 0, 8, 16 };
        SDL_Rect dstRect = { x + i*8, y, 8, 16 };
        SDL_RenderCopy(renderer, font, &srcRect, &dstRect);
        c = text[++i];
    }
}

void Textures::free() {
    SDL_DestroyTexture(ball);
}
