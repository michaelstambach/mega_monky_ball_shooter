
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

    return true;
}

void Game::run() {
    bool quit = !init();
    if(quit) {
        std::cout << "Something wrent wrong during initialisation, exiting!" << std::endl;
    }

    GameState gameState = GS_AIM;
    
    std::list<Block> blocks;
    for (int x = 10; x < 450; x += 42) {
        blocks.push_back(Block(x, 200, 5));
    }

    int startX = WINDOW_WIDTH / 2;
    int startY = WINDOW_HEIGHT - 20;

    BallMaster balls(startX, startY);
    balls.addBalls(9);

    int mx = startX;
    int my = startY;

    while(!quit) {
        SDL_Event e;
        // event handling
        while (SDL_PollEvent(&e)) {
            // handle all pending events
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (gameState == GS_AIM) {
                if (e.type == SDL_MOUSEMOTION) {
                    mx = e.motion.x;
                    my = e.motion.y;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    gameState = GS_RUN;
                    float angle = atan((float)(mx-startX)/(float)(my-startY));
                    balls.reset(angle);
                }
            }
        }

        // game logic
        if (gameState == GS_RUN) {
            // move ball
            balls.move(blocks);
            blocks.remove_if([](Block b){ return b.health == 0;});
            if (!balls.anyMoving()) gameState = GS_AIM;
        }

        // rendering
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        for (auto block = blocks.begin(); block != blocks.end(); ++block) {
            block->render(renderer);
        }

        if (gameState == GS_RUN) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
            // render balls
            balls.render(renderer);
        }
        else if (gameState == GS_AIM) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20, mx, my);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }

    clean();
}

void Game::clean() {
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
}
