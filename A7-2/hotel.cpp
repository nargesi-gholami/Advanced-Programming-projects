#include "hotel.hpp"

Hotel::Hotel()
{}

Hotel::~Hotel()
{}

Hotel::Hotel(std::string unique_id_ , std::string property_name_,
            int hotel_star_rating_ , std::string hotel_overview_,
            std::string property_amenities_ , std::string city_,
            float longitude_ , float latitude_,
            std::string image_url_ , int num_of_standard_rooms_,
            int num_of_deluxe_rooms_ , int num_of_luxary_rooms_,
            int num_of_premium_rooms_ , int standard_room_price_,
            int delux_room_price_ , int luxury_room_price_,
            int premium_room_price_)

{
        unique_id = unique_id_;
        name = property_name_;
        star_rating = hotel_star_rating_;
        overview = hotel_overview_;
        amenities = property_amenities_;
        city = city_;
        longitude = longitude_;
        latitude = latitude_;
        image_url = image_url_;
        num_of_standard_rooms = num_of_standard_rooms_;
        num_of_deluxe_rooms = num_of_deluxe_rooms_;
        num_of_luxary_rooms = num_of_luxary_rooms_;
        num_of_premium_rooms = num_of_premium_rooms_;
        total_number_of_room = num_of_deluxe_rooms + num_of_luxary_rooms + num_of_premium_rooms + num_of_standard_rooms;
        standard_room_price = standard_room_price_;
        deluxe_room_price = delux_room_price_;
        luxury_room_price = luxury_room_price_;
        premium_room_price = premium_room_price_;
        average_price = cal_average();
		has_rating = false;
        for(int i = 0 ; i < 30 ; i++)
        {
            reserved_standard_rooms_time[i] = 0;
            reserved_deluxe_rooms_time[i] = 0;
            reserved_luxary_rooms_in_time[i] = 0;
            reserved_premium_rooms_in_time[i] = 0;
        }
}

void Hotel::print1()
{
    std::cout << unique_id << std::endl
    << name << std::endl 
    << "star: " << star_rating << std::endl
    << "overview: " << overview << std::endl
    << "amenities: "<< amenities << std::endl 
    << "city: " << city << std::endl;
    printf("latitude: %.2f\n", latitude);
    printf("longitude: %.2f\n", longitude);
    std::cout << "#rooms: " << num_of_standard_rooms << " " << num_of_deluxe_rooms << 
    " " << num_of_luxary_rooms << " " << num_of_premium_rooms << std::endl
    << "price: " << standard_room_price << " " << deluxe_room_price << " "
    << luxury_room_price << " " << premium_room_price << std::endl;
}

void Hotel::print2()
{
    std::cout << unique_id << SPACE << name << SPACE << star_rating << 
    SPACE << city << SPACE << total_number_of_room << SPACE;
        printf("%.2f \n",cal_average());
}

float Hotel::cal_average()
{
    float average = 0;
    int count = 0;

    if(standard_room_price != 0) { average += standard_room_price; count++; }
    if(deluxe_room_price != 0) { average += deluxe_room_price; count++; }
    if(luxury_room_price != 0) { average += luxury_room_price; count++; }
    if(premium_room_price != 0) { average += premium_room_price; count++; }
    if(!standard_room_price && !deluxe_room_price && !luxury_room_price && !premium_room_price)
        return 0;

    return average / count;
}

void Hotel::put_average_rate(float location_avg_, float cleanless_avg_, float staff_avg_,
	float facilities_avg_, float value_avg_, float overall_avg_)
{
	has_rating = true;
	location_avg = location_avg_;
	cleanless_avg = cleanless_avg_;
	staff_avg = staff_avg_;
	facilities_avg = facilities_avg_;
	value_avg = value_avg_;
	overall_avg = overall_avg_;
}

float Hotel::cal_overall_rating(Consumer* temp_consumer)
{
	float location_manual = temp_consumer->get_location_manual();
	float cleanless_manual = temp_consumer->get_cleanless_manual();
	float staff_manual = temp_consumer->get_staff_manual();
	float facilities_manual = temp_consumer->get_facilities_manual();
	float value_manual = temp_consumer->get_value_manual();
	return (location_avg*location_manual + cleanless_manual*cleanless_avg + staff_manual*staff_avg +
		facilities_avg*facilities_manual + value_avg*value_manual) / (location_manual + cleanless_manual +
			staff_manual + facilities_manual + value_manual);
}

