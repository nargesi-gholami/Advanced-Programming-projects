#include "reception.hpp"

Reception::Reception(std::string address1 , std::string address2)
{
	hotels = read_hotels_information(address1);
	put_hotels_rates(address2);
    current_consumer = new Consumer("0","0","0",false);
	filter_applied = false;
	asc_or_dec = ASC;
	kind = ID;
}

Reception::~Reception()
{}

std::string get_information(std::ifstream& hotel_file,char space = UNDER_LINE)
{
    std::string temp;
    getline(hotel_file,temp,space);
    return temp;
}

Hotel* Reception::read_all_information(std::string id,std::ifstream& hotel_file)
{
    std::string unique_id_ = id;
    std::string name_ = get_information(hotel_file);
    int star_rating_ = stoi(get_information(hotel_file));
    std::string overview_ = get_information(hotel_file);
    std::string amenities_ = get_information(hotel_file);
    std::string city_ = get_information(hotel_file);
    float latitude_ = stof(get_information(hotel_file));
    float longitude_ = stof(get_information(hotel_file));
    std::string image_url_ = get_information(hotel_file);
    int num_of_standard_rooms_ = stoi(get_information(hotel_file));
    int num_of_deluxe_rooms_ = stoi(get_information(hotel_file));
    int num_of_luxary_rooms_ = stoi(get_information(hotel_file));
    int num_of_premium_rooms_ = stoi(get_information(hotel_file));
    int standard_room_price_ = stoi(get_information(hotel_file));
    int delux_room_price_ = stoi(get_information(hotel_file));
    int luxury_room_price_ = stoi(get_information(hotel_file));
    int premium_room_price_ = stoi(get_information(hotel_file,ENTER));
    Hotel* hotel = new Hotel (unique_id_ , name_,
        star_rating_, overview_,
        amenities_, city_,
        longitude_,latitude_,
        image_url_, num_of_standard_rooms_,
        num_of_deluxe_rooms_, num_of_luxary_rooms_,
        num_of_premium_rooms_, standard_room_price_,
        delux_room_price_, luxury_room_price_,
        premium_room_price_);
    return hotel;
}

hotel_vec Reception::read_hotels_information(std::string address1)
{
    std::ifstream hotel_file(address1);
    std::string id;
	std::getline(hotel_file ,id, ENTER);
    while(std::getline(hotel_file , id , UNDER_LINE))
    {
        Hotel* hotel = read_all_information(id,hotel_file);
        hotels.push_back(hotel);
    }       
    return hotels;
}

void Reception::put_hotels_rates(std::string address)
{
	std::ifstream rating_file(address);
	std::string id;
	std::getline(rating_file, id, ENTER);
	while (std::getline(rating_file, id, UNDER_LINE))
	{
		Hotel* hotel = find_hotel_by_id(id);
		float location_avg = stof(get_information(rating_file));
		float cleanless_avg = stof(get_information(rating_file));
		float staff_avg = stof(get_information(rating_file));
		float facilities_avg = stof(get_information(rating_file));
		float value_avg = stof(get_information(rating_file));
		float overall_avg = stof(get_information(rating_file , ENTER));
		hotel->put_average_rate(location_avg, cleanless_avg, staff_avg, facilities_avg , value_avg , overall_avg);
	}
}

template <typename I>
void print(I thing)
{
    std::cout << thing << std::endl;
}

bool check_exist_in_string(int index)
{
	if (index == std::string::npos)
		throw BAD_REQUEST;
}

void Reception::is_login()
{
    if(current_consumer->is_login())
        return;
    else
        throw PERMISSIN_DENIED;
}

bool is_question_mark(std::string order)
{
    if(order.find(QUESTION_MARK) != std::string::npos)
        return true;
    else
        throw BAD_REQUEST;
}

void Reception::change_defualt_filter(bool filter_mode)
{
	current_consumer->set_default_price_filter(filter_mode);
	current_consumer->set_default_filter(filter_mode);
	if(!current_consumer->is_default_mode())
		filter_hotel.clear();
}

