#ifndef ENEMY_HPP
#define ENEMY_HPP 

#include "rsdl.hpp"
#include <vector>

#define ENEMY_MOVE 50
#define ENEMY_SIZE 65

#define ENEMY_INITIAL_HEALTH 0.9
#define COFFICIENT_HEALTH 0.1

#define RUNNER_HEALTH 250
#define RUNNER_SPEED 5
#define RUNNER_KILL_PRICE 6
#define RUNNER_REDUCE 1

#define PRUNNER_HEALTH 400
#define PRUNNER_SPEED 3
#define PRUNNER_KILL 10
#define PRUNNER_REDUCE 4

#define ERUNNER_HEALTH 500
#define ERUNNER_SPEED 2.5
#define ERUNNER_KILL 8
#define ERUNNER_REDUCE 4

#define BIKER_HEALTH 100
#define BIKER_SPEED 9
#define BIKER_KILL 4
#define BIKER_REDUCE 2

#define RUNNER1 "ax/runner1.png"
#define RUNNER2 "ax/runner3.png"
#define RUNNER3 "ax/runner2.png"
#define DOWN_RUNNER1 "ax/down_soldier1.png"
#define DOWN_RUNNER2 "ax/down_soldier2.png"
#define DOWN_RUNNER3 "ax/down_soldier3.png"
#define UP_RUNNER1 "ax/up_soldier1.png"
#define UP_RUNNER2 "ax/up_soldier2.png"
#define UP_RUNNER3 "ax/up_soldier3.png"

#define SCRAMBLER1 "ax/stubborn1.png"
#define SCRAMBLER2 "ax/stubborn2.png"
#define SCRAMBLER3 "ax/stubborn3.png"
#define DOWN_SCRAMBLER1 "ax/downstubborn1.png"
#define DOWN_SCRAMBLER2 "ax/downstubborn2.png"
#define DOWN_SCRAMBLER3 "ax/downstubborn3.png"
#define UP_SCRAMBLER1 "ax/upstubborn1.png"
#define UP_SCRAMBLER2 "ax/upstubborn2.png"
#define UP_SCRAMBLER3 "ax/upstubborn3.png"

#define ROOPER1 "ax/rooper1.png"
#define ROOPER2 "ax/rooper2.png"
#define ROOPER3 "ax/rooper3.png"
#define DOWN_ROOPER1 "ax/downrooper1.png"
#define DOWN_ROOPER2 "ax/downrooper2.png"
#define UP_ROOPER1 "ax/uprooper1.png"
#define UP_ROOPER2 "ax/uprooper2.png"
#define UP_ROOPER3 "ax/uprooper3.png"

#define BIKER "ax/scrambler.png"
#define DOWN_BIKER1 "ax/downbike.png"

#define UP_BIKER "ax/upbike.png"

#define  RIGHT1 1
#define  RIGHT2 2
#define  RIGHT3 3

#define  DOWN1 4
#define  DOWN2 5
#define  DOWN3 6

#define UP1 7
#define UP2 8
#define UP3 9

#define ALIVE_ 1
#define DEAD 0

#define WALKING 1
#define END 0
#define START 1

#define DEC_TOWER1 35
#define DEC_TOWER2 70
#define DEC_TOWER3 105

class Enemy
{
    public:
    Enemy(Window* win,std::vector<Point> path);

    virtual std::string get_address() = 0;
    virtual void dec_health(int dec_health);

    void draw();
    void set_walk();
    void set_end_way();
    void update_x(int counter_time);
    void update_y(int counter_time);
    void update(int counter_time);

    bool is_end();
    bool is_dead();
    bool is_walk();
    bool check_home(int home_number_);

    int get_x();
    int get_y();
    int get_health();
    int get_kill_price();
    int get_progress_way();
    int get_health_reducer(); 
    int update_health(int wave_number);
    
    protected:
        Window* window;
        std::vector<Point> enemy_path;

        int x;
        int y;
        int walk;
        int mode;
        int speed;
        int health;
        int kill_price;
        int home_number;
        int player_health_reducer;

        bool alive;
        bool way_where;
};

class Runner : public Enemy
{
    public:
        Runner(Window* win,std::vector<Point> path,int wave_number);
        std::string get_address();
};

class Pertinacious_runner : public Enemy
{
    public:
    void dec_health(int dec_health);
    Pertinacious_runner(Window* win,std::vector<Point> path,int wave_number);
    std::string get_address();
};

class Elder_runner : public Enemy
{
    public:
        Elder_runner(Window* win,std::vector<Point> path,int wave_number);
        std::string get_address();
};

class Biker : public Enemy
{
    public:
        Biker (Window* win,std::vector<Point> path,int wave_number);
        std::string get_address();
};


#endif
