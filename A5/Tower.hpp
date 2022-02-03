#ifndef TOWER_HPP
#define TOWER_HPP 

#include "rsdl.hpp"
#include "enemy.hpp"
#include "bullet.hpp"

#include <vector>
#include <string>

#define ONE 1
#define TWO 2
#define THREE 3

#define FIRST 1
#define SECOND 2
#define THIRD 3

#define CONST 0
#define UPDATE 1
#define HOME_RADIOUS 50

#define GUN_DAMAGE 35
#define GUN_TIME 10
#define GUN_COSNTRUCT 55
#define GUN_UPGRADE 40
#define GUN_RADIOS 150
#define GUN_DAMAGE_ADD 35

#define Missile_DAMAGE 75
#define Missile_TIME 30
#define Missile_COSNTRUCT 70
#define Missile_UPGRADE 60
#define Missile_RADIOS 50
#define Missile_DAMAGE_ADD 75

#define Tesla_DAMAGE 700
#define Tesla_TIME 15
#define Tesla_COSNTRUCT 120
#define Tesla_UPGRADE 100
#define Tesla_RADIOS 150
#define Tesla_DAMAGE_ADD 1000

#define GATEELING_ONE "ax/gattling1.png"
#define GATEELING_TWO "ax/gattling2.png"
#define GATEELING_THREE "ax/gattling3.png"
#define GATEELING_ONE1 "ax/gattling13.png"
#define GATEELING_TWO2 "ax/gattling12.png"
#define GATEELING_THREE3 "ax/gattling11.png"

#define MISSLE_ONE "ax/missile1.png"
#define MISSLE_TWO "ax/missile2.png"
#define MISSLE_THREE "ax/missile3.png"
#define MISSLE_ONE1 "ax/missile11.png"
#define MISSLE_TOW2 "ax/missile12.png"
#define MISSLE_THREE3 "ax/missile13.png"

#define GATEELING_ONE "ax/gattling1.png"
#define GATEELING_TWO "ax/gattling2.png"
#define GATEELING_THREE "ax/gattling3.png"


#define TESLA_ONE "ax/tesla1.png"
#define TESLA_TWO "ax/tesla2.png"
#define TESLA_THREE "ax/tesla3.png"

class Tower 
{
	public:
        Tower(Window* win , int x_ , int y_,std::vector <std::vector <Enemy*>> enemy_);
        virtual std::string get_address() = 0;
        virtual void update(int wave_number,int sum_wave);
        virtual void shelik_tir();
        virtual void shelik(int counter_time);

        void draw();
        void update_level();

        int get_time();
        int get_x(){ return x;}
        int get_y(){ return y;}
        int get_money(int mode = CONST);
        int get_damage_amount();

        bool has_target();
        bool check_radious(int i, int j);
        bool is_update_possible(Point tower);

	protected:
        Window* window;
        std::vector<Bullet*> bullet;
        std::vector <std::vector <Enemy*>> enemy;
        Enemy* target;

        int x;
        int y;
        int level;
		int radious;
        int damage_add;
		int time_period;
		int upgrade_cost;
		int damage_amount;
		int construction_cost;

        bool has_target_;
};

class Gun : public Tower
{
    public:
        Gun(Window* win ,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_);
        std::string get_address();   
};

class Missile : public Tower
{
    public:
        Missile(Window* win ,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_);
        void update(int wave_number,int sum_wave);
        void shelik_tir();
        void shelik(int counter_time);
        std::string get_address();
    private:
        std::vector <Enemy*> target; 
};

class Tesla  : public Tower
{
    public:
        Tesla(Window* win ,int x_, int y_,std::vector <std::vector <Enemy*>> enemy_);
        std::string get_address();  
};


#endif
