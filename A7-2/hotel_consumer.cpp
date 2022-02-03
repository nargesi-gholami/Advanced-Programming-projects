#include "hotel_consumer.hpp"

Consumer::Consumer(std::string email_address_,std::string user_name_,
                    std::string password_,bool enterred_)
{
    email_address = email_address_;
    user_name = user_name_;
    password = password_;
    wallet.push_back(0);
    enterred = enterred_;
	default_price_filter = true;
	default_filter = false;
	active_manual_weight = false;
	manual_calcualted = false;
}

Consumer::~Consumer()
{

}

void Consumer::initilize_estimate_rate()
{
	for (int i = 0; i < 5; i++)
		w.push_back(rand() % 4 + 1);
}

long double Consumer::f(Hotel_rate* rate)
{
	return (w[LOCATIN_NUM]*rate->location_rate + w[CLEANLESS_NUM]*rate->cleanliness_rate
		+ w[STAFF_NUM]*rate->staff_rate + w[FACILITIES_NUM]*rate->facilities
		+ w[VALUE_NUM]*rate->value_for_money_rate)
		/ (w[LOCATIN_NUM] + w[CLEANLESS_NUM] + w[STAFF_NUM] + w[FACILITIES_NUM] + w[VALUE_NUM]);
}

long double Consumer::E(Hotel_rate* rate)
{
	return pow((f(rate) - rate->overall_rate), 2);
}

void Consumer::increase_manual_weights(int number ,  bool sum)
{
	if (sum) 
		w[number] += EPSILON;
	else   
		w[number] -= EPSILON;
}

long double Consumer::d_E(Hotel_rate* rate, int number)
{
	long double last_E = E(rate);
	increase_manual_weights(number, SUM);
	long double current_E = (E(rate) - last_E) / EPSILON;
	increase_manual_weights(number, SUB);
	return current_E;
}

void Consumer::put_weights()
{
	location_manual = w[LOCATIN_NUM];
	cleanless_manual = w[CLEANLESS_NUM];
	staff_manual = w[STAFF_NUM];
	facilities_manual = w[FACILITIES_NUM];
	value_manual = w[VALUE_NUM];
	manual_calcualted = true;
}

std::vector<long double> Consumer::estimate_rating()
{
	initilize_estimate_rate();
	for (int j = 0 ; j < hotel_rates.size() ; j++)
		while (E(hotel_rates[j]) > EPSILON)
			for (int i = FIRST_RATING ; i < LAST_RATING ; i++)
				w[i] -= ALFA * d_E(hotel_rates[j], i);
	put_weights();
	return w;
}

std::vector<long double> Consumer::estimate_weights()
{
	if(manual_calcualted)
		return { location_manual , cleanless_manual , staff_manual , facilities_manual , value_manual };
	else if (hotel_rates.size() >= MIN_PEOPLE_RATE)
		return estimate_rating();
	else
		throw INSUFFICENT_RATING;
}

void Consumer::put_rate(std::string Hotel_id, std::vector <float> rates)
{
	for(int i = 0 ; i < hotel_rates.size() ; i++)
		if (hotel_rates[i]->hotel_id_rate == Hotel_id)
		{
			hotel_rates[i]->location_rate = rates[0];
			hotel_rates[i]->cleanliness_rate = rates[1];
			hotel_rates[i]->staff_rate = rates[2];
			hotel_rates[i]->facilities = rates[3];
			hotel_rates[i]->value_for_money_rate = rates[4];
			return;
		}
	hotel_rates.push_back(new Hotel_rate {Hotel_id,rates[0],rates[1],rates[2],rates[3],rates[4],rates[5]});
}

void Consumer::print_manual_weights()
{
	std::cout << ACTIVE_TRUE
		<< LOCATION << SPACE; printf("%.2f ", floor(location_manual*TRUNCATE_NUM) / TRUNCATE_NUM);
	std::cout << CLEANLINESS << SPACE; printf("%.2f ", floor(cleanless_manual * TRUNCATE_NUM) / TRUNCATE_NUM);
	std::cout << STAFF << SPACE; printf("%.2f ", floor(staff_manual * TRUNCATE_NUM) / TRUNCATE_NUM);
	std::cout << FACILITIES << SPACE; printf("%.2f ", floor(facilities_manual * TRUNCATE_NUM) / TRUNCATE_NUM);
	std::cout << VALUE_FOR_MONEY << SPACE; printf("%.2f \n", floor(value_manual * TRUNCATE_NUM) / TRUNCATE_NUM);
}

double find_rate(std::string order , int position)
{
	double rate = std::stod(order.substr(position , order.find(SPACE, position) - position ));
	if (rate < 1 || rate > 5)
		throw BAD_REQUEST;
	return rate;
}

std::vector <int> get_position(std::string order, std::vector <std::string> words)
{
	std::vector <int> position;
	for (int i = 0; i < words.size(); i++)
	{
		if (order.find(words[i]) == std::string::npos)
			throw BAD_REQUEST;
		position.push_back(order.find(words[i]) + words[i].size() + 1);
	}
	return position;
}