void Reception::default_filter_setting(std::string order)
{
	is_login();
	is_question_mark(order);
	if (order.find(ACTIVE) != std::string::npos)
	{
		if (order.find(TRUE) != std::string::npos)
			change_defualt_filter(true);
		else if (order.find(FALSE) != std::string::npos)
			change_defualt_filter(false);
		else
			throw BAD_REQUEST;
		print(OK);
	}
	else
		throw BAD_REQUEST;
}

void Reception::check_defualt_filter()
{
	if (current_consumer->is_default_mode_price())
	{
		if (filter_hotel.empty())
			if (current_consumer->get_reserve_num() >= TEN)
			{
				current_consumer->set_default_filter(true);
				hotel_vec final_hotel = get_hotel();
				Default_filter* filter = new Default_filter(final_hotel , current_consumer->cal_reserved_room_price_average()
					, current_consumer->cal_standard_deviation_room_price());
				filter_hotel = filter->apply();
			}
	}
}

template < typename I >
hotel_vec Reception::sort_hotels(I (Hotel::*func_ptr))
{
	hotel_vec final_hotel = get_hotel();
	for (int i = 0 ; i < final_hotel.size() - 1 ; i++)
	{
		for (int j = 0 ; j < final_hotel.size() - i - 1 ; j++)
		{
			if ((((final_hotel[j]->*func_ptr)() > (final_hotel[j + 1]->*func_ptr)()) && asc_or_dec == ASC)
				|| (((final_hotel[j]->*func_ptr)() < (final_hotel[j + 1]->*func_ptr)()) && asc_or_dec == DEC))
				std::swap(final_hotel[j], final_hotel[j + 1]);
			if ((final_hotel[j]->*func_ptr)() == (final_hotel[j + 1]->*func_ptr)())
				if (final_hotel[j]->get_id() > final_hotel[j + 1]->get_id())
					std::swap(final_hotel[j], final_hotel[j + 1]);
		}
	}
	return final_hotel;
}

hotel_vec Reception::sort_hotels_rating_personal ()
{
	hotel_vec final_hotel = get_hotel();
	for (int i = 0 ; i < final_hotel.size() - 1 ; i++)
	{
		for (int j = 0 ; j < final_hotel.size() - i - 1 ; j++)
		{
			if (((final_hotel[j]->get_rate(current_consumer) > (final_hotel[j + 1]->get_rate(current_consumer))) && asc_or_dec == ASC)
				|| ((final_hotel[j]->get_rate(current_consumer)) < (final_hotel[j + 1]->get_rate(current_consumer))) && asc_or_dec == DEC)
				std::swap(final_hotel[j], final_hotel[j + 1]);
			if ((final_hotel[j]->get_rate(current_consumer)) == (final_hotel[j + 1]->get_rate(current_consumer)))
				if (final_hotel[j]->get_id() > final_hotel[j + 1]->get_id())
					std::swap(final_hotel[j], final_hotel[j + 1]);
		}
	}
	return final_hotel;
}

hotel_vec Reception::which_kind(std::string kind)
{
	if (!kind.compare(ID))
		return sort_hotels(&Hotel::get_id);
	else if (!kind.compare(CITY))
		return sort_hotels(&Hotel::get_city);
	else if (!kind.compare(NAME))
		return sort_hotels(&Hotel::get_name);
	else if (!kind.compare(STAR_RATING))
		return sort_hotels(&Hotel::get_star);
	else if (!kind.compare(S_PRRICE))
		return sort_hotels(&Hotel::get_standard_price);
	else if (!kind.compare(L_PRICE))
		return sort_hotels(&Hotel::get_luxary_price);
	else if (!kind.compare(D_PRICE))
		return sort_hotels(&Hotel::get_deluxe_price);
	else if (!kind.compare(P_PRICE))
		return sort_hotels(&Hotel::get_premium_price);
	else if (!kind.compare(AVERAGE_PRICE))
		return sort_hotels(&Hotel::get_average_price);
	else if (!kind.compare(RATING_OVERALL))
		return sort_hotels(&Hotel::get_overall_rating);
	else if (!kind.compare(RATING_PERSONAL))
		return sort_hotels_rating_personal();
	else
		throw BAD_REQUEST;
}

