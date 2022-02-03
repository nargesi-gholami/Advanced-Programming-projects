#ifndef HOTEL_
#define HOTEL_ _HOTEL_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <map>

#include "hotel_consumer.hpp"
#include "Room.hpp"

#define STAFF "staff"
#define COMMENT "comment"
#define LOCATION "location"
#define FACILITIES "facilities"
#define CLEANLINESS "cleanliness"
#define VALUE_FOR_MONEY_ "value for money"
#define OVERALL_RATING_ "overall rating"

#define SAY ": "
#define SPACE ' '
#define ENTER '\n' 

#define DELUX "deluxe"
#define LUXARY "luxury"
#define PREMIUM "premium" 
#define STANDARD "standard"

#define NO_RATING "No Rating"
#define NOT_ENOUGH_ROOM "Not Enough Room"
#define NOT_ENOUGH_CREDIT "Not Enough Credit"

typedef struct people_rating Person_rate;


class Hotel
{
    public:
        Hotel();
            Hotel(std::string unique_id_ , std::string property_name_,
                int hotel_star_rating_ , std::string hotel_overview_,
                std::string property_amenities_ , std::string city_,
                float longitude_ , float latitude_,
                std::string image_url_ , int num_of_standard_rooms_,
                int num_of_deluxe_rooms_ , int num_of_luxary_rooms_,
                int num_of_premium_rooms_ , int standard_room_price_,
                int delux_room_price_ , int luxury_room_price_,
                int premium_room_price_);
            ~Hotel();
        std::vector<Room*> reserve_room(std::string type , int quantity , int check_in , int check_out , int wallet);
        Room* which_room(std::string type , int quantity , int check_in , int check_out);
        bool check_member(std::string type , int quantity , int check_in , int check_out , int wallet);
        bool check_enough_room(std::string type , int quantity , int check_in , int check_out);
        void free_room(std::string type , int quantity , int check_in , int check_out);
        void increase_room(std::string type , int quantity , int check_in , int check_out);
        void put_rate(Consumer* consumer_temp , std::vector <float> rates);
        void put_comments(std::string name , std::string order);
        void print_comments(std::string order);
        void print_rate();
        void print1();
        void print2();

        float cal_average();
		float get_price() { return average_price; }

        std::string get_city() { return city; }
        std::string get_id(){return unique_id; };

        int which_price(std::string type);
        int get_average_price() { return int(average_price); }
        int get_star() { return hotel_star_rating; }
        int get_reserved_standard_rooms(int check_in) { return reserved_standard_rooms_time[check_in];}
        int get_reserved_deluxe_rooms(int check_in) { return reserved_deluxe_rooms_time[check_in];}
        int get_reserved_luxary_rooms(int check_in) { return reserved_luxary_rooms_in_time[check_in];}
        int get_reserved_premium_rooms(int check_in) { return reserved_premium_rooms_in_time[check_in];}
        std::string get_reserve_id(std::string type , int i , int check_in);
    private:
        std::vector <Person_rate*> rate_vec;
        std::string unique_id;
        std::string property_name;
        int hotel_star_rating;
        std::string hotel_overview;
        std::string property_amenities;
        std::string city;
        float longitude;
        float latitude;
        std::string image_url;
        int num_of_standard_rooms;
        int num_of_deluxe_rooms;
        int num_of_luxary_rooms;
        int num_of_premium_rooms;
        int total_number_of_room;
        int standard_room_price;
        int delux_room_price;
        int luxury_room_price;
        int premium_room_price;
        float average_price;
        std::vector <std::string> comments;  
        std::vector <std::string> user_names;
        std::map< int , int > reserved_standard_rooms_time;
        std::map< int , int > reserved_deluxe_rooms_time;
        std::map< int , int > reserved_luxary_rooms_in_time;
        std::map< int , int > reserved_premium_rooms_in_time;
};

struct people_rating
{
    Consumer* consumer_rate;
    float location_rate;
    float cleanliness_rate;
    float staff_rate;
    float facilities;
    float value_for_money_rate;
    float overall_rate;
};



#endif