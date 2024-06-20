#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include "Player.h"
#include "Platform.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
const int PLATFORM_SPACING_MIN = 100;
const int PLATFORM_SPACING_MAX = 140;
const int PLATFORM_HORIZONTAL_RANGE = 150;
const int PLATFORM_GENERATION_OFFSET = 150;
const float PLATFORM_MOVE_SPEED = 2.0f;

bool isGameOver = false;
bool firstJump = false;

/**
 * @brief Generuje pozycję poziomą nowej platformy na podstawie poprzedniej pozycji poziomej.
 * 
 * @param previousX Pozycja pozioma poprzedniej platformy.
 * @return float Nowa pozycja pozioma platformy.
 */
float generatePlatformHorizontalPosition(float previousX) {
    return previousX + (rand() % (PLATFORM_HORIZONTAL_RANGE * 2)) - PLATFORM_HORIZONTAL_RANGE;
}

/**
 * @brief Generuje pozycję pionową nowej platformy na podstawie poprzedniej pozycji pionowej.
 * 
 * @param previousY Pozycja pionowa poprzedniej platformy.
 * @return float Nowa pozycja pionowa platformy.
 */
float generatePlatformVerticalPosition(float previousY) {
    return previousY - ((rand() % (PLATFORM_SPACING_MAX - PLATFORM_SPACING_MIN)) + PLATFORM_SPACING_MIN);
}

/**
 * @brief Rysuje ekran końca gry.
 * 
 * @param font Czcionka używana do wyświetlania tekstu.
 */
void drawGameOverScreen(ALLEGRO_FONT* font) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, ALLEGRO_ALIGN_CENTER, "Game Over");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10, ALLEGRO_ALIGN_CENTER, "Press R to Restart");
    al_flip_display();
}

/**
 * @brief Generuje początkowy zestaw platform.
 * 
 * @return std::vector<Platform> Wektor zawierający wygenerowane platformy.
 */
std::vector<Platform> generatePlatforms(){
    std::vector<Platform> tmpPlatforms;
    float initialY = SCREEN_HEIGHT - 50;
    float previousX = SCREEN_WIDTH / 2;
    tmpPlatforms.push_back(Platform(previousX, SCREEN_HEIGHT - 10));
    for (int i = 1; i < 10; ++i) {
        previousX = tmpPlatforms[i - 1].getX();
        float x = generatePlatformHorizontalPosition(previousX);
        float y = generatePlatformVerticalPosition(initialY);
        tmpPlatforms.push_back(Platform(x, y));
        initialY = y;
    }
    return tmpPlatforms;
}

/**
 * @brief Resetuje stan gry do początkowego.
 * 
 * @param player Obiekt gracza do zresetowania.
 * @param platforms Wektor platform do zresetowania.
 */
void resetGame(Player& player, std::vector<Platform>& platforms) {
    firstJump = false;
    player.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
    player.resetVelocity();

    platforms.clear();

    platforms = generatePlatforms();

    isGameOver = false;
}

/**
 * @brief Główna funkcja programu.
 * 
 * Inicjalizuje Allegro, tworzy okno gry, uruchamia pętlę główną gry.
 * 
 * @return int Status zakończenia programu.
 */
int main() {
    if (!al_init()) {
        return -1;
    }

    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        return -1;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display)); // Register display event source

    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        al_destroy_display(display);
        return -1;
    }

    bool running = true;
    bool redraw = true;
    srand(time(nullptr));
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
    std::vector<Platform> platforms = generatePlatforms();     
    std::cout << platforms.size() << std::endl;
    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        } else if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (!isGameOver) {
                player.update(SCREEN_WIDTH, SCREEN_HEIGHT);

                if (player.getY() > SCREEN_HEIGHT) {
                    isGameOver = true;
                }

                auto it = platforms.begin();
                while (it != platforms.end()) {
                    if (it->getY() > SCREEN_HEIGHT) {
                        it = platforms.erase(it);
                    } else {
                        ++it;
                    }
                }

                float minY = player.getY() - SCREEN_HEIGHT + PLATFORM_GENERATION_OFFSET;
               if (platforms.empty() || platforms.back().getY() > minY) {
                    float initialY = platforms.empty() ? SCREEN_HEIGHT - 50 : platforms.back().getY();
                    float previousX = 0;
                    for (int i = 0; i < 3; ++i) {
                        previousX = platforms[platforms.size() - 1].getX();
                        float x = generatePlatformHorizontalPosition(previousX);
                        float y = generatePlatformVerticalPosition(initialY);
                        platforms.push_back(Platform(x, y));
                        initialY = y;
                    }

                }
               if(firstJump){
                    for (Platform& platform : platforms) {
                        platform.moveDown(PLATFORM_MOVE_SPEED);
                    }
                }               
                if (player.isOnPlatform(platforms)) {
                    for (Platform& platform : platforms) {
                        if (player.collidesWith(platform)) {
                            player.landOnPlatform(platform, PLATFORM_MOVE_SPEED);
                            break;
                        }
                    }
                } else {
                    player.update(SCREEN_WIDTH, SCREEN_HEIGHT); // Apply gravity if the player is not on any platform
                }

                redraw = true;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            SCREEN_WIDTH = ev.display.width;
            SCREEN_HEIGHT = ev.display.height;
            al_acknowledge_resize(display);
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (!isGameOver) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        player.moveLeft();
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        player.moveRight();
                        break;
                    case ALLEGRO_KEY_SPACE:
                        if(!firstJump)
                            firstJump = true;
                        player.jump();
                        break;
                }
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_R) {
                resetGame(player, platforms);
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT || ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                player.stop();
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            player.draw();
            for (const Platform& platform : platforms) {
                platform.draw();
            }

            if (isGameOver) {
                drawGameOverScreen(font);
            }

            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}