void Reception::sort(std::string order)
{
	is_login();
	is_question_mark(order);
	check_exist_in_string(order.find(PROPERTY));
	int index = order.find(PROPERTY) + 9;
	int index_ = order.find(SPACE, index);
	check_exist_in_string(index_);
	kind = order.substr(index, index_ - index);
	if (order.find(ASCENDING) != std::string::npos)
		asc_or_dec = ASC;
	else if (order.find(DESCENDING) != std::string::npos)
		asc_or_dec = DEC;
	else
		throw BAD_REQUEST;
	print(OK);
}

void Reception::post_manual_weights(std::string order)
{
	int index = order.find(ACTIVE);
	check_exist_in_string(index);
	if (order.find(TRUE) != std::string::npos)
	{
		current_consumer->set_manual_weight(true);
		current_consumer->post_manual_weights(order);
	}
	else if (order.find(FALSE) != std::string::npos)
		current_consumer->set_manual_weight(false);
	else
		throw BAD_REQUEST;
	print(OK);
}

void Reception::print_manual_weights(std::string order)
{
	if (!current_consumer->is_active_manual()) { print(FALSE_ACTIVE); return; }
		current_consumer->print_manual_weights();
}

void Reception::manual_weight(std::string order, std::string model)
{
	is_login();
	if (!model.compare(GET))
		print_manual_weights(order);
	else if (!model.compare(POST))
		post_manual_weights(order);
}

void Reception::print_hotel_info(std::string order)
{
    is_login();
    if(order.find(ID) != std::string::npos)
    {
        int index1 = order.find(ID) + 3;
        Hotel* hotel_temp = find_hotel_by_id(order.substr(index1, order.size() - index1));
        hotel_temp->print1();
    }
    else if(order.find(ID) == std::string::npos)
    {
		check_defualt_filter();
        hotel_vec final_hotels = get_hotel();
        if(hotels.empty() || (filter_applied && filter_hotel.empty())) throw EMPTY;
        final_hotels = which_kind(kind);
		if (current_consumer->is_default_mode()) print(DEFAULT_FILTER_MESSAGE);
        for(int i = 0 ; i < final_hotels.size() ; i++)
            final_hotels[i]->print2();
    }
    else 
        throw BAD_REQUEST;
}

void Reception::person_wallet(std::string order)
{
    is_login();
    is_question_mark(order);;
    current_consumer->see_wallet(order);
}

Hotel* Reception::find_hotel_by_id(std::string id)
{
    for(int i = 0 ; i < hotels.size() ; i++)
        if(!hotels[i]->get_id().compare(id))
            return hotels[i];
    throw NOT_FOUND;
}

float check_rating(std::string word , std::string order )
{
    int index = order.find(word) + word.size() + 1;
    if(index == std::string::npos)
        throw BAD_REQUEST;
    float rate = stof(order.substr(index , order.find(SPACE, index + 1) - index));
    if(rate < 1 || rate > 5)
        throw BAD_REQUEST;
    return rate;
}

std::vector<float> put_rates(std::string order)
{    
    std::vector<float> rates;
    rates.push_back(check_rating(LOCATION , order));
    rates.push_back(check_rating(CLEANLINESS , order));
    rates.push_back(check_rating(STAFF , order));
    rates.push_back(check_rating(FACILITIES , order));
    rates.push_back(check_rating(VALUE_FOR_MONEY, order));
    rates.push_back(check_rating(OVERALL_RATING, order));
    return rates;
}

Hotel* Reception::find_hotel(std::string order,char space)
{
    int index1 = order.find(HOTEL) + 6;
    int index2 = order.find(SPACE , index1 + 1);
    return find_hotel_by_id(order.substr(index1 , index2 - index1));
}