float Hotel::estimate_weights(Consumer* temp_consumer)
{
	std::vector<long double> w = temp_consumer->estimate_weights();
	return (location_avg*w[LOCATIN_NUM] + w[CLEANLESS_NUM] *cleanless_avg + w[STAFF_NUM] * staff_avg +
		facilities_avg*w[FACILITIES_NUM] + value_avg*w[VALUE_NUM]) / (w[LOCATIN_NUM] + w[CLEANLESS_NUM] +
			w[STAFF_NUM] + w[FACILITIES_NUM] + w[VALUE_NUM]);
}

float Hotel::get_rate(Consumer* temp_consumer)
{
	for (int i = 0 ; i < rate_vec.size() ; i++)
		if (rate_vec[i]->consumer_rate == temp_consumer)
			return rate_vec[i]->overall_rate;
	if (temp_consumer->is_active_manual())
		return cal_overall_rating(temp_consumer);
	else
		return estimate_weights(temp_consumer);
}

void Hotel::put_rate(Consumer* consumer_temp , std::vector <float> rates)
{
    for(int i = 0 ; i < rate_vec.size() ; i++)
        if(rate_vec[i]->consumer_rate ==  consumer_temp)
        {
            rate_vec[i]->location_rate = rates[0]; 
            rate_vec[i]->cleanliness_rate = rates[1]; 
            rate_vec[i]->staff_rate = rates[2]; 
            rate_vec[i]->facilities = rates[3]; 
            rate_vec[i]->value_for_money_rate = rates[4]; 
            rate_vec[i]->overall_rate = rates[5];
			return;
        }
    rate_vec.push_back(new Person_rate{consumer_temp,rates[0],rates[1],rates[2],rates[3],rates[4],rates[5]});    
}

void Hotel::print_rate()
{
	if (!has_rating) throw NO_RATING;
    std::cout << LOCATION << SAY ;printf("%.2f\n", location_avg );
    std::cout << CLEANLINESS << SAY ;printf("%.2f\n", cleanless_avg);
    std::cout << STAFF << SAY ;printf("%.2f\n", staff_avg);
    std::cout << FACILITIES << SAY ;printf("%.2f\n", facilities_avg);
    std::cout << VALUE_FOR_MONEY_ << SAY ;printf("%.2f\n", value_avg);
    std::cout << OVERALL_RATING_ << SAY ;printf("%.2f\n", overall_avg);
}

void Hotel::put_comments(std::string name , std::string order)
{
    if(order.find(COMMENT) != std::string::npos)
    {
        int index = order.find(COMMENT);
        int index1 = order.find(ENTER);
        comments.push_back(order.substr(index + 8, index1));
        user_names.push_back(name);
		std::cout << OK << std::endl;
    }
    else
        throw BAD_REQUEST;
}

void Hotel::print_comments(std::string order)
{
    for(int i = 0 ; i < comments.size() ; i++)
        std::cout << user_names[i] << SAY << comments[i] << std::endl;
}

bool Hotel::check_enough_room(std::string type , int quantity , int check_in , int check_out)
{
    for(int i = check_in ; i <= check_out ; i++)
    {
    if(!((!type.compare(LUXARY) && reserved_luxary_rooms_in_time[i] +  quantity <= num_of_luxary_rooms )
            ||  (!type.compare(DELUX) && reserved_deluxe_rooms_time[i] +  quantity <= num_of_deluxe_rooms)
            || (!type.compare(STANDARD) && reserved_standard_rooms_time[i] +  quantity <= num_of_standard_rooms)
            || (!type.compare(PREMIUM) && reserved_premium_rooms_in_time[i]+  quantity <= num_of_premium_rooms )))
            return false;
    }
    return true;
}

