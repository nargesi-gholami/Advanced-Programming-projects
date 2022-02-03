#ifndef _ROOM_
#define _ROOM_ ROOM_HPP

#include <string>
#include <vector>

#define EMPTY_STRING ""
#define FIRST_STANDARD 's'
#define FIRST_LUXURY 'l'
#define FIRST_DELUXE 'd'
#define FIRST_PREMIUM 'p'

class Room 
{
    public:
        Room() {};
        Room(std::string hotel_id , std::string type_ , int quantity , int check_in_ , int check_out_ , int price_);
        ~Room();
        std::string get_hotel_id() { return hotel_id; }
        std::string get_room_id() { return room_id; }
        std::string get_type(){ return type; }

        int get_check_out(){ return check_out; }
        int get_quantity() { return quantity; }
        int get_check_in(){ return check_in; }
        int get_price() { return price; }
    protected:
        std::vector<int> cancel_room;
        std::string hotel_id;
        std::string room_id;
        std::string type;
        int quantity;
        int check_in;
        int check_out;
        int price;
};

class Standard_room : public Room
{
    public:
        Standard_room(std::string hotel_id_ ,std::string type_, int quantity_,int check_in_, int check_out_,int price_); 
};

class Delux_room : public Room
{
    public:
        Delux_room(std::string hotel_id_ ,std::string type_, int quantity_,int check_in_, int check_out_,int price_);
};

class Luxary_room : public Room
{
    public:
        Luxary_room(std::string hotel_id_ ,std::string type_, int quantity_,int check_in_, int check_out_,int price_);
};

class Premium_room : public Room
{
    public:
        Premium_room(std::string hotel_id_ ,std::string type_, int quantity_,int check_in_, int check_out_,int price_);
};

#endif