#ifndef GOOD_READ
#define GOOD_READ "GOOD_READ"

#include "good_book.hpp" 
#include "good_comment.hpp"
#include "good_follow.hpp"
#include "good_user.hpp"
#include "good_writer.hpp"
#include "function.hpp"
#include <string>
#include <vector>

#define FOR_PRINT 0 
#define NORMAL 0
#define READ "read" 
#define WANT_TO_READ "want_to_read" 
#define CURR_READ "currently_reading" 

using namespace std;

typedef vector <user> user_vec;
typedef vector <book> book_vec;
typedef vector <comment> comment_vec;
typedef vector <writer> writer_vec;
typedef vector <follow> follow_vec;

class good_reads
{
	public:
		good_reads(comment_vec comments, user_vec users, book_vec books, writer_vec writers,follow_vec follows);
		void show_author_info();

		void show_book(int user_id, string gener,string mode);
		void print_book(vector <int> final);

		void find_best_book();
		void show_best_book(float average,book temp_book);
		vector <int> sort_book_by_gener(vector<int> temp, string gener);
		vector <int> sort_book_by_title(vector<int> temp, string gener);

		float cal_average(comment_vec review, int book_id);
		void find_best_reviewer();
		void show_best_reviwer(int num , user temp_user);
		void print_best_reviwer(user temp_user, string type, vector<string> for_print);
		int sum_review(comment_vec review, int user_id);

		float calculate_credit(int id, int mode = FOR_PRINT);
		vector<float> calculate_all_credit();

		float cal_rating(comment_vec review, int book_id, vector<float> user_credit);

		void second();
		void first();
		vector <int> sort_book_first(vector<int> temp , string gener);
		vector <float> find_recommend(vector<float> user_credit, int id);
		void print_recommend(int final);
		bool is_favorite(book ketab,vector<string> fav_genres);
		int find_max_second(vector<int> main_best);
		vector<int> recommend_second(vector<float> score_vec,vector<float>user_credit,int id, vector <bool>& seen, vector <int>& main_best, int end);

		comment_vec get_comment();
		user_vec get_user();
		book_vec get_book();
		follow_vec get_follow();

	private:
		follow*  find_follow_by_id(int id);
		writer* find_author_by_id(int id);
		void search_book(int author_id);
		user* find_user_by_id(int id);
		book* find_book_by_id(int id);
		comment* find_comment_by_id(int id);
		follow_vec Follow;
		comment_vec Comment;
		user_vec User;
		book_vec Book;
		writer_vec Writer;
};

#endif