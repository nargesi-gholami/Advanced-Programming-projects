#include "function.hpp"
#include "good_read.hpp"



std::string get_line(std::ifstream& user_file ,int mode)
{
	std::string temp;
	if(mode == NORMAL)
		getline(user_file,temp,COMMA);
	else if(mode == END)
		getline(user_file,temp,'\n');
	return temp;
}

std::vector <int> getline_int(std::ifstream& user_file, int mode )
{
	std::vector<int> int_vec;
	std::string temp ;

	if(mode == NORMAL)
		getline(user_file,temp,COMMA);
	else if(mode == END)
		getline(user_file,temp,'\n');

	while(true)
		{
			int found = temp.find(SEPERATOR);
			if(found != std::string::npos)
				{
					int curr= stoi(temp.substr(0 , found));
					int_vec.push_back(curr);
					temp = temp.substr(found + 1);
				}
			else
				{
				if(temp != "")
					int_vec.push_back(stoi(temp));
					break; 
				}
		}
	return int_vec;
}

std::vector <std::string> getline_string(std::ifstream& user_file, int mode) 
{
	std::vector<std::string> string_vec;
	std::string temp;

	if(mode == NORMAL)
		getline(user_file,temp,COMMA);
	else if(mode == END)
		getline(user_file,temp,'\n');

	while(true)
		{
			int found = temp.find(SEPERATOR);
			if(found != std::string::npos)
				{
					std::string curr = temp.substr(0,found);
					string_vec.push_back(curr);
					temp = temp.substr(found + 1);
				}
			else
				{
					string_vec.push_back(temp);
					break; 
				}
		}
	return string_vec;
}

void get_first_line(std::ifstream& inputFile)
{
	std::string temp;
	getline(inputFile, temp, '\n');
}

std::string find_address(char* address, std::string dir)
{
	std::string add = "./";
	add +=  address;
	add += dir;
	return add;
}

follow_vec get_follow_information(char* address)
{
	std::string add = find_address(address,FOLLOW_CSV);
	ifstream user_file(add);
	follow_vec follows;
	std::string temp;

	get_first_line(user_file);

	for (int i = 0; getline(user_file, temp,COMMA); i++)
	{
		int id_f = stoi(temp);
		std::vector<int> following_f = getline_int(user_file);
		std::vector<int> follower_f = getline_int(user_file, END);
		follows.push_back(follow(id_f, following_f,follower_f ));
	}
	return follows;
}

user_vec get_user_information(char* address)
{
	std::string add = find_address(address,USER_CSV);
	ifstream user_file(add);

	user_vec users;
	std::string temp;

	get_first_line(user_file);

	for(int i = 0 ; getline(user_file,temp,COMMA) ; i++)
		{
			int id_u = stoi(temp);
			std::string name_u = get_line(user_file);
			std::string country_u = get_line(user_file);
			std::string member_since_u = get_line(user_file);
			std::vector <int> favoriate_writer_u = getline_int(user_file);
			std::vector <std::string> favoriate_genres_u = getline_string(user_file);
			std::vector <int> want_to_read_u = getline_int(user_file);
			std::vector <int> currently_reading_u = getline_int(user_file);
			std::vector <int> read_u = getline_int(user_file , END);
			users.push_back(user(id_u,name_u ,country_u, member_since_u, favoriate_writer_u, 
				                favoriate_genres_u, want_to_read_u, currently_reading_u, read_u));
		}
	return users;
}

book_vec get_book_information(char* address)
{
	std::string add = find_address(address,BOOK_CSV);
	ifstream user_file(add);

	book_vec books;
	std::string temp;

	get_first_line(user_file);
	for(int i = 0 ; getline(user_file,temp,COMMA) ; i++)
	{
		int id_b = stoi(temp);
		std::string title_b  = get_line(user_file);
		int writer_id_b = stoi(get_line(user_file));
		std::string genres_b = get_line(user_file,END);
		books.push_back(book(id_b , title_b , writer_id_b , genres_b));
	}

	return books;
}

comment_vec get_comment_information(char* address)
{
	std::string add = find_address(address,REVIEW_CSV);
	ifstream user_file(add);

	comment_vec comments;
	std::string temp;

	get_first_line(user_file);
	for(int i = 0 ; getline(user_file,temp,COMMA) ; i++)
		{
			int id_c = stoi(temp);
			int book_id_c = stoi(get_line(user_file));
			int user_id_c = stoi(get_line(user_file));
			int rating_c  = stoi(get_line(user_file));
			std::string date_c = get_line(user_file); 
			int number_of_likes_c = stoi(get_line(user_file,END));
			comments.push_back(comment(id_c,book_id_c,user_id_c,rating_c,date_c,number_of_likes_c));
		}
	return comments;
}

