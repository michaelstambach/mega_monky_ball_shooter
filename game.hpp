
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.hpp"

class Game {
    public:
        void run();
    private:
        bool init();
        void clean();
        SDL_Window *window;
        SDL_Renderer *renderer;
        Textures *textures;
        int level = 1;
};
