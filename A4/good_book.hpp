#ifndef BOOK
#define BOOK "BOOK"

#include <string>

class book
{
	public:
	book();
    book(int id_b , std::string title_b , int writer_id_b, std::string genres_b);
   	int get_writer_id();
   	int get_book_id() ;
   	std::string get_book_title();
	std::string get_book_genres();

	private:
		int id;
		std::string title;
		int writer_id;
		std::string genres;
};

#endif