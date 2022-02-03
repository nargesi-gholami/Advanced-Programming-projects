#include "hotel_consumer.hpp"

Consumer::Consumer(std::string email_address_,std::string user_name_,
                    std::string password_,bool enterred_)
{
    email_address = email_address_;
    user_name = user_name_;
    password = password_;
    wallet.push_back(0);
    enterred = enterred_;
}

Consumer::~Consumer()
{

}

bool Consumer::is_login()
{
    return enterred;
}

bool Consumer::set_login()
{
    if(!enterred)
    {
        enterred = true;
        return true;
    }
    else
        return false ;
}

bool Consumer::set_logout()
{
    if(enterred)
    {
        enterred = false;
        return true;
    }
    else
        return false ;
}

void Consumer::print_wallet(int count)
{
	for (int i = 0; i < count && i < wallet.size(); i++)
		printf("%.0f\n", wallet[wallet.size() - i - 1]);
}

void Consumer::increase_wallet(float count)
{
	if (count > 0)
		wallet.push_back(wallet[wallet.size() - 1] + float(count));
    else
        throw BAD_REQUEST;
}

void Consumer::see_wallet(std::string order)
{
    if(order.find(COUNT) != std::string::npos && order.find(GET) != std::string::npos)
    {
        int index1 = order.find(COUNT) + 5;
        int index2 = order.find(SPACE , index1 + 6); 
        print_wallet(stoi(order.substr(index1,index2)));
    }
   
    else if(order.find(AMOUNT) != std::string::npos && order.find(POST) != std::string::npos)
    {
        int index1 = order.find(AMOUNT) + 6 ;
        int index2 = order.find(SPACE , index1 + 7); 
        increase_wallet(stof(order.substr(index1,index2)));
		std::cout << OK << std::endl;
    }
    else
        throw BAD_REQUEST;
}

void Consumer::put_reserve(std::vector <Room*> reserved)
{
    reserved_room.push_back(reserved);
}

bool is_assign(int id , std::vector <int> delete_number )
{
    for(int i = 0 ; i < delete_number.size() ; i++)
        if(id == delete_number[i])
            return true;
    return false;
}

void Consumer::print_reserve()
{
    int id = reserved_room.size();
    for(int i = 0 ; i < reserved_room.size(); i++)
    {
        if(is_assign(reserved_room.size() - i , deleted_id )){ id--; continue;}
        std::cout << "id: " << id << " hotel: " << reserved_room[reserved_room.size() - i -1][0]->get_hotel_id() 
        << " room: " <<  reserved_room[reserved_room.size() - i -1][0]->get_type() 
        << " quantity: " << reserved_room[reserved_room.size() - i -1][0]->get_quantity() << " cost: " <<
        reserved_room[reserved_room.size() - i -1][0]->get_quantity()*reserved_room[reserved_room.size() - i -1][0]->get_price() <<
        " check_in " << reserved_room[reserved_room.size() - i -1][0]->get_check_in() << " check_out " << 
        reserved_room[reserved_room.size() - i -1][0]->get_check_out() << std::endl;
        id --;
    }
	if(reserved_room.size() == 0 )
		std::cout << EMPTY << std::endl;
}

void Consumer::dec_wallet(int money)
{ 
    wallet.push_back(wallet[wallet.size() - 1] - money);
}

Room* Consumer::delete_room(int id)
{
    if(id <= reserved_room.size())
    {
        int sum = 0; 
		for (int j = 0 ; j < reserved_room[id - 1].size() ; j++)
			sum += reserved_room[id - 1][j]->get_price();
        wallet.push_back(wallet[wallet.size() - 1] + sum / 2);
        Room* room = reserved_room[id - 1][0]; 
        deleted_id.push_back(id);
        return room;
    }
    else 
        throw NOT_FOUND;
}