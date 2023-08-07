
#include <SDL2/SDL.h>

class Game {
    public:
        void run();
    private:
        bool init();
        void clean();
        SDL_Window *window;
        SDL_Renderer *renderer;
        int level = 1;
};
