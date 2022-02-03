#ifndef HOTEL_CONCUMER
#define HOTEL_CONCUMER _HOTEL_CONCUMER_

#include <string>
#include <iostream>
#include <vector>
#include <iomanip> 
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

        bool set_login();
        bool set_logout();
        bool is_login();

        void see_wallet(std::string order);
        void print_wallet(int count);
        void increase_wallet(float count);

        void print_reserve();
        void dec_wallet(int money);
        void put_reserve(std::vector <Room*> reserved);
        Room* delete_room(int id);

    private:
		std::vector <std::vector <Room*>> reserved_room;
        std::vector <int> deleted_id;
		std::vector <float> wallet;
		std::string email_address;
		std::string user_name;
		std::string password;
		bool enterred;
		int reserves;
};

#endif