void Reception::put_rating(std::string order)
{
	int index_ = order.find(HOTEL) + 6;
	int index = order.find(SPACE, index_ + 1);
	std::string id = order.substr(index_, index - index_);
    Hotel* temp_hotel = find_hotel_by_id(id);
    std::vector <float> rates = put_rates(order);
    temp_hotel->put_rate(current_consumer,rates);
	current_consumer->put_rate(temp_hotel->get_id() , rates);
    print(OK);
}

void Reception::print_hotel_rating(std::string order)
{
    int index_ = order.find(HOTEL) + 6;
    int index = order.find(SPACE,index_ + 1);
    order = order.substr(index_,index);
    Hotel* temp_hotel = find_hotel_by_id(order);
    temp_hotel->print_rate();
}

void Reception::print_rating(std::string order,std::string model)
{
    is_login();
    is_question_mark(order);
    int check_ = order.find(HOTEL); 
    if((check_ == std::string::npos)) throw BAD_REQUEST;

    if(!model.compare(POST))
        put_rating(order);
    else if(!model.compare(GET))
        print_hotel_rating(order);
}

void Reception::print_comment(std::string order,std::string model)
{
    is_login();
    is_question_mark(order);
	int index1 = order.find(HOTEL) + 6;
    int index2 = order.find(SPACE,index1);
    std::string id = order.substr(index1  , index2 - index1);
    Hotel* temp_hotel = find_hotel_by_id(id);

    if(!model.compare(GET))
        temp_hotel->print_comments(order);

    else if(!model.compare(POST))
        temp_hotel->put_comments(current_consumer->get_user_name(),order.substr(index2));
}

Room* Reception::put_room_information(std::string order , Hotel* hotel_temp)
{
    std::vector <int> position = get_position(order , {TYPE,QUANTITY,CHECK_IN,CHECK_OUT});
    std::string type = order.substr(position[0] , order.find(SPACE,position[0]) - position[0]);
    int quantity = stoi(order.substr(position[1] , order.find(SPACE,position[1]) - position[1]));
    int check_in = stoi(order.substr(position[2] , order.find(SPACE,position[2]) - position[2]));
    int check_out = stoi(order.substr(position[3] , order.find(SPACE,position[3]) - position[3]));
    std::vector <Room*> rooms = hotel_temp->reserve_room(type , quantity , check_in , check_out , current_consumer->get_wallet());
    current_consumer->dec_wallet(quantity * hotel_temp->which_price(type));
    current_consumer->put_reserve(rooms);    
    return rooms[0];
}

void Reception::reserve_room(std::string order)
{
    is_login();
    if(order.find(HOTEL) != std::string::npos)
    {
		is_question_mark(order);
        Hotel* hotel_temp = find_hotel(order);
		Room* sample_room = put_room_information(order , hotel_temp);
        int quantity = sample_room->get_quantity();
        for (int i = 0 ; i < quantity ; i++)
        {
            std::cout << (hotel_temp->get_reserve_id(sample_room->get_type() , quantity - i - 1 
                                            , sample_room->get_check_in()));
            //if(i != quantity - 1) 
            std::cout << (SPACE);
        }
        std::cout << (ENTER);
    }
    else
        current_consumer->print_reserve();
}

bool Reception::check_exist(std::string user_name,std::string email_address)
{
    for(int i = 0 ; i < consumers.size() ; i++)
        if(!user_name.compare(consumers[i]->get_user_name()) ||
             (email_address.compare(consumers[i]->get_email())))
            throw BAD_REQUEST;
    return true;
}

int Reception::is_exist(std::string email, std::string pass)
{   
	for (int i = 0; i < consumers.size(); i++)
		if (!email.compare(consumers[i]->get_email()) &&
			!pass.compare(consumers[i]->get_password()))
		{
			if (i == 0)
				return -1;
			return i;
		}
    return 0;            
}

bool Reception::is_befor_exist(std::string email, std::string user_name)
{
	for (int i = 0; i < consumers.size(); i++)
		if (!email.compare(consumers[i]->get_email()) ||
			!user_name.compare(consumers[i]->get_user_name()))
				return false;
	return true;
}

