#include "Tower.hpp"

Tower::Tower(Window* win ,int x_ , int y_ ,std::vector <std::vector <Enemy*>> enemy_)
{
    enemy = enemy_;
    window = win;
    has_target_ = false;
    x = x_;
    y = y_;
}

int Tower::get_time()
{
    return time_period;
}

int Tower::get_damage_amount()
{
    return damage_amount;
}

bool Tower::has_target()
{
    return has_target_;
}

bool Tower::check_radious(int i, int j)
{
    if((enemy[i][j]->get_x() > x - radious )&&(enemy[i][j]->get_x() < x + radious) 
            &&  (enemy[i][j]->get_y() > y - radious )&&(enemy[i][j]->get_y() < y + radious)
                && enemy[i][j]->is_end() && enemy[i][j]->is_dead())
                    return true;
    else
        return false;
    
}

void Tower::update(int wave_number,int sum_wave)
{
    for(int j = 0 ; j < sum_wave ; j++)
    {
        if(check_radious(wave_number,j))
        {
            target = enemy[wave_number][j];
            has_target_ = true;
                return;
        }        
        else
            has_target_ = false ;
    }    
}

void Missile::update(int wave_number,int sum_wave)
{
    for(int j = 0 ; j < sum_wave ; j++)
    {
        if(check_radious(wave_number,j))
        {
            target.push_back(enemy[wave_number][j]);
            has_target_ = true;
                return;
        }        
        else
            has_target_ = false ;
    }    
}

void Tower::draw()
{
    window->draw_img(get_address(),Rectangle(x-50,y-50,100,100));
    if(has_target())
        for(int i = 0 ; i < bullet.size() ; i++)
            bullet[i]->draw(window);
    else
        window->stop_music();
}

void Tower::shelik_tir()
{
    for(int i = 0; i < bullet.size() ; i++)
    {
        bullet[i]->update();
        if(bullet[i]->is_shelik())
        {
            target->dec_health(damage_amount);   
            bullet.erase(bullet.begin() + i);
        }
    }
}

void Missile::shelik_tir()
{
    for(int i = 0; i < bullet.size() ; i++)
    {
        bullet[i]->update();
        if(bullet[i]->is_shelik())
        {
            for(int i = 0 ; i < target.size() ; i++)
                target[i]->dec_health(damage_amount);   
            bullet.erase(bullet.begin() + i);
        }
    }
}

void Missile::shelik(int counter_time)
{
    if(has_target())
        if(counter_time % get_time() == 0)
        {
            for(int i = 0 ; i < target.size() ; i++)
            {
                Bullet* bullet_temp = new Bullet(x , y ,target[i]);
                bullet.push_back(bullet_temp);
            }
        }
    shelik_tir();
}

void Tower::shelik(int counter_time)
{
    if(has_target())
        if(counter_time % get_time() == 0)
            {
                Bullet* bullet_temp = new Bullet(x , y ,target);
                bullet.push_back(bullet_temp);
            }
    shelik_tir();
}

bool Tower::is_update_possible(Point tower)
{
    if(tower.x < x + HOME_RADIOUS && tower.x > x - HOME_RADIOUS &&
     tower.y > y - HOME_RADIOUS && tower.y < y + HOME_RADIOUS )
        if(level != THREE)
            return true;
    return false;
}

void Tower::update_level()
{
    level++;
}

int Tower::get_money(int mode)
{
    if(mode == CONST)
        return construction_cost;
    else if(mode == UPDATE)
    {
        damage_amount += damage_add;
        return upgrade_cost;
    }
}

Gun::Gun(Window* win,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_)
    : Tower(win,x_,y_,enemy_)
{
    damage_amount = GUN_DAMAGE;
    time_period = GUN_TIME;
    construction_cost = GUN_COSNTRUCT;
    upgrade_cost = GUN_UPGRADE;
    radious = GUN_RADIOS;
    damage_add = GUN_DAMAGE_ADD;
    level = ONE;
}

std::string Gun::get_address()
{
    if(level == ONE)
        return GATEELING_ONE;

    else if(level == TWO)
        return GATEELING_TWO;

    else if(level == THREE)
        return GATEELING_THREE;
}

Missile::Missile(Window* win,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_)
    : Tower(win,x_,y_,enemy_)
{
    damage_amount = Missile_DAMAGE;
    time_period = Missile_TIME;
    construction_cost = Missile_COSNTRUCT;
    upgrade_cost = Missile_UPGRADE;
    radious = Missile_RADIOS;
    damage_add = Missile_DAMAGE_ADD;
    level = ONE;
}

std::string Missile::get_address()
{
    if(level == ONE)
        return MISSLE_ONE;
    
    else if(level == TWO)
        return MISSLE_TWO;
       
    else if(level == THREE)
        return MISSLE_THREE;
}

std::string Tesla::get_address()
{
    if(level == ONE)
        return TESLA_ONE;
    else if(level == TWO)
        return TESLA_TWO;
    else if(level == THREE)
        return TESLA_THREE;
}

Tesla::Tesla(Window* win,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_)
    : Tower(win,x_,y_,enemy_)
{
    damage_amount = Tesla_DAMAGE;
    time_period = Tesla_TIME;
    construction_cost = Tesla_COSNTRUCT;
    upgrade_cost = Tesla_UPGRADE;
    radious = Tesla_RADIOS;
    damage_add = Tesla_DAMAGE_ADD;
    level = ONE;
}