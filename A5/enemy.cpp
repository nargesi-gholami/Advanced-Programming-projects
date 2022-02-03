#include "enemy.hpp"
#include <iostream>


Enemy::Enemy(Window* win,std::vector<Point>path)
{
    window = win;
    enemy_path = path;
    x = path[0].x;
    y = path[0].y;
    home_number = 0;
    walk = 0;
    way_where = START;
    alive = ALIVE_;
}

bool Enemy::is_walk()
{
    if(walk == WALKING)
        return true;
    else
        return false;
}

void Enemy::set_end_way()
{
    way_where = END;
}

void Enemy::set_walk()
{
    walk = WALKING;
}

void Enemy::dec_health(int dec_health)
{
    health -= dec_health;
}

void Pertinacious_runner::dec_health(int dec_health)
{
    if(dec_health != DEC_TOWER1)
        if(dec_health != DEC_TOWER2 )
            if(dec_health != DEC_TOWER3)
                health -= dec_health;
}

int Enemy::get_health()
{
    return health;
}

int Enemy::get_kill_price()
{
    if(alive)
    {
        alive = DEAD;
        return kill_price;
    }
    else
        return 0;
    
}

bool Enemy::is_dead()
{
    if((health == 0) || (health < 0) || !is_end())
        return false;
    else
        return true;   
}

int Enemy::get_health_reducer()
{
    set_end_way();
    return player_health_reducer;
}

int Enemy::get_progress_way()
{
    return speed;
}

int Enemy::get_x()
{
    return x;
}

int Enemy::get_y()
{
    return y;
}

bool Enemy::is_end()
{
    return way_where;
}

void Enemy::draw()
{
    window->draw_img(get_address() , Rectangle(x - ENEMY_MOVE , y - ENEMY_MOVE , ENEMY_SIZE , ENEMY_SIZE));
}

void Enemy::update_y(int counter_time)
{
    if( y < enemy_path[home_number + 1].y  &&  enemy_path[home_number].y < enemy_path[home_number + 1].y)
        {
            if(counter_time % 3 == 0)
                mode = DOWN1;
            else if(counter_time % 3 == 1)
                mode = DOWN2;
            else if(counter_time % 3 == 2) 
                mode = DOWN3;
            y += get_progress_way();
        }
        else if( y > enemy_path[home_number + 1].y && enemy_path[home_number].y > enemy_path[home_number + 1].y)
        {
            if(counter_time % 3 == 0)
                mode = UP1;
            else if(counter_time % 3 == 1)
                mode = UP2;
            else if(counter_time % 3 == 2) 
                mode = UP3;
            y -= get_progress_way();
        }
}

void Enemy::update_x(int counter_time)
{
    if(x < enemy_path[home_number + 1].x && enemy_path[home_number].x < enemy_path[home_number + 1].x)
        {
            if(counter_time % 3 == 0)
                mode = RIGHT1;
            else if(counter_time % 3 == 1)
                mode = RIGHT2;
            else if(counter_time % 3 == 2) 
                mode = RIGHT3;
            
            x += get_progress_way();
        }
        else if( enemy_path[home_number].x > enemy_path[home_number + 1].x)
        {
           if(counter_time % 3 == 0)
                mode = RIGHT1;
            else if(counter_time % 3== 1)
                mode = RIGHT2;
            else if(counter_time % 3 == 2) 
                mode = RIGHT3;

            x -= get_progress_way();
        }
}

bool Enemy::check_home(int home_number_)
{
    if((((y == enemy_path[home_number_ + 1].y || y > enemy_path[home_number_ + 1].y) 
    && enemy_path[home_number_].y < enemy_path[home_number_ + 1].y)) || 
    ((y == enemy_path[home_number_ + 1].y || y < enemy_path[home_number_ + 1].y) 
    && enemy_path[home_number_].y > enemy_path[home_number_ + 1].y) ||
    ((x == enemy_path[home_number_ + 1].x || x > enemy_path[home_number_ + 1].x) &&
        enemy_path[home_number_].x < enemy_path[home_number_ + 1].x) ||
    ((x == enemy_path[home_number_ + 1].x || x < enemy_path[home_number_ + 1].x) &&
        enemy_path[home_number_].x > enemy_path[home_number_ + 1].x) )
        return true;
    else
        return false;
}

int Enemy::update_health(int wave_number)
{
   return (ENEMY_INITIAL_HEALTH + COFFICIENT_HEALTH*wave_number)*health;
}