void Reception::signup(std::string order)
{
    is_question_mark(order);
    std::vector<int> positions = get_position(order,{EMAIL , USER_NAME , PASS});
    std::string email,user_name,password;
    email = order.substr(positions[0] , order.find(SPACE,positions[0] + 1) - positions[0]);
    user_name = order.substr(positions[1] , order.find(SPACE,positions[1] + 1) - positions[1]);
    password = order.substr(positions[2] , order.find(SPACE,positions[2] + 1) - positions[2]);
	if (is_befor_exist(email, user_name))
	{
		consumers.push_back(new Consumer(email, user_name, password));
		current_consumer = consumers[consumers.size() - 1];
		print(OK);
		return;
	}
    throw BAD_REQUEST;
}

void Reception::login(std::string order)
{
    if(current_consumer->is_login())
        throw BAD_REQUEST;
    is_question_mark(order);
    std::vector<int> positions = get_position(order,{EMAIL,PASS});
    std::string email = order.substr(positions[0] , order.find(SPACE,positions[0] + 1) - positions[0]);
    std::string password = order.substr(positions[1] , order.find(SPACE,positions[1] + 1) - positions[1]);
    if(is_exist(email,password))
    {
        int i = is_exist(email,password);
		if (i == -1) i++;
        if(consumers[i]->set_login())
        {
            current_consumer = consumers[i];
            print(OK);
            return;
        }
    }
    throw(BAD_REQUEST);                
}

void Reception::logout()
{
    if(current_consumer->set_logout())
    {
        current_consumer = new Consumer("0","0","0",false);
        filter_hotel.clear();
		print(OK);
        return;
    }
    else
        throw PERMISSIN_DENIED;
}

bool Reception::enter_common_command(std::string order,std::string model)
{
    if(order.find(HOTELS) != std::string::npos)
    {
        print_hotel_info(order);
        return true;
    }
    else if((order.find(WALLET) != std::string::npos))
    {
        person_wallet(order);
        return true;
    }
    else if(order.find(RATING) != std::string::npos)
    {
        print_rating(order,model);
        return true;
    }
    else if(order.find(RESERVES) != std::string::npos)
    {
        reserve_room(order);
        return true;
    }
    else if(order.find(COMMENTS) != std::string::npos)
    {
        print_comment(order,model); 
        return true;
    }
	else if (order.find(MANUAL_WEIGHTS) != std::string::npos)
	{
		manual_weight(order,model);
		return true;
	}
    return false;
}

void Reception::print_estimate()
{
	is_login();
	current_consumer->estimate_weights();
	current_consumer->print_manual_weights();
}

void Reception::enter_GET_order(std::string order)
{
	if (enter_common_command(order))
		return;
	if (order.find(ESTIMATED_WEIGHTS) != std::string::npos)
		print_estimate();
    else
        throw(NOT_FOUND);
}

void Reception::enter_POST_order(std::string order)
{
	if (enter_common_command(order , POST))
		return;
	else if (order.find(SIGNUP) != std::string::npos)
		signup(order);

	else if (order.find(LOGIN) != std::string::npos)
		login(order);

	else if (order.find(LOGOUT) != std::string::npos)
		logout();

	else if (order.find(FILTERS) != std::string::npos)
		filter(order);

	else if (order.find(SORT) != std::string::npos)
		sort(order);

	else if (order.find(DEFAULT_FILTER) != std::string::npos)
		default_filter_setting(order);
    else
        throw(NOT_FOUND);
}

std::vector <std::string> check_correct_input(std::string order)
{
	std::vector <int> places = get_position(order, {TYPE , QUANTITY , CHECK_IN , CHECK_OUT});
    std::string type = order.substr(places[0]  , order.find(SPACE , places[0]) - (places[0]));
    std::string quantity = order.substr(places[1]  , order.find(SPACE , places[1]) - (places[1]));
    std::string check_in = order.substr(places[2]  , order.find(SPACE , places[2]) - (places[2]));
    std::string check_out = order.substr(places[3]  , order.size() - (places[3]));
    std::vector <std::string> places_;
    places_.push_back(type);places_.push_back(quantity);
    places_.push_back(check_in);places_.push_back(check_out);
    return places_;
}

