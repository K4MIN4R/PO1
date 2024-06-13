#include "Player.h"
#include "Platform.h"
#include <allegro5/allegro_primitives.h>

Player::Player(float x, float y) : x(x), y(y), dx(0), dy(0), jumping(false), canJump(true), hasJumped(false) {}

void Player::moveLeft() {
    dx = -5;
}

void Player::moveRight() {
    dx = 5;
}

void Player::stop() {
    dx = 0;
}

void Player::jump() {
    if (canJump) {
        dy = bounceVelocity; // Adjust the jump height as needed
        jumping = true;
        canJump = false; // Set canJump to false after jumping
        hasJumped = true; // Set hasJumped to true after the first jump
    }
}

void Player::update(int screenWidth, int screenHeight) {
    x += dx;
    y += dy;
    dy += 0.5; // Apply gravity

    // Prevent the player from moving out of screen horizontally
    if (x < 0) x = 0;
    if (x > screenWidth) x = screenWidth;
}

void Player::draw() {
    al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(255, 255, 255));
}

bool Player::collidesWith(const Platform& platform) const {
    return x + 10 > platform.getX() &&
           x - 10 < platform.getX() + platform.getWidth() &&
           y + 10 > platform.getY() &&
           y - 10 < platform.getY() + platform.getHeight();
}

void Player::landOnPlatform(const Platform& platform, float platformSpeed) {
    y = platform.getY() - 10;
    dy = platformSpeed; // Player moves down with the platform
    jumping = false;
    canJump = true; // Reset canJump to true after landing on a platform
}

void Player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Player::resetVelocity() {
    dx = 0;
    dy = 0;
    jumping = false;
    canJump = true;
    hasJumped = false; // Reset hasJumped flag
}

bool Player::isOnPlatform(const std::vector<Platform>& platforms) const {
    for (const Platform& platform : platforms) {
        if (collidesWith(platform)) {
            return true;
        }
    }
    return false;
}
