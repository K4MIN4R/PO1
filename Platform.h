#ifndef PLATFORM_H
#define PLATFORM_H

/**
 * @brief Klasa reprezentująca platformę.
 */
class Platform {
public:
    /**
     * @brief Konstruktor klasy Platform.
     * 
     * @param x Pozycja pozioma platformy.
     * @param y Pozycja pionowa platformy.
     */
    Platform(float x, float y);

    /**
     * @brief Przesuwa platformę w dół.
     * 
     * @param speed Prędkość poruszania się platformy.
     */
    void moveDown(float speed);

    /**
     * @brief Rysuje platformę na ekranie.
     */
    void draw() const;

    /**
     * @brief Zwraca pozycję poziomą platformy.
     * 
     * @return float Pozycja pozioma platformy.
     */
    float getX() const { return x; }

    /**
     * @brief Zwraca pozycję pionową platformy.
     * 
     * @return float Pozycja pionowa platformy.
     */
    float getY() const { return y; }

    /**
     * @brief Zwraca szerokość platformy.
     * 
     * @return float Szerokość platformy.
     */
    float getWidth() const { return width; }

    /**
     * @brief Zwraca wysokość platformy.
     * 
     * @return float Wysokość platformy.
     */
    float getHeight() const { return height; }

private:
    float x, y; ///< Pozycje platformy
    static const float width; ///< Szerokość platformy
    static const float height; ///< Wysokość platformy
};

#endif
