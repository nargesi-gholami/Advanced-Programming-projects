#ifndef RECEPTION
#define RECEPTION _RECEPTION_

#include "hotel.hpp"
#include "hotel_consumer.hpp"
#include "filter.hpp"
#include "Room.hpp"

#include <exception>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#define BAD_REQUEST "Bad Request"
#define PERMISSIN_DENIED "Permission Denied"
#define NOT_FOUND "Not Found"

#define EMPTY "Empty"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"

#define LOCATION_RATE 0
#define CLEANLINESS_RATE 1
#define STAFF_RATE 2
#define FACILITIES_RATE 3
#define VALUE_FOR_MONE_RATE 4 
#define OVERALL_RATING_RATE 5

#define UNDER_LINE ','
#define SPACE_ ' ' 
#define OK "OK"
#define ID "id"
#define GET "GET"
#define POST "POST"
#define DELETE "DELETE"
#define WALLET "wallet"
#define RESERVES "reserves"
#define COMMENTS "comments"
#define RATING "ratings"

#define QUESTION_MARK '?'

#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define FILTERS "filters"
#define HOTELS "hotels"
#define HOTEL "hotel"
#define TYPE "type" 
#define QUANTITY "quantity" 
#define CHECK_IN "check_in" 
#define CHECK_OUT "check_out"
#define CITY "city"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MAX_PRICE "max_price"
#define MIN_PRICE "min_price"
#define USER_NAME "username"
#define PASS "password"
#define EMAIL "email"

#define TYPE_PLACE 0
#define Q_PLACE 1
#define IN_PLACE 2
#define OUT_PLACE 3
#define SUB_GET 3
#define SUB_POST 4
#define SUB_DELETE 6

typedef std::vector <Hotel*> hotel_vec;
typedef std::vector <Consumer*> consumer_vec;

class Reception
{
    public:
        Reception(std::string address);
        ~Reception();
        Hotel* find_hotel(std::string order , char space = SPACE_);
        Hotel* read_all_information(std::string id , std::ifstream& hotel_file);
        Hotel* find_hotel_by_id(std::string id);
        Room* put_room_information(std::string order , Hotel* hotel_temp);

        void signup(std::string order);
        void login(std::string order);
        void enter_order();
        void logout();
        void is_login();
        void delete_filter();
        void filter(std::string order);
        void apply_filter(std::string order);
        void delete_reserve(std::string id);
        void put_rating(std::string order);
        void reserve_room(std::string order);
        void person_wallet(std::string order);
        void enter_GET_order(std::string order);
        void enter_POST_order(std::string order);
        void enter_DELETE_order(std::string order);
        void print_hotel_info(std::string order);
        void print_hotel_rating(std::string order);
        void print_rating(std::string order , std::string model);
        void print_comment(std::string order , std::string model);
        bool check(std::string user_name , std::string email_address);
        bool enter_common_command(std::string order , std::string model = GET );
		bool is_befor_exist(std::string email , std::string user_name_or_pass);
        int is_exist(std::string email , std::string user_name);

        hotel_vec sort_hotels(hotel_vec input_hotels);
        hotel_vec get_hotel();
        

    private:

        hotel_vec read_hotels_information(std::string address);
        Consumer* currrent_consumer;
        hotel_vec filter_hotel;
        consumer_vec consumers;
        hotel_vec hotels;
		bool filter_applied;
};  




#endif