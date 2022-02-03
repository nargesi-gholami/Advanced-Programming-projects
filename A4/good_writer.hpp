#ifndef WRITER
#define WRITER "WRITER"

#include <string>
#include <vector>

class writer 
{
	public:
		writer();
		writer(int id_w,std::string name_w,std::string gender_w,std::string member_w,std::string birth_w,std::string place_w,std::vector<std::string> genres_w);
		int get_id();
		std::string get_writer_name();
		std::string get_birthday();
		std::string get_place();
		std::string get_member() ;
		std::vector<std::string> get_genres();
	private:
		int id;
		std::string name ;
		std::string gender;
		std::string member_since;
		std::string year_of_birth;
		std::string place_of_birth;
		std::vector<std::string> genres;
};

#endif