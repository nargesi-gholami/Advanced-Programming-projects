#include "good_user.hpp"

int user:: get_id(){ return id;}
std::string user:: get_name() { return name;}
std::string user:: get_member() { return member_since; }
std::string user:: get_country(){ return country; }
std::vector<int> user:: get_favoriate_writer(){ return favoriate_writer;}
std::vector <std::string> user::get_favoriate_gener(){ return favoriate_genres;}
std::vector<int> user:: get_read() { return read;}
std::vector<int> user:: get_want_to_read(){ return want_to_read;}
std::vector<int> user:: get_curr_read(){ return currently_reading;}

user::user(){}

user::user(int id_u ,std::string name_u ,std::string country_u ,std::string member_u ,std::vector<int> writer_u ,
	std::vector <std::string> favoriate_genres_u,std::vector <int> want_to_read_u,	std::vector <int> currently_reading_u,std::vector <int> read_u )
{
		id = id_u;
		name = name_u;
		country = country_u;
		member_since = member_u;
		favoriate_writer = writer_u;
		favoriate_genres = favoriate_genres_u;
		want_to_read = want_to_read_u;
		currently_reading = currently_reading_u;
		read = read_u;
}