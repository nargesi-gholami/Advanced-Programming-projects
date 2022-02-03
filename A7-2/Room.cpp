#include "Room.hpp"

Room::Room(std::string hotel_id_,std::string type_,int quantity_,int check_in_,int check_out_,int price_)
{
    room_id = EMPTY_STRING;
    hotel_id = hotel_id_;
    type = type_;
    quantity = quantity_;
    check_in = check_in_;
    check_out = check_out_;
    price = price_;
}

Room::~Room()
{}

Standard_room::Standard_room(std::string hotel_id_,std::string type_,int quantity_,int check_in_,int check_out_,int price_)
    : Room(hotel_id_,type_,quantity_,check_in_,check_out_,price_)
    {
        
    }

Delux_room::Delux_room(std::string hotel_id_,std::string type_,int quantity_,int check_in_,int check_out_,int price_)
    : Room(hotel_id_,type_,quantity_,check_in_,check_out_,price_)
    {
        
    }

Luxary_room::Luxary_room(std::string hotel_id_,std::string type_,int quantity_,int check_in_,int check_out_,int price_)
    : Room(hotel_id_,type_,quantity_,check_in_,check_out_,price_)
    {
     
    }

Premium_room::Premium_room(std::string hotel_id_,std::string type_,int quantity_,int check_in_,int check_out_,int price_)
    : Room(hotel_id_,type_,quantity_,check_in_,check_out_,price_)
    {

    }
