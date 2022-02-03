#ifndef USER
#define USER "USER"

#include <string>
#include <vector>

class user
{
	public:
		user();
		user (int id_u ,std::string name_u ,std::string country_u ,	std::string member_u , std::vector <int> writer_u ,
		std::vector <std::string> favoriate_genres_u,std::vector <int> want_to_read_u,std::vector <int> currently_reading_u,std::vector <int> read_u );
		int get_id();
		std::string get_name();
		std::string get_member() ;
		std::string get_country();
		std::vector <int> get_favoriate_writer();
		std::vector <std::string> get_favoriate_gener();
		std::vector <int> get_read() ;
		std::vector <int> get_want_to_read();
		std::vector <int> get_curr_read();

	private:
		int id;
		std::string name;
		std::string country;
		std::string member_since;
		std::vector <int> favoriate_writer;
		std::vector <std::string> favoriate_genres;
		std::vector <int> want_to_read;
		std::vector <int> currently_reading;
		std::vector <int> read;
		float credit;
};

#endif