writer_vec get_writer_information(char* address)
{
	std::string add = find_address(address,AUTHER_CSV);
	ifstream user_file(add);

	writer_vec writers;
	std::string temp;

	get_first_line(user_file);
	for(int i = 0 ; getline(user_file,temp,COMMA) ; i++)
		{
			int id_w = stoi(temp);
			std::string name_w = get_line(user_file); 
			std::string gender_w = get_line(user_file); 
			std::string member_w = get_line(user_file); 
			std::string birth_w = get_line(user_file); 
			std::string place_w = get_line(user_file); 
			std::vector<std::string> genres_w = getline_string(user_file,END); 
			writers.push_back(writer(id_w,name_w,gender_w,member_w,birth_w,place_w,genres_w));
		}
	return writers;
}

void show_sorted_shelf(good_reads good)
{
	int user_id;
	std::cin >> user_id;
	
	std::string shelf_type;
	std::cin >> shelf_type;

	std::string gener;
	std::getline(std::cin,gener);
	gener = gener.substr( 1 , gener.size());

	good.show_book(user_id,gener,shelf_type);
}

float final_credit(int all_comments,int all_likes,int person_like,int person_comment,int mode )
{
	float part1;
	if((all_likes == 0))
		part1 = 0;
	else
		part1 = (float(person_like) / float(all_likes));

	float part2;
	if((all_comments==0))
		part2 = 0;
	else
		part2 = (float(person_comment) / float(all_comments));

	float credit = 0.5*(part1 + part2);
	if (mode == FOR_PRINT)
		printf("%.6lf\n", credit);
	
	return credit;
}

int find_max(vector<float> score_vec)
{
	float max = 0;
	int max_id;
	for (int i = 0; i < score_vec.size(); i++)
	{
		if ((score_vec[i]) > max)
		{
			max = score_vec[i];
			max_id = i;
		}
	}
	return max_id;
}

void print_recommend_comment(comment_vec review, int book_id)
{
	for (int j = 0; j < review.size(); j++)
	{
		if (review[j].get_book_id() == book_id)
		{
			cout << "id: " << review[j].get_id() << " Rating: " << review[j].get_rating() <<
				" Likes: " << review[j].get_like() << " Date: " << review[j].get_date() << endl;
		}
	}
}

bool all_seen(vector <bool> seen, int end,int id)
{
	if(seen[id] == SEEN)
		return false;
	for (int i = 0; i < end; i++)
		if (seen[i] != SEEN)
			return false;
	return true;
}

vector<int> find_three_max(vector <int> book_list,vector<float> score_vec)
{
	std::vector<int> three_max(3);
	std::vector<float> max(3);

	for (int i = 0 ; i < book_list.size() ; i++)
		if ((score_vec[book_list[i]]) > max[0])
			{
				max[0] = score_vec[book_list[i]];
				three_max[0] = book_list[i];
			}

		if(book_list.size() >= 2)
	for (int i = 0 ; i < book_list.size() ; i++)
		if (((score_vec[book_list[i]]) < max[0]) && ((score_vec[book_list[i]]) > max[1]))
			{
				max[1] = score_vec[book_list[i]];
				three_max[1] = book_list[i];
			}
	

	if (book_list.size() >= 3)
	for (int i = 0 ; i < book_list.size() ; i++)
		 if (((score_vec[book_list[i]]) < max[0]) && ((score_vec[book_list[i]]) < max[1]) && ((score_vec[book_list[i]]) > max[2]))
			{
				max[2] = score_vec[book_list[i]];
				three_max[2] = book_list[i];
			}
	
	return three_max;
}

void get_order(good_reads good)
{
	std::string order;
	while( std::cin >> order)
	{
		if (!order.compare(SHOW_AUTHOR_INFO))
			good.show_author_info();

		else if (!order.compare(SHOW_SORTED_SHELF))
			show_sorted_shelf(good);

		else if (!order.compare(CREDIT))
		{
			int id;
			std::cin >> id;
			good.calculate_credit(id);
		}
		else if (!order.compare(BEST_BOOK))
			good.find_best_book();

		else if (!order.compare(BEST_REVIEWER))
			good.find_best_reviewer();

		else if (!order.compare(RECOMMEND_FIRST))
			good.first();

		else if (!order.compare(RECOMMEND_SECOND))
			good.second();
	}
}
