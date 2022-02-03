#include "function.hpp"
#include "good_read.hpp"

int main(int argc , char* argv[])
{
	user_vec users = get_user_information(argv[FIRST]); 

	book_vec books = get_book_information(argv[FIRST]);

	comment_vec comments = get_comment_information(argv[FIRST]);

	writer_vec writers = get_writer_information(argv[FIRST]);

	follow_vec follows = get_follow_information(argv[FIRST]);

	good_reads good(comments , users , books , writers , follows);
	
	get_order(good);
}