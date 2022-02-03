#include "filter.hpp"


Filter::Filter(hotel_vec all_hotels_)
{
    all_hotels = all_hotels_;
}

Filter::~Filter()
{}

City_filter::City_filter(hotel_vec all_hotels_ , std::string city_)
    : Filter(all_hotels_)
{
    city = city_;
}

Star_filter::Star_filter(hotel_vec all_hotels_,int min_star_ , int max_star_)
    : Filter(all_hotels_)
{
    min_star = min_star_;
    max_star = max_star_;
}

Price_filter::Price_filter(hotel_vec all_hotels_,float min_price_ , float max_price_)
    : Filter(all_hotels_)
{
    min_price = min_price_;
    max_price = max_price_;
}

Quantity_filter::Quantity_filter(hotel_vec all_hotels_, std::string type_ , int quantity_ , int check_in_ , int check_out_)
    : Filter(all_hotels_)
{
    type = type_;
    quantity = quantity_;
    check_in = check_in_;
    check_out = check_out_;
}

hotel_vec City_filter::apply()
{
    for(int i = 0 ; i < all_hotels.size() ; i++)
        if(!city.compare(all_hotels[i]->get_city()))
            applied_hotel.push_back(all_hotels[i]);
    return applied_hotel;
}

hotel_vec Star_filter::apply()
{   
    for(int i = 0 ; i < all_hotels.size() ; i++)
        if(min_star <= all_hotels[i]->get_star() && max_star >= all_hotels[i]->get_star())
            applied_hotel.push_back(all_hotels[i]);
    return applied_hotel;
}

hotel_vec Price_filter::apply()
{
    for(int i = 0 ; i < all_hotels.size() ; i++)
        if(min_price <= all_hotels[i]->get_price() && max_price >= all_hotels[i]->get_price())
            applied_hotel.push_back(all_hotels[i]);
    return applied_hotel;
}

hotel_vec Quantity_filter::apply()
{
    for(int i = 0 ; i < all_hotels.size() ; i++)
        if(all_hotels[i]->check_enough_room(type,quantity,check_in,check_out))
            applied_hotel.push_back(all_hotels[i]);
    return applied_hotel;
}


