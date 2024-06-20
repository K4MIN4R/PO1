#ifndef PLAYER_H
#define PLAYER_H
#include "Platform.h"
#include <vector>

/**
 * @brief Klasa reprezentująca gracza.
 */
class Player {
public:
    /**
     * @brief Konstruktor klasy Player.
     * 
     * @param x Początkowa pozycja pozioma gracza.
     * @param y Początkowa pozycja pionowa gracza.
     */
    Player(float x, float y);

    /**
     * @brief Przesuwa gracza w lewo.
     */
    void moveLeft();

    /**
     * @brief Przesuwa gracza w prawo.
     */
    void moveRight();

    /**
     * @brief Zatrzymuje ruch gracza.
     */
    void stop();

    /**
     * @brief Powoduje, że gracz skacze.
     */
    void jump();

    /**
     * @brief Aktualizuje stan gracza.
     * 
     * @param screenWidth Szerokość ekranu.
     * @param screenHeight Wysokość ekranu.
     */
    void update(int screenWidth, int screenHeight);

    /**
     * @brief Rysuje gracza na ekranie.
     */
    void draw();

    /**
     * @brief Ustawia pozycję gracza.
     * 
     * @param x Nowa pozycja pozioma gracza.
     * @param y Nowa pozycja pionowa gracza.
     */
    void setPosition(float x, float y);

    /**
     * @brief Resetuje prędkość gracza.
     */
    void resetVelocity();

    /**
     * @brief Sprawdza kolizję gracza z platformą.
     * 
     * @param platform Obiekt platformy do sprawdzenia kolizji.
     * @return true Jeśli gracz koliduje z platformą.
     * @return false Jeśli gracz nie koliduje z platformą.
     */
    bool collidesWith(const Platform& platform) const;

    /**
     * @brief Powoduje, że gracz ląduje na platformie.
     * 
     * @param platform Obiekt platformy, na której gracz ląduje.
     * @param platformSpeed Prędkość poruszania się platformy.
     */
    void landOnPlatform(const Platform& platform, float platformSpeed);

    /**
     * @brief Sprawdza, czy gracz znajduje się na platformie.
     * 
     * @param platforms Wektor platform do sprawdzenia.
     * @return true Jeśli gracz znajduje się na platformie.
     * @return false Jeśli gracz nie znajduje się na platformie.
     */
    bool isOnPlatform(const std::vector<Platform>& platforms) const;

    /**
     * @brief Zwraca pozycję poziomą gracza.
     * 
     * @return float Pozycja pozioma gracza.
     */
    float getX() const { return x; }

    /**
     * @brief Zwraca pozycję pionową gracza.
     * 
     * @return float Pozycja pionowa gracza.
     */
    float getY() const { return y; }

private:
    float x, y;        /**< Pozycja gracza */
    float dx, dy;      /**< Prędkość gracza */
    bool jumping;      /**< Czy gracz jest w trakcie skoku */
    bool canJump;      /**< Czy gracz może skoczyć */
    bool hasJumped;    /**< Czy gracz już skoczył */
    const float bounceVelocity = -10.0f; /**< Prędkość odbicia po skoku */
};

#endif
