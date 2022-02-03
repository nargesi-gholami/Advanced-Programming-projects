#ifndef HOTEL_CONCUMER
#define HOTEL_CONCUMER _HOTEL_CONCUMER_

#include <string>
#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath> 
#include <random>
#include "Room.hpp"

#define COUNT "count"
#define AMOUNT "amount"
#define PERMISSIN "Permission Denied"
#define BAD_REQUEST "Bad Request"
#define NOT_FOUND "Not Found"
#define SPACE ' '
#define OK "OK"
#define EMPTY "Empty"

#define GET "GET"
#define POST "POST"

#define ACTIVE_TRUE "active true "
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"

#define LOCATIN_NUM 0
#define CLEANLESS_NUM 1
#define STAFF_NUM 2
#define FACILITIES_NUM 3
#define VALUE_NUM 4

#define SUM 1
#define SUB 0

#define FIRST_RATING 0
#define LAST_RATING 5

#define TRUNCATE_NUM 100
#define MIN_PEOPLE_RATE 5
#define INSUFFICENT_RATING "Insufficient Ratings"
#define EPSILON pow(10,-4)
#define ALFA 1

typedef struct hotel_rating Hotel_rate;


class Consumer
{
    public:
        Consumer(std::string user_name_,std::string email_address_,
                std::string password_,bool enterred_= true);
        ~Consumer();
        std::string get_email(){ return email_address;};
        std::string get_user_name(){return user_name;};
        std::string get_password() { return password;}
        int get_wallet() { return wallet[wallet.size() - 1];} 
		int get_reserve_num() { return reserved_room.size(); }

		float cal_reserved_room_price_average();
		float cal_standard_deviation_room_price();


        bool set_login();
        bool set_logout();
        bool is_login();

        void see_wallet(std::string order);
        void print_wallet(int count);
        void increase_wallet(float count);

		void put_rate(std::string Hotel_id , std::vector <float> rates);

        void print_reserve();
        void dec_wallet(int money);
        void put_reserve(std::vector <Room*> reserved);
        Room* delete_room(int id);

		void set_manual_weight(bool mode) { active_manual_weight = mode; }
		bool is_active_manual() { return active_manual_weight; }

		void set_default_price_filter(bool mode) { default_price_filter = mode; }
		void set_default_filter(bool mode) { default_filter = mode;  }
		bool is_default_mode() { return default_filter; }
		bool is_default_mode_price() { return default_price_filter; }

		void print_manual_weights();
		void post_manual_weights(std::string order);
		float get_location_manual() {return location_manual;}
		float get_cleanless_manual() { return cleanless_manual; }
		float get_staff_manual() {return staff_manual;}
		float get_facilities_manual() { return facilities_manual; }
		float get_value_manual() { return value_manual; }
		int get_number_of_room();

		std::vector<long double>  estimate_weights();
		std::vector<long double>  estimate_rating();
		void initilize_estimate_rate();
		long double E(Hotel_rate* rate);
		long double f(Hotel_rate* rate);
		long double d_E(Hotel_rate* rate, int number);
		void increase_manual_weights(int number , bool sum);
		void put_weights();

    private:
		std::vector <Hotel_rate*> hotel_rates;
		std::vector <std::vector <Room*>> reserved_room;
        std::vector <int> deleted_id;
		std::vector <float> wallet;
		std::string email_address;
		std::string user_name;
		std::string password;
		bool enterred;
		int reserves;
		bool default_price_filter;
		bool default_filter;
		bool active_manual_weight;

		bool manual_calcualted;
		long double location_manual;
		long double cleanless_manual;
		long double staff_manual;
		long double facilities_manual;
		long double value_manual;
		std::vector <long double> w;
};

struct hotel_rating
{
	std::string hotel_id_rate;
	float location_rate;
	float cleanliness_rate;
	float staff_rate;
	float facilities;
	float value_for_money_rate;
	float overall_rate;
};

std::vector <int> get_position(std::string order, std::vector<std::string> words);

#endif