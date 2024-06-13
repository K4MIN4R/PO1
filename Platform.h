//platform.h
#ifndef PLATFORM_H
#define PLATFORM_H

class Platform {
public:
    Platform(float x, float y);

    void moveDown(float speed); // Method to move the platform downwards
    void draw() const;

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

private:
    float x, y;
    static const float width, height;
};

#endif
