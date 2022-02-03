#ifndef GAME_HPP
#define GAME_HPP
#include "rsdl.hpp"
#include "Tower.hpp"
#include "enemy.hpp"
#include "Player.hpp"

#include <iostream>
#include <vector>

#define END 0
#define LOSE 9
#define WIN 10
#define START 1
#define ALIVE 10

#define WALL_WIDTH 1365
#define WALL_LENGTH 1024

#define FIVE 5
#define WAVE_DELAY 30
#define PATH_RADIOUS 30
#define REC_WIDTH 59
#define ADDITION_WIDTH  29.5
#define X_DISTANT 125
#define Y_DISTANT 176
#define TYPE_LOCATION 400
#define SIZE 100

#define LOSE_TEXT "You lose:("
#define WIN_TEXT "You win:)"
#define BACKGROUND "ax/background.png"
#define GAME_NAME "ax/FieldRunners"
#define MUSIC_NAME "03 Crossroads.mp3"
#define BLACK_BACKGROND "ax/black.png"
#define FONT "OpenSans.ttf"
#define GUN_KEY 'g'
#define MISSLE_KEY 'm'
#define TESLA_KEY 't'
#define UPDATE_KEY 'u'
#define ENTER '\n'
#define COMMA ' '

class Game
{
    public:
    Game();
    void start();
    void set_window(Window* win){ window = win;}
    
    private:

    bool delay_time;
    Window* window;
    std::vector<int> random;

    void draw();
    void update();
    void check_delay();
    void handle_event();
    void the_end(std::string text);
    void check_win(Window *window);
    void identify_event(Window *window);

    std::vector <Point> path;
    std::vector <Point> get_path(std::vector<Point> path);

    int enemy_num;
    int sum_wave();
    bool all_seen();
    void find_enemy();
    void enter_enemy();
    void update_enemy();
    std::vector <Enemy*> enemy_temp;
    std::vector <std::vector <Enemy*>> enemy;
    std::vector<Enemy*> get_enemy_kind2(int runner_num,int prunner_num,int erunner_num,int biker);
    std::vector<std::vector<Enemy*>> get_enemy_kind1();

    bool is_end();
    void draw_enemy();
    void update_walking(int enemy_number);
    void update_dead_enemy(int enemy_number);
    void update_player_health(int enemy_number);

    void check_wave();
    
    Player* player;

    char tower_kind;
    void draw_tower();
    void update_tower();
    Point tower_update;
    Point Tower_position;
    std::vector <Tower*> tower;
    void tower_inc_level(int tower_number);
    bool check_tower(Point Tower_position);
    void save_tower(Window *window, Point Tower_position, char tower_kind);

    int is_end_game;
    int counter_time;

    int counter_wave_time;
    int wave_number;

    std::vector<int> wave_num ;
    bool not_repeation(int rand_);
};


#endif