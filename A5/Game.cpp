#include "Game.hpp"

Game::Game()
{
    Window *window = new Window(WALL_WIDTH, WALL_LENGTH, GAME_NAME);
    set_window(window);
    player = new Player(window,MAX_HEALTH,MAX_MONEY);
    is_end_game = START;
    delay_time = false;
    counter_time = 0;
    counter_wave_time = 0 ;
    wave_number = 0;
}

void Game::start()
{
    find_enemy();
    window->play_sound_effect(MUSIC_NAME);
    while(is_end_game)
	{   
		window->draw_img(BACKGROUND);
        if(delay_time)
            enter_enemy();
		identify_event(window);
        update();
        draw();
        window->update_screen();
        check_delay();
        check_win(window);
        delay(100);
	}
}

bool is_repeat(std::vector<int> random ,int temp)
{
    for(int i = 0 ; i < random.size() ; i++)
    {
        if(temp == random[i])
            return false;
    }
    return true;
}

std::vector<int> const_random(int start, int size)
{
    std::vector<int> random;
    int temp,count = start;
    srand(size);
    while(count < size)
    {
        temp = (rand() % (size - start)) + start ;
        if(is_repeat(random,temp))
            random.push_back(temp);
        else
            continue;
        
        count ++;
    }
    return random;
}

void Game::find_enemy()
{
    path  = get_path(path);
    enemy = get_enemy_kind1();
    random = const_random(0 , enemy[wave_number].size());

    enemy_num = 0;   
}

void Game::check_delay()
{
    if(!delay_time)
        counter_wave_time++;

    if(counter_wave_time % WAVE_DELAY == 0)
        delay_time = true;

    counter_time++;
}

void Game::check_wave()
{
    if(wave_number == wave_num.size())
        wave_number = wave_num.size() - 1;
}

int Game::sum_wave()
{
    int sum = 0;
    for(int i = 0 ; i <= wave_number ; i++)
        sum += wave_num[i];
    return sum;
}

bool Game::all_seen()
{
    for(int i = 0 ; i < sum_wave(); i++)
        if(!enemy[wave_number][i]->is_walk())
            return false;
    return true;
}

void Game::enter_enemy()
{
    if(counter_time % FIVE == 0)
    {
        if(!all_seen())
        {
            if(!enemy[wave_number][random[enemy_num]]->is_walk())
            {
                enemy[wave_number][random[enemy_num]]->set_walk();
                enemy_num++;
                return;
            }
        }
        else
        {
            if(wave_number + 1 < wave_num.size())
            {
                wave_number++;
                std::vector<int> temp = const_random(enemy[wave_number - 1].size(),enemy[wave_number].size());
                random.insert(random.end(),temp.begin(),temp.end());
            }
            delay_time = 0;
        }
    }
}

void Game::identify_event(Window *window)
{
    while (window->has_pending_event())
    {
        Event e = window->poll_for_event();
        switch (e.get_type()) 
        {
            case Event::LCLICK:
                Tower_position = e.get_mouse_position();
                break;
            case Event::KEY_PRESS:
            {
                char tower_kind = e.get_pressed_key();
                save_tower(window , Tower_position , tower_kind);
            }
                break;
            case Event::QUIT:
                is_end_game = END;
                break;
        }
    }
}

bool Game::check_tower(Point Tower_position)
{
    for(int i = 0 ; i < path.size(); i++)
        if(Tower_position.x > path[i].x - PATH_RADIOUS && Tower_position.x < path[i].x + PATH_RADIOUS)
            if(Tower_position.y > path[i].y - PATH_RADIOUS && Tower_position.y < path[i].y + PATH_RADIOUS)
                return false;
    return true;
}

void Game::save_tower(Window *window, Point Tower_position , char tower_kind)
{
    if(check_tower(Tower_position))
    {
        switch(tower_kind)
        {
            case GUN_KEY:
            { 
                Gun* gun = new Gun(window,Tower_position.x,Tower_position.y,enemy);
                if(player->money_dec(gun->get_money()))
                    tower.push_back(gun);
            }
                break;
            case MISSLE_KEY:
            {
                Missile* missile = new Missile(window,Tower_position.x,Tower_position.y,enemy);
                if(player->money_dec(missile->get_money()))
                    tower.push_back(missile);
            }
               break;
             case TESLA_KEY:
             {
                Tesla* tesla = new Tesla(window,Tower_position.x,Tower_position.y,enemy);
                if(player->money_dec(tesla->get_money()))
                    tower.push_back(tesla);
             }
                break;
            case UPDATE_KEY:
                tower_update = Tower_position;
                   break;
        }     
    }   
}

