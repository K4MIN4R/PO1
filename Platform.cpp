//platform.cpp
#include "Platform.h"
#include <allegro5/allegro_primitives.h>

const float Platform::width = 80;
const float Platform::height = 20;

Platform::Platform(float x, float y) : x(x), y(y) {}

void Platform::moveDown(float speed) {
    y += speed;
}

void Platform::draw() const {
    al_draw_filled_rectangle(x - (width / 2), y - (height / 2), x + width + (width / 2), y + (height / 2), al_map_rgb(255, 255, 255));
}
