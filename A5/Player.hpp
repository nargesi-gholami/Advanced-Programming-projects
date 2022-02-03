#ifndef PLAYER_HPP
#define PLAYER_HPP 

#include "rsdl.hpp"
#include <string>

#define MAX_HEALTH 20
#define MAX_MONEY 200

#define FONT "OpenSans.ttf"
#define COIN "ax/coin.png" 
#define HEART "ax/heart.png" 
#define HEALTH "Health:" 
#define MONEY "Money:" 

class Player 
{
    public:
    Player(Window *win ,int health_ , int money_ );

    void draw();
    void inc_money_player(int inc_money);

    bool money_dec(int money);
    bool dec_health(int health_dec);

    std::string get_health() { return std::to_string(health);}
    std::string get_money() { return std::to_string(money); }

    private:
        Window* window;
        int health;
        int money;   
};

#endif