hotel_vec Reception::get_hotel()
{
    if(filter_hotel.empty())
        return hotels;
    else
        return filter_hotel;
}

void Reception::apply_filter(std::string order)
{
    hotel_vec final_hotel = get_hotel();
    if(order.find(CITY) != std::string::npos)
    {
		int index = order.find(CITY) + 5;
		int index_ = order.find(SPACE);
        City_filter* filter = new City_filter(final_hotel,order.substr(index,index - index_));
        filter_hotel = filter->apply();
    }
    else if(order.find(MIN_STAR) != std::string::npos && order.find(MAX_STAR) != std::string::npos)
    {
		int min = stoi(order.substr(order.find(MIN_STAR) + 9 , 1));
		int max = stoi(order.substr(order.find(MAX_STAR) + 9 , 1));
        Star_filter* filter = new Star_filter(final_hotel,min,max);
        filter_hotel = filter->apply();
    }
    else if(order.find(MAX_PRICE) != std::string::npos && order.find(MIN_PRICE) != std::string::npos)
    {
		float min = stof(order.substr(order.find(MIN_PRICE) + 10 , order.find(SPACE, order.find(MIN_PRICE) + 10) - (order.find(MIN_PRICE) + 10)));
		float max = stof(order.substr(order.find(MAX_PRICE) + 10 , order.find(SPACE, order.find(MAX_PRICE) + 10) - (order.find(MAX_PRICE) + 10)));
        Price_filter* filter = new Price_filter(final_hotel,min,max);
        filter_hotel = filter->apply();
    }
    else
    {
        std::vector <std::string> places = check_correct_input(order);
        Quantity_filter* filter = new Quantity_filter(final_hotel,places[TYPE_PLACE],stoi(places[Q_PLACE]),stoi(places[IN_PLACE]),stoi(places[OUT_PLACE]));
		filter_hotel = filter->apply();
    }
}

void Reception::filter(std::string order)
{
	is_login();
    is_question_mark(order);
    apply_filter(order);
    print(OK);
	filter_applied = true;
}

void Reception::delete_filter()
{
    is_login();
    filter_hotel.clear();
	filter_applied = false;
	print(OK);
}

void Reception::delete_reserve(std::string id)
{
    is_login();
    is_question_mark(id);
    int reserve_id; 
	if (id.find(ID) != std::string::npos)
	{
		int index = id.find(ID) + 3;
		reserve_id = stoi(id.substr(index));
	}
    else 
        throw BAD_REQUEST; 
    
    Room* deleted_room = current_consumer->delete_room(reserve_id);
    Hotel* temp_hotel = find_hotel_by_id(deleted_room->get_hotel_id());
    temp_hotel->free_room(deleted_room->get_type(),deleted_room->get_quantity(),
                            deleted_room->get_check_in(),deleted_room->get_check_out());
    print(OK);
}

void Reception::enter_DELETE_order(std::string order)
{
    if(order.find(FILTERS) != std::string::npos)
        delete_filter();
    else if(order.find(RESERVES) != std::string::npos)
        delete_reserve(order.substr(15));
    else
        throw(NOT_FOUND);
}

void Reception::enter_order()
{
    std::string order;
    while(getline(std::cin , order , ENTER))
    {
        try
        {
            if(!order.substr(0 , SUB_GET).compare(GET))
                enter_GET_order(order);
                
            else if(!order.substr(0 , SUB_POST).compare(POST))
                enter_POST_order(order);
            
            else if(!order.substr(0 , SUB_DELETE).compare(DELETE))
                enter_DELETE_order(order);

            else
                throw(BAD_REQUEST);
        }
        catch(const char* error_message)
        {
            print(error_message);
        }
    }

}