#include "bullet.hpp"


Bullet::Bullet(int x_,int y_,Enemy* enemy)
{
    x = x_;
    y = y_;
    shelik = false;
    enemy_target = enemy; 
}

bool Bullet::is_shelik()
{
    if((x < enemy_target->get_x() + END_RADIOS && x > enemy_target->get_x() - END_RADIOS)
     && (y < enemy_target->get_y() + END_RADIOS && y > enemy_target->get_y() - END_RADIOS))
    {   
        shelik = true;
        return true;
    }
        return false;
}

void Bullet::draw(Window* window)
{
    window->fill_circle(Point(x,y), RADIOUS ,RGB(COLOR1, COLOR2, COLOR3));
    play_music(window);
}

void Bullet::play_music(Window* window)
{
    window->play_music(MUSIC_POLICE);
}

void Bullet::update()
{
    if(x < enemy_target->get_x())
        x += X_PROGRESS;

    if(y > enemy_target->get_y())
        y -= Y_PROGRESS;

    if(x > enemy_target->get_x() )
        x -= X_PROGRESS;

    if(y < enemy_target->get_y())
        y += Y_PROGRESS;
}