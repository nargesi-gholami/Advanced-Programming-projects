#ifndef COMMENT 
#define COMMENT "COMMENT"
#include <string>
#include <vector>
class comment
{
	public:
		comment(int id_c,int book_id_c,int user_id_c,int rating_c,std::string date_c,int number_of_likes_c);
		int get_id();
		int get_user_id();
		int get_like();
		int get_book_id();
		int get_rating();
		std::string get_date();
	private:
		int id;
		int book_id;
		int user_id;
		int rating;
		std::string date;
		int number_of_likes;
};

#endif
