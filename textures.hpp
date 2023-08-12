#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Textures {
    public:
        Textures(SDL_Renderer* renderer);
        void loadTextures();
        void renderText(int x, int y, const char* text);
        void free();
        SDL_Texture *ball;
        SDL_Texture *block;
        SDL_Texture *font;
    private:
        SDL_Renderer *renderer;
};