bool Hotel::check_member(std::string type , int quantity , int check_in , int check_out , int wallet)
{
    if(check_in > check_out || check_in < 1 || check_in > 30 ||
        check_out < 1 || check_out > 30) 
        throw BAD_REQUEST;

    if((!type.compare(LUXARY) && quantity * luxury_room_price > wallet)
        ||  (!type.compare(DELUX) && quantity * deluxe_room_price > wallet)
        || (!type.compare(STANDARD) && quantity * standard_room_price > wallet)
        || (!type.compare(PREMIUM) && quantity * premium_room_price > wallet))
        throw NOT_ENOUGH_CREDIT;

    if(!check_enough_room(type , quantity , check_in , check_out))
        throw NOT_ENOUGH_ROOM;

    return true;
}

Room* Hotel::which_room(std::string type , int quantity , int check_in , int check_out)
{
    if(!type.compare(LUXARY)) 
        return new Luxary_room(unique_id,type , quantity ,check_in,check_out,luxury_room_price);
    else if(!type.compare(DELUX))  
        return new Delux_room(unique_id,type,quantity,check_in,check_out,deluxe_room_price);
    else if(!type.compare(STANDARD))
       return new Standard_room(unique_id,type,quantity,check_in,check_out,standard_room_price);
    else if(!type.compare(PREMIUM))
        return new Premium_room(unique_id,type,quantity,check_in,check_out,premium_room_price);
    else 
        throw BAD_REQUEST;
}

void Hotel::increase_room(std::string type , int quantity , int check_in , int check_out)
{
    for(int i = check_in ; i <= check_out ; i++)
    {
        if(!type.compare(LUXARY)) 
            reserved_luxary_rooms_in_time[i] += quantity;
        else if(!type.compare(DELUX)) 
            reserved_deluxe_rooms_time[i] +=  quantity;
        else if(!type.compare(STANDARD))
            reserved_standard_rooms_time[i] +=  quantity;
        else if(!type.compare(PREMIUM))
            reserved_premium_rooms_in_time[i] +=  quantity;
    }
}

int Hotel::which_price(std::string type)
{
    if(!type.compare(LUXARY)) 
        return luxury_room_price;
    else if(!type.compare(DELUX)) 
        return deluxe_room_price;
    else if(!type.compare(STANDARD))
        return standard_room_price;
    else if(!type.compare(PREMIUM))
        return premium_room_price;
    else
        throw BAD_REQUEST;
}

std::vector<Room*> Hotel::reserve_room(std::string type , int quantity , int check_in , int check_out , int wallet)
{
    if(check_member(type,quantity,check_in,check_out,wallet))
    {
        std::vector <Room*> rooms;
        for(int i = 0 ; i < quantity ; i++)
        {
            Room* room = which_room(type , quantity , check_in , check_out);
            rooms.push_back(room);
        }
        increase_room(type,quantity,check_in,check_out);
        return rooms;
    }
}

void Hotel::free_room(std::string type , int quantity , int check_in , int check_out)
{
    if(!type.compare(LUXARY)) 
        for(int i = check_in ; i < check_out ; i++)
            reserved_luxary_rooms_in_time[i] -= quantity;
    else if(!type.compare(DELUX)) 
        for(int i = check_in ; i < check_out ; i++)
            reserved_deluxe_rooms_time[i] -= quantity;
    else if(!type.compare(STANDARD))
        for(int i = check_in ; i < check_out ; i++)
            reserved_standard_rooms_time[i] -= quantity;
    else if(!type.compare(PREMIUM))
        for(int i = check_in ; i < check_out ; i++)
            reserved_premium_rooms_in_time[i] -= quantity;
}


std::string Hotel::get_reserve_id(std::string type , int i , int check_in)
{   
    if(!type.compare(LUXARY)) 
        return FIRST_LUXURY + std::to_string(get_reserved_luxary_rooms(check_in) - i);
    
    else if(!type.compare(DELUX)) 
        return FIRST_DELUXE + std::to_string(get_reserved_deluxe_rooms(check_in) - i);

    else if(!type.compare(STANDARD))
        return FIRST_STANDARD + std::to_string(get_reserved_standard_rooms(check_in) - i);

    else if(!type.compare(PREMIUM))
        return FIRST_PREMIUM + std::to_string(get_reserved_premium_rooms(check_in) - i);
}




