#ifndef PLAYER_H
#define PLAYER_H
#include "Platform.h"
#include <vector>

class Player {
public:
    Player(float x, float y);

    void moveLeft();
    void moveRight();
    void stop();
    void jump();
    void update(int screenWidth, int screenHeight);
    void draw();
    void setPosition(float x, float y);
    void resetVelocity();

    bool collidesWith(const Platform& platform) const;
    void landOnPlatform(const Platform& platform, float platformSpeed);
    bool isOnPlatform(const std::vector<Platform>& platforms) const;

    float getX() const { return x; }
    float getY() const { return y; }

private:
    float x, y;
    float dx, dy;
    bool jumping;
    bool canJump;
    bool hasJumped;
    const float bounceVelocity = -10.0f;
};

#endif
