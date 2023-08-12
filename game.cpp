
#include "config.h"
#include "game.hpp"
#include "ball.hpp"
#include "block.hpp"

#include <iostream>
#include <list>
#include <cmath>

enum GameState {
    GS_AIM,
    GS_RUN
};

bool Game::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initalized!" << std::endl
                << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::cout << "SDL Image module could not be initalized!" << std::endl
                << "SDL Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("super monlky ball shooter :))",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                WINDOW_WIDTH, WINDOW_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(!window) {
        std::cout << "Window could not be created!" << std::endl
                << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cout << "Renderer could not be created!" << std::endl
                << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    textures = new Textures(renderer);
    textures->loadTextures();


    // seed random number generation
    srand(time(NULL));

    return true;
}

void Game::run() {
    bool quit = !init();
    if(quit) {
        std::cout << "Something wrent wrong during initialisation, exiting!" << std::endl;
    }

    GameState gameState = GS_AIM;

    int startX = WINDOW_WIDTH / 2;
    int startY = WINDOW_HEIGHT - 20;

    BlockMaster blocks;
    blocks.next(level);

    BallMaster balls(startX, startY);

    int mx = startX;
    int my = startY;

    bool fast = false;

    while(!quit) {
        SDL_Event e;
        // event handling
        while (SDL_PollEvent(&e)) {
            // handle all pending events
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_s) {
                    fast = false;
                }
            }
            if (gameState == GS_AIM) {
                if (e.type == SDL_MOUSEMOTION) {
                    mx = e.motion.x;
                    my = e.motion.y;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    gameState = GS_RUN;
                    float angle = atan((float)(mx-startX)/(float)(my-startY));
                    balls.reset(level, angle);
                }
            }
            if (gameState == GS_RUN) {
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_s) {
                        fast = true;
                    }
                }
            }
        }

        // game logic
        if (gameState == GS_RUN) {
            // move ball
            balls.move(blocks.blocklist);
            if (!balls.anyMoving()) {
                // turn is ending
                ++level;
                blocks.next(level);
                gameState = GS_AIM;
            }
        }

        // rendering
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        blocks.render(renderer, textures);

        if (gameState == GS_RUN) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
            // render balls
            balls.render(renderer, textures);
        }
        else if (gameState == GS_AIM) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20, mx, my);
        }
        SDL_RenderPresent(renderer);
        if (fast) {
            SDL_Delay(2);
        } else {
            SDL_Delay(1000/60);
        }
    }

    clean();
}

void Game::clean() {
    textures->free();
    IMG_Quit();
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
}
