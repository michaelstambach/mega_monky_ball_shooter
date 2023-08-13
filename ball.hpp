
#include <SDL2/SDL.h>
#include <list>
#include "textures.hpp"
#include "block.hpp"

enum BallState {
    BALL_MOVE,
    BALL_READY,
    BALL_DEAD
};

class Ball {
    public:
        Ball(int x, int y);
        // move and collide
        void move(std::list<Block> &blocks);
        // render the ball
        void render(SDL_Renderer* renderer, Textures* textures);
        BallState state;
        // position, should be private maybe idk if useful
        float px, py;
        // velocity
        float vx, vy;
};

class BallMaster {
    public:
        BallMaster(int sy);
        void addBalls(int count);
        void reset(int level, float angle, int startX);
        void move(std::list<Block> &blocks);
        void render(SDL_Renderer* renderer, Textures* textures);
        bool anyMoving();
        void updateStartPos(int &startX);
    private:
        std::list<Ball> balls;
        Ball *firstBall;
        Ball *lastBall;
        int sty;
};
