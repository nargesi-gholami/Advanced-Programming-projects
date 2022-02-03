#include "Player.hpp"

Player::Player(Window* win ,int health_ , int money_ ) 
{
    window = win;
    health = health_;
    money = money_; 
}

void Player::draw()
{
    window->draw_img(COIN , Rectangle(Point(990,7),60,60));
	window->draw_img(HEART , Rectangle(Point(620,7),80,80));
    window->show_text(HEALTH,Point(700,5),WHITE,FONT,50);
    window->show_text(get_health() ,Point(880,7),WHITE,FONT,50);
    window->show_text(MONEY,Point(1050,5),WHITE,FONT,50);
    window->show_text(get_money(),Point(1230,5),WHITE,FONT,50);
}

bool Player::money_dec(int money_dec_)
{
    if(money_dec_ < money)
    {
        money -= money_dec_;
        return true;
    }
    return false;
}

bool Player::dec_health(int health_dec)
{
    if(health - health_dec > 0)
    {
        health -= health_dec;
        return true;
    }
    return false;
}

void Player::inc_money_player(int inc_money)
{
    money += inc_money;
}