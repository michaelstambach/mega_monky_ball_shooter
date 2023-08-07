
#include "config.h"
#include "ball.hpp"

int dist2(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return (dx * dx) + (dy * dy);
}

Ball::Ball(int x, int y) {
    px = x;
    py = y;
    // for now
    vx = 0;
    vy = 0;
    state = BALL_READY;
}

void Ball::move(std::list<Block> &blocks) {
    // only move when ball should move
    if (state != BALL_MOVE) return;

    // what would the next position be
    int nx = px + vx;
    int ny = py + vy;
    
    // check if inside screen
    if ((nx < BALL_RADIUS) || ((WINDOW_WIDTH - nx) < BALL_RADIUS)) {
        // left, right
        vx = -vx;
    }
    if (ny < BALL_RADIUS) {
        // top
        vy = -vy;
    }
    else if ((WINDOW_HEIGHT - ny) < BALL_RADIUS) {
        // bottom, ball dies
        state = BALL_DEAD;
    }

    // check collision with rects
    int r2 = BALL_RADIUS * BALL_RADIUS;
    for (std::list<Block>::iterator block = blocks.begin(); block != blocks.end(); ++block) { // huh?
        if (block->health <= 0) continue;
        SDL_Rect rect = block->rect;
        // determine closest point
        int cx, cy;
        if (nx < rect.x) {
            cx = rect.x;
        }
        else if (nx < rect.x + rect.w) {
            cx = nx;
        }
        else {
            cx = rect.x + rect.w;
        }
        if (ny < rect.y) {
            cy = rect.y;
        }
        else if (ny < rect.y + rect.h) {
            cy = ny;
        }
        else {
            cy = rect.y + rect.w;
        }

        // has collided?
        if (dist2(nx, ny, cx, cy) < r2) {
            block->hit();
            if (cx == nx) {
                vy = -vy;
            }
            else if (cy == ny) {
                vx = -vx;
            }
        }
    }

    px += vx;
    py += vy;

    // std::cout << "new ball position is: " << px << " "<< py 
    // << ", velocity is" << vx << " " << vy << std::endl;
}

void Ball::render(SDL_Renderer* renderer) {
    // ball is only visible when moving
    if (state != BALL_MOVE) return;
    SDL_Rect ballRect {
        (int)px - BALL_RADIUS,
        (int)py - BALL_RADIUS,
        2 * BALL_RADIUS,
        2 * BALL_RADIUS
    };
    SDL_RenderFillRect(renderer, &ballRect);
}

BallMaster::BallMaster(int sx, int sy) {
    // this already adds one ball to prevent unitilaize pointer :D
    stx = sx;
    sty = sy;
    Ball ball = Ball(sx, sy);
    balls.push_back(ball);
    lastBall = &ball;
}

void BallMaster::addBalls(int count) {
    for (int i = 0; i < count; i++) {
        balls.push_back(Ball(stx, sty));
    }
}

void BallMaster::reset(float angle) {
    for (auto &ball: balls) {
        ball.state = BALL_READY;
        ball.px = stx;
        ball.py = sty;
        ball.vx = -sin(angle)*BALL_SPEED;
        ball.vy = -cos(angle)*BALL_SPEED;
    }
}

void BallMaster::move(std::list<Block> &blocks) {
    bool any = false;
    for (auto &ball: balls) {
        if ((ball.state == BALL_READY) &&
            dist2(ball.px, ball.py, lastBall->px, lastBall->py) > BALL_SPACING) {
            ball.state = BALL_MOVE;
            lastBall = &ball;
        }
        if (ball.state == BALL_MOVE) {
            ball.move(blocks);
            any = true;
        }
    }
    if (!any) {
        // no ball is moving rn, start the first
        lastBall->state = BALL_MOVE;
        lastBall->move(blocks);
    }
}

void BallMaster::render(SDL_Renderer* renderer) {
    for (auto &ball: balls) {
        ball.render(renderer);
    }
}

bool BallMaster::anyMoving() {
    for (auto &ball: balls) {
        if (ball.state == BALL_MOVE) return true;
    }
    return false;
}
