#include "good_book.hpp"

int book:: get_writer_id() { return writer_id;}
int book:: get_book_id() { return 	id;	}
std::string book:: get_book_title(){ return title; }
std::string book:: get_book_genres(){ return genres; }


book::book(){}

book::book(int id_b , std::string title_b , int writer_id_b, std::string genres_b)
{
  	id = id_b;
	title = title_b;
	writer_id = writer_id_b;
	genres = genres_b;
}