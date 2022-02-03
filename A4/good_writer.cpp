#include "good_writer.hpp"

int writer:: get_id() { return id; }
std::string writer:: get_writer_name() { return name;}
std::string writer:: get_birthday(){ return year_of_birth;}
std::string writer:: get_place() { return place_of_birth;}
std::string writer:: get_member() { return member_since;}
std::vector<std::string> writer:: get_genres(){ return genres;}

writer::writer(int id_w,std::string name_w,std::string gender_w,std::string member_w,std::string birth_w,std::string place_w,
	               std::vector<std::string> genres_w)
{
	id = id_w;
	name = name_w;
	gender = gender_w;
	member_since = member_w;
	year_of_birth = birth_w;
	place_of_birth = place_w;
	genres = genres_w;
}