void Consumer::post_manual_weights(std::string order)
{
	std::vector<int> positions = get_position(order, { LOCATION , CLEANLINESS , STAFF , FACILITIES , VALUE_FOR_MONEY });
	location_manual = find_rate(order , positions[0]);
	cleanless_manual = find_rate(order, positions[1]);
	staff_manual = find_rate(order, positions[2]);
	facilities_manual = find_rate(order, positions[3]);
	value_manual = find_rate(order, positions[4]);
}

int Consumer::get_number_of_room()
{
	int number_of_room = 0;
	for(int i = 0 ; i < reserved_room.size() ; i++)
		number_of_room += reserved_room[i][0]->get_quantity();
	return number_of_room;
}

float Consumer::cal_reserved_room_price_average()
{
	float average = 0 ;
	for(int i = 0 ; i < reserved_room.size() ; i++)
		average += reserved_room[i][0]->get_price()*reserved_room[i][0]->get_quantity();
		
	return average / get_number_of_room();
}

float Consumer::cal_standard_deviation_room_price()
{
	float variance = 0;
	float mean = cal_reserved_room_price_average();
	for (int i = 0 ; i < reserved_room.size() ; i++)
		for(int j = 0 ; j < reserved_room[i].size() ; j++)
			variance += pow((reserved_room[i][j]->get_price() - mean) , 2);
	
	variance /= (get_number_of_room() - 1);
	return sqrt(variance);
}

bool Consumer::is_login()
{
    return enterred;
}

bool Consumer::set_login()
{
    if(!enterred)
    {
        enterred = true;
        return true;
    }
    else
        return false ;
}

bool Consumer::set_logout()
{
    if(enterred)
    {
        enterred = false;
        return true;
    }
    else
        return false ;
}

void Consumer::print_wallet(int count)
{
	for (int i = 0; i < count && i < wallet.size(); i++)
		printf("%.0f\n", wallet[wallet.size() - i - 1]);
}

void Consumer::increase_wallet(float count)
{
	if (count > 0)
		wallet.push_back(wallet[wallet.size() - 1] + float(count));
    else
        throw BAD_REQUEST;
}

void Consumer::see_wallet(std::string order)
{
    if(order.find(COUNT) != std::string::npos && order.find(GET) != std::string::npos)
    {
        int index1 = order.find(COUNT) + 5;
        int index2 = order.find(SPACE , index1 + 6); 
        print_wallet(stoi(order.substr(index1,index2)));
    }
   
    else if(order.find(AMOUNT) != std::string::npos && order.find(POST) != std::string::npos)
    {
        int index1 = order.find(AMOUNT) + 6 ;
        int index2 = order.find(SPACE , index1 + 7); 
        increase_wallet(stof(order.substr(index1,index2)));
		std::cout << OK << std::endl;
    }
    else
        throw BAD_REQUEST;
}

void Consumer::put_reserve(std::vector <Room*> reserved)
{
    reserved_room.push_back(reserved);
}

bool is_assign(int id , std::vector <int> delete_number )
{
    for(int i = 0 ; i < delete_number.size() ; i++)
        if(id == delete_number[i])
            return true;
    return false;
}

void Consumer::print_reserve()
{
    int id = reserved_room.size();
    for(int i = 0 ; i < reserved_room.size(); i++)
    {
        if(is_assign(reserved_room.size() - i , deleted_id )){ id--; continue;}
        std::cout << "id: " << id << " hotel: " << reserved_room[reserved_room.size() - i -1][0]->get_hotel_id() 
        << " room: " <<  reserved_room[reserved_room.size() - i -1][0]->get_type() 
        << " quantity: " << reserved_room[reserved_room.size() - i -1][0]->get_quantity() << " cost: " <<
        reserved_room[reserved_room.size() - i -1][0]->get_quantity()*reserved_room[reserved_room.size() - i -1][0]->get_price() <<
        " check_in " << reserved_room[reserved_room.size() - i -1][0]->get_check_in() << " check_out " << 
        reserved_room[reserved_room.size() - i -1][0]->get_check_out() << std::endl;
        id --;
    }
	if(reserved_room.size() == 0 )
		std::cout << EMPTY << std::endl;
}

void Consumer::dec_wallet(int money)
{ 
    wallet.push_back(wallet[wallet.size() - 1] - money);
}

Room* Consumer::delete_room(int id)
{
    if(id <= reserved_room.size())
    {
        int sum = 0; 
		for (int j = 0 ; j < reserved_room[id - 1].size() ; j++)
			sum += reserved_room[id - 1][j]->get_price();
        wallet.push_back(wallet[wallet.size() - 1] + sum / 2);
        Room* room = reserved_room[id - 1][0]; 
        deleted_id.push_back(id);
        return room;
    }
    else 
        throw NOT_FOUND;
}