#ifndef FILTER
#define FILTER _FILTER_

#include <vector>
#include "hotel.hpp"

typedef std::vector < Hotel* > hotel_vec;

class Filter
{
    public:
        Filter(hotel_vec all_hotels_);
        ~Filter();
        virtual hotel_vec apply() = 0;

    protected:
        hotel_vec all_hotels;
        hotel_vec applied_hotel;
};

class City_filter : public Filter
{
    public:
        City_filter(hotel_vec all_hotels_,std::string city_);
        hotel_vec apply();
    private:
        std::string city;
}; 

class Star_filter : public Filter
{
    public:
        Star_filter(hotel_vec all_hotels_,int min_star_, int max_star_);
        hotel_vec apply();
    private:
        int min_star;
        int max_star;
};

class Price_filter : public Filter
{
    public:
        Price_filter(hotel_vec all_hotels_, float min_price_, float max_price_);
        hotel_vec apply();
    private:
		float min_price;
		float max_price;
};

class Quantity_filter : public Filter
{
    public:
        Quantity_filter(hotel_vec all_hotels_, std::string type_ , int quantity_ , int check_in_ , int check_out_);
        hotel_vec apply();
    private:
        std::string type;
        int quantity;
        int check_in;
        int check_out;
};


#endif