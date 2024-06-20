#include "Player.h"
#include "Platform.h"
#include <allegro5/allegro_primitives.h>

/**
 * @brief Konstruktor klasy Player.
 * 
 * @param x Początkowa pozycja pozioma gracza.
 * @param y Początkowa pozycja pionowa gracza.
 */
Player::Player(float x, float y) : x(x), y(y), dx(0), dy(0), jumping(false), canJump(true), hasJumped(false) {}

/**
 * @brief Przesuwa gracza w lewo.
 */
void Player::moveLeft() {
    dx = -5;
}

/**
 * @brief Przesuwa gracza w prawo.
 */
void Player::moveRight() {
    dx = 5;
}

/**
 * @brief Zatrzymuje ruch gracza.
 */
void Player::stop() {
    dx = 0;
}

/**
 * @brief Powoduje, że gracz skacze.
 */
void Player::jump() {
    if (canJump) {
        dy = bounceVelocity; // Dostosuj wysokość skoku według potrzeby
        jumping = true;
        canJump = false; // Ustawia canJump na false po skoku
        hasJumped = true; // Ustawia hasJumped na true po pierwszym skoku
    }
}

/**
 * @brief Aktualizuje stan gracza.
 * 
 * @param screenWidth Szerokość ekranu.
 * @param screenHeight Wysokość ekranu.
 */
void Player::update(int screenWidth, int screenHeight) {
    x += dx;
    y += dy;
    dy += 0.5; // Zastosuj grawitację

    // Zapobiega wychodzeniu gracza poza ekran poziomo
    if (x < 0) x = 0;
    if (x > screenWidth) x = screenWidth;
}

/**
 * @brief Rysuje gracza na ekranie.
 */
void Player::draw() {
    al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(255, 255, 255));
}

/**
 * @brief Sprawdza kolizję gracza z platformą.
 * 
 * @param platform Obiekt platformy do sprawdzenia kolizji.
 * @return true Jeśli gracz koliduje z platformą.
 * @return false Jeśli gracz nie koliduje z platformą.
 */
bool Player::collidesWith(const Platform& platform) const {
    return x + (platform.getWidth() / 2) > platform.getX() &&
           x - (platform.getWidth() / 2) < platform.getX() + platform.getWidth() &&
           y + (platform.getHeight() / 2) > platform.getY() &&
           y - (platform.getHeight() / 2) < platform.getY() + platform.getHeight();
}

/**
 * @brief Powoduje, że gracz ląduje na platformie.
 * 
 * @param platform Obiekt platformy, na której gracz ląduje.
 * @param platformSpeed Prędkość poruszania się platformy.
 */
void Player::landOnPlatform(const Platform& platform, float platformSpeed) {
    y = platform.getY() - 10;
    dy = platformSpeed; // Gracz porusza się w dół z platformą
    jumping = false;
    canJump = true; // Resetuje canJump na true po wylądowaniu na platformie
}

/**
 * @brief Ustawia pozycję gracza.
 * 
 * @param newX Nowa pozycja pozioma gracza.
 * @param newY Nowa pozycja pionowa gracza.
 */
void Player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Resetuje prędkość gracza.
 */
void Player::resetVelocity() {
    dx = 0;
    dy = 0;
    jumping = false;
    canJump = true;
    hasJumped = false; // Resetuje flagę hasJumped
}

/**
 * @brief Sprawdza, czy gracz znajduje się na platformie.
 * 
 * @param platforms Wektor platform do sprawdzenia.
 * @return true Jeśli gracz znajduje się na platformie.
 * @return false Jeśli gracz nie znajduje się na platformie.
 */
bool Player::isOnPlatform(const std::vector<Platform>& platforms) const {
    for (const Platform& platform : platforms) {
        if (collidesWith(platform)) {
            return true;
        }
    }
    return false;
}