void Enemy::update(int counter_time)
{
    if(enemy_path[home_number].x == enemy_path[home_number + 1].x )
    {
        update_y(counter_time);
    }
    else if(enemy_path[home_number].y == enemy_path[home_number + 1].y)
    {
        update_x(counter_time);
    }
    if(check_home(home_number))
        home_number ++;   
}

std::string Runner::get_address()
{
    if(mode == RIGHT1)
        return RUNNER1;
    else if( mode == RIGHT2)
        return RUNNER2;
    else if(mode == RIGHT3)
        return RUNNER3;
    else if(mode == DOWN1)
        return DOWN_RUNNER1;
    else if(mode == DOWN2)
        return DOWN_RUNNER2;
    else if(mode == DOWN3)
        return DOWN_RUNNER3;
    else if(mode == UP1)
        return UP_RUNNER1;
    else if(mode == UP2)
        return UP_RUNNER2;
    else if(mode == UP3)
        return UP_RUNNER3;
}

Runner::Runner(Window* win,std::vector<Point> path,int wave_number)
    : Enemy(win,path)
{
    health = RUNNER_HEALTH;
    health = update_health(wave_number);
    speed = RUNNER_SPEED;
    kill_price = RUNNER_KILL_PRICE;
    player_health_reducer = RUNNER_REDUCE;
}

std::string Pertinacious_runner::get_address()
{
    if(mode == RIGHT1)
        return SCRAMBLER1;
    else if( mode == RIGHT2)
        return SCRAMBLER2;
    else if(mode == RIGHT3)
        return SCRAMBLER3;
    else if(mode == DOWN1)
        return DOWN_SCRAMBLER1;
    else if(mode == DOWN2)
        return DOWN_SCRAMBLER2;
    else if(mode == DOWN3)
        return DOWN_SCRAMBLER3;
    else if(mode == UP1)
        return UP_SCRAMBLER1;
    else if(mode == UP2)
        return UP_SCRAMBLER2;
    else if(mode == UP3)
        return UP_SCRAMBLER3;
}

Pertinacious_runner::Pertinacious_runner(Window* win,std::vector<Point> path,int wave_number)
    : Enemy(win,path)
{
    health = PRUNNER_HEALTH;
    health = update_health(wave_number);
    speed = PRUNNER_SPEED;
    kill_price = PRUNNER_KILL;
    player_health_reducer = PRUNNER_REDUCE;
}

std::string Elder_runner::get_address()
{
    if(mode == RIGHT1)
        return ROOPER1;
    else if( mode == RIGHT2)
        return ROOPER2;
    else if(mode == RIGHT3)
        return ROOPER3;
    else if(mode == DOWN1)
        return DOWN_ROOPER1;
    else if(mode == DOWN2)
        return DOWN_ROOPER2;
    else if(mode == DOWN3)
        return DOWN_ROOPER2;
    else if(mode == UP1)
        return UP_ROOPER1;
    else if(mode == UP2)
        return UP_ROOPER2;
    else if(mode == UP3)
        return UP_ROOPER3;
}

Elder_runner::Elder_runner(Window* win,std::vector<Point> path,int wave_number)
    : Enemy(win,path)
{
    health = ERUNNER_HEALTH;
    health = update_health(wave_number);
    speed = ERUNNER_SPEED;
    kill_price = ERUNNER_KILL;
    player_health_reducer = ERUNNER_REDUCE;
}

std::string Biker::get_address()
{
    if(mode == RIGHT1)
        return BIKER;
    else if( mode == RIGHT2)
        return BIKER;
    else if(mode == RIGHT3)
        return BIKER;
    else if(mode == DOWN1)
        return DOWN_BIKER1;
    else if(mode == DOWN2)
        return DOWN_BIKER1;
    else if(mode == DOWN3)
        return DOWN_BIKER1;
    else if(mode == UP1)
        return UP_BIKER;
    else if(mode == UP2)
        return UP_BIKER;
    else if(mode == UP3)
        return UP_BIKER;
}

Biker::Biker(Window* win,std::vector<Point> path,int wave_number)
    : Enemy(win,path)
{
    health = BIKER_HEALTH;
    health = update_health(wave_number);
    speed = BIKER_SPEED;
    kill_price = BIKER_KILL;
    player_health_reducer = BIKER_REDUCE;
}