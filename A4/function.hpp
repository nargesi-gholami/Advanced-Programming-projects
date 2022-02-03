#ifndef FUNCTION_CPP
#define FUNCTION_CPP "FUNCTION.CPP"
#include "good_user.hpp"
#include "good_writer.hpp"
#include "good_book.hpp"
#include "good_follow.hpp"
#include "good_comment.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>


#define END 1
#define FOR_PRINT 0 
#define NORMAL 0
#define JUST_CAL 1
#define FIRST 1
#define SECOND 2
#define SEEN 1
#define SHOW_AUTHOR_INFO "show_author_info"
#define SHOW_SORTED_SHELF "show_sorted_shelf"
#define CREDIT "credit"
#define BEST_BOOK "best_book"
#define BEST_REVIEWER "best_reviewer"
#define RECOMMEND_FIRST "recommend_first_approach"
#define RECOMMEND_SECOND "recommend_second_approach"
#define COMMA ',' 
#define SEPERATOR '$' 
#define FOLLOW_CSV "/follow_edges.csv" 
#define USER_CSV "/users.csv"
#define BOOK_CSV "/books.csv"
#define REVIEW_CSV "/reviews.csv"
#define AUTHER_CSV "/authors.csv"

typedef std::vector <user> user_vec;
typedef std::vector <book> book_vec;
typedef std::vector <comment> comment_vec;
typedef std::vector <writer> writer_vec;
typedef std::vector <follow> follow_vec;

class good_reads;
std::string get_line(std::ifstream& user_file, int mode = NORMAL);
std::vector <int> getline_int(std::ifstream& user_file, int mode = NORMAL);
std::vector <std::string> getline_string(std::ifstream& user_file, int mode = NORMAL);
void get_first_line(std::ifstream& inputFile);
std::string find_address(char* address, std::string dir);
follow_vec get_follow_information(char* address);
user_vec get_user_information(char* address);
book_vec get_book_information(char* address);
comment_vec get_comment_information(char* address);
writer_vec get_writer_information(char* address);
void show_sorted_shelf(good_reads good);
float final_credit(int all_comments,int all_likes,int person_like,int person_comment,int mode = FOR_PRINT);
int find_max(std::vector<float> score_vec);
void print_recommend_comment(comment_vec review, int book_id);
std::vector<int> find_three_max(std::vector <int> book_list,std::vector<float> score_vec);
bool all_seen(std::vector <bool> seen, int end,int id);
void print_recommend_comment(comment_vec review, int book_id);
void get_order(good_reads good);


#endif
