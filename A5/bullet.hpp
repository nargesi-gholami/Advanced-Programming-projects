#ifndef BULLET_HPP
#define BULLET_HPP

#include "enemy.hpp"

#define X_PROGRESS 8
#define Y_PROGRESS 8

#define END_RADIOS 8

#define COLOR1 7
#define COLOR2 92
#define COLOR3 83
#define RADIOUS 4

#define MUSIC_POLICE "police.mp3"

class Bullet
{
    public:
    Bullet(int x_,int y_,Enemy* enemy);
    void update();
    bool is_shelik();
    void draw(Window* window);
    void play_music(Window* window);

    private:
    Enemy* enemy_target;
    bool shelik;
    int speed;
    int time;
    int x;
    int y;
};

#endif