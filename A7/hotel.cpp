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
        property_name = property_name_;
        hotel_star_rating = hotel_star_rating_;
        hotel_overview = hotel_overview_;
        property_amenities = property_amenities_;
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
        delux_room_price = delux_room_price_;
        luxury_room_price = luxury_room_price_;
        premium_room_price = premium_room_price_;
        average_price = cal_average();
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
    << property_name << std::endl 
    << "star: " << hotel_star_rating << std::endl
    << "overview: " << hotel_overview << std::endl
    << "amenities: "<< property_amenities << std::endl 
    << "city: " << city << std::endl;
    printf("latitude: %.2f\n", latitude);
    printf("longitude: %.2f\n", longitude);
    std::cout << "#rooms: " << num_of_standard_rooms << " " << num_of_deluxe_rooms << 
    " " << num_of_luxary_rooms << " " << num_of_premium_rooms << std::endl
    << "price: " << standard_room_price << " " << delux_room_price << " "
    << luxury_room_price << " " << premium_room_price << std::endl;
}

void Hotel::print2()
{
    std::cout << unique_id << SPACE << property_name << SPACE << hotel_star_rating << 
    SPACE << city << SPACE << total_number_of_room << SPACE;
        printf("%.2f \n",cal_average());
}

float Hotel::cal_average()
{
    float average = 0;
    int count = 0;

    if(standard_room_price != 0) { average += standard_room_price; count++; }
    if(delux_room_price != 0) { average += delux_room_price; count++; }
    if(luxury_room_price != 0) { average += luxury_room_price; count++; }
    if(premium_room_price != 0) { average += premium_room_price; count++; }
    if(!standard_room_price && !delux_room_price && !luxury_room_price && !premium_room_price)
        return 0;

    return average / count;
}

void Hotel::put_rate(Consumer* consumer_temp , std::vector <float> rates)
{
    if(rate_vec.size() == 0)
        rate_vec.push_back(new Person_rate{consumer_temp,rates[0],rates[1],rates[2],rates[3],rates[4],rates[5]});    

    for(int i = 0 ; i < rate_vec.size() ; i++)
        if(rate_vec[i]->consumer_rate ==  consumer_temp)
        {
            rate_vec[i]->location_rate = rates[0]; 
            rate_vec[i]->cleanliness_rate = rates[1]; 
            rate_vec[i]->staff_rate = rates[2]; 
            rate_vec[i]->facilities = rates[3]; 
            rate_vec[i]->value_for_money_rate = rates[4]; 
            rate_vec[i]->overall_rate = rates[5]; 
        }
}

void Hotel::print_rate()
{
	if (rate_vec.size() == 0) throw NO_RATING;
    float location_rate_average = 0;float cleanliness_rate_average = 0;
    float staff_rate_average = 0;float facilities_average = 0;
    float value_for_money_rate_average = 0;float overall_rate_average = 0;
    for(int i = 0 ; i < rate_vec.size() ; i++)
    {
        location_rate_average += rate_vec[i]->location_rate;
        cleanliness_rate_average += rate_vec[i]->cleanliness_rate;
        staff_rate_average += rate_vec[i]->staff_rate;
        facilities_average += rate_vec[i]->facilities;
        value_for_money_rate_average += rate_vec[i]->value_for_money_rate;
        overall_rate_average += rate_vec[i]->overall_rate;
    }
    std::cout << LOCATION << SAY ;printf("%.2f\n",location_rate_average / rate_vec.size()); 
    std::cout << CLEANLINESS << SAY ;printf("%.2f\n",cleanliness_rate_average / rate_vec.size()); 
    std::cout << STAFF << SAY ;printf("%.2f\n", staff_rate_average / rate_vec.size());
    std::cout << FACILITIES << SAY ;printf("%.2f\n", facilities_average / rate_vec.size());
    std::cout << VALUE_FOR_MONEY_ << SAY ;printf("%.2f\n",value_for_money_rate_average / rate_vec.size());
    std::cout << OVERALL_RATING_ << SAY ;printf("%.2f\n", overall_rate_average / rate_vec.size()); 
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
        ||  (!type.compare(DELUX) && quantity * delux_room_price > wallet)
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
        return new Luxary_room(unique_id,type,quantity,check_in,check_out,luxury_room_price);
    else if(!type.compare(DELUX)) 
        return new Delux_room(unique_id,type,quantity,check_in,check_out,delux_room_price);
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
        return delux_room_price;
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
            Room* room = which_room(type,quantity,check_in,check_out);
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



