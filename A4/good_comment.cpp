#include "good_comment.hpp"

int comment:: get_id() { return id; }
int comment:: get_user_id() { return user_id; }
int comment:: get_like(){ return number_of_likes; }
int comment:: get_book_id(){ return book_id;}
int comment:: get_rating() { return rating; }
std::string comment:: get_date() { return date; }

comment::comment(int id_c,int book_id_c,int user_id_c,int rating_c,std::string date_c,int number_of_likes_c)
{
	id = id_c;
	book_id = book_id_c;
	user_id = user_id_c;
	rating = rating_c;
	date = date_c;
	number_of_likes = number_of_likes_c;
}