std::vector <Enemy*> Game::get_enemy_kind2(int runner_num ,int prunner_num ,int erunner_num ,int biker)
{
	for(int i = 0 ; i < runner_num ; i++) 
    {
        Runner* runner = new Runner(window,path,wave_num.size()+1);
        enemy_temp.push_back(runner);
    }
	for(int i = 0 ; i < prunner_num ; i++) 
    {
        Pertinacious_runner* pertinacious_runner = new Pertinacious_runner(window,path,wave_num.size()+1);
        enemy_temp.push_back(pertinacious_runner);
    }
	for(int i = 0 ; i < erunner_num ; i++)
    {
        Elder_runner* elder_runner = new Elder_runner(window,path,wave_num.size()+1);
        enemy_temp.push_back(elder_runner);
    }
	for(int i = 0 ; i < biker ; i++) 
    {
        Biker* biker = new Biker(window,path,wave_num.size()+1);
        enemy_temp.push_back(biker);
    }
    return enemy_temp;
}

std::vector<std::vector<Enemy*>> Game::get_enemy_kind1()
{
	int runner_num,prunner_num,erunner_num,biker;
	while(std::cin >> runner_num)
    {
        std::cin >> prunner_num;
        std::cin >> erunner_num;
        std::cin >> biker;
        enemy.push_back(get_enemy_kind2(runner_num,prunner_num,erunner_num,biker));
        wave_num.push_back(runner_num + prunner_num + erunner_num + biker);
    }   
	return enemy;
}

std::vector <Point> Game:: get_path(std::vector<Point> path)
{
    std::string input;
    std::getline(std::cin,input,ENTER);
	while(!input.empty())
    {
        Point p;
        p.x = stoi(input.substr(0,input.find(COMMA)))*REC_WIDTH + X_DISTANT + ADDITION_WIDTH;
        input = input.substr(input.find(COMMA) + 1);
        if(input.find(COMMA) == std::string::npos)
        {
            p.y = stoi(input)*REC_WIDTH + Y_DISTANT + ADDITION_WIDTH;
            path.push_back(p);
        	break;
        }
        p.y = stoi(input.substr(0,input.find(COMMA)))*REC_WIDTH + Y_DISTANT + ADDITION_WIDTH;
        input = input.substr(input.find(COMMA) + 1 );
		path.push_back(p);
    }
	return path;
}

void Game::update_walking(int enemy_number)
{
    if(enemy[wave_number][enemy_number]->is_walk() 
        && enemy[wave_number][enemy_number]->is_dead())
            enemy[wave_number][enemy_number]->update(counter_time);
}

void Game::update_player_health(int enemy_number)
{
    if(enemy[wave_number][enemy_number]->check_home(path.size() - 2) && enemy[wave_number][enemy_number]->is_end()) 
    {
        if(!player->dec_health(enemy[wave_number][enemy_number]->get_health_reducer()))
            is_end_game = LOSE;  
        else 
            enemy[wave_number][enemy_number]->set_end_way();
    }
}

void Game::update_dead_enemy(int enemy_number)
{
    if((enemy[wave_number][enemy_number]->get_health()) == 0 || 
        (enemy[wave_number][enemy_number]->get_health()) < 0)
        player->inc_money_player(enemy[wave_number][enemy_number]->get_kill_price()); 
}

void Game::update_enemy()
{
    for(int i = 0 ; i < sum_wave() ; i++)
    {
        update_walking(i);
        update_player_health(i);
        update_dead_enemy(i);     
    }
}

void Game::tower_inc_level(int tower_number)
{
    if(tower[tower_number]->is_update_possible(tower_update))
        if(player->money_dec(tower[tower_number]->get_money(UPDATE)))
        {
            tower[tower_number]->update_level();
            tower_update.x = 0;
            tower_update.y = 0;
        }
}

void Game::update_tower()
{
    check_wave();
    for(int i = 0 ; i < tower.size() ; i++)
    {
        tower_inc_level(i);
        tower[i]->update(wave_number,sum_wave());
        tower[i]->shelik(counter_time);
    }
}

void Game::update()
{
    update_tower();
    update_enemy();
}

void Game::draw_enemy()
{
    for(int i = 0 ; i < sum_wave() ; i++)
        if(enemy[wave_number][i]->is_walk() && enemy[wave_number][i]->is_dead())
            enemy[wave_number][i]->draw();
}

void Game::draw_tower()
{
    for(int i = 0 ; i < tower.size() ; i++)
        tower[i]->draw();
}

void Game::draw()
{
    draw_enemy();
    player->draw();
    draw_tower();
}

bool Game::is_end()
{
    for(int i = 0 ; i < sum_wave() ; i++)
        if(enemy[wave_number][i]->is_dead())
            return false;
    return true;
}

void Game::the_end(std::string text)
{
    window->draw_img(BLACK_BACKGROND);
    window->show_text(text,Point(TYPE_LOCATION,TYPE_LOCATION),WHITE,FONT,SIZE);
    window->update_screen();
    delay(5000);
    is_end_game = END;
}

void Game::check_win(Window *window)
{
    if(is_end_game == LOSE)
        the_end(LOSE_TEXT);

    if(is_end())
       the_end(WIN_TEXT);
}



