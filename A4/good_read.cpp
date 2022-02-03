#include "good_read.hpp"
#include <algorithm>


comment_vec good_reads::get_comment(){ return Comment;};
user_vec good_reads::get_user() { return User;}
book_vec good_reads::get_book(){ return Book;};
follow_vec good_reads::get_follow() { return Follow;}
	
comment* good_reads::find_comment_by_id(int id)
{
	for (int i = 0; i < Comment.size(); i++)
		if (Comment[i].get_user_id() == id)
			return &Comment[i];
}

book* good_reads::find_book_by_id(int id)
{
	for (int i = 0; i < Book.size(); i++)
		if (Book[i].get_book_id() == id)
			return &Book[i];
}

follow* good_reads::find_follow_by_id(int id)
{
	for (int i = 0; i < Follow.size(); i++)
		if (Follow[i].get_id() == id)
			return &Follow[i];
}
writer* good_reads::find_author_by_id(int id)
{
	for (int i = 0; i < Writer.size(); i++)
		if (Writer[i].get_id() == id)
			return &Writer[i];
}
void good_reads::search_book(int author_id)
{
	for (int i = 0; i < Book.size(); i++)
		if (Book[i].get_writer_id() == author_id)
			cout << "id: " << Book[i].get_book_id() << " Title: " << Book[i].get_book_title() << endl;
}
user* good_reads::find_user_by_id(int id)
{
	for (int i = 0; i < User.size(); i++)
		if (User[i].get_id() == id)
			return &User[i];
}

good_reads::good_reads(comment_vec comments,user_vec users , book_vec books, writer_vec writers, follow_vec follows)
{
		Comment = comments;
		User = users;
		Book = books;
		Writer = writers;
		Follow = follows;
}

void good_reads::show_author_info()
{
	int id;
	cin >> id;
	writer* author = find_author_by_id(id);
	cout << "id: " << id << endl;
	cout << "Name: " << author->get_writer_name() << endl;
	cout << "Year of Birth: "<< author->get_birthday() << endl;
	cout << "Place of Birth: "<< author->get_place() << endl;
	cout << "Member Since: "<< author->get_member() << endl;
	cout << "Genres: ";
	vector <string> temp = author->get_genres();
	sort(temp.begin(),temp.end());
	for (int i = 0; i < temp.size(); i++)
	{
		if(i == temp.size() - 1 )
			cout << temp[i] << endl;
		else
			cout << temp[i] << ", ";
	}
	cout << "Books:" << endl;
	search_book(author->get_id());
}

vector <int> good_reads::sort_book_by_gener(vector<int> sort_book, string gener)
{
	int i = 0;
	for (int j = 0; j < sort_book.size(); j++)
	{
		book* book1 = find_book_by_id(sort_book[j]);
		if (!book1->get_book_genres().compare(gener))
		{
			swap(sort_book[j], sort_book[i]);
			i++;
		}
	}
	return sort_book;
}

vector <int> good_reads::sort_book_by_title(vector<int> sort_book, string gener)
{
	for (int j = 0 ; j < sort_book.size() - 1 ; j++)
	{
		for (int i = 0; i <sort_book.size() - j - 1; i++)
		{
			book* book1 = find_book_by_id(sort_book[i]);
			book* book2 = find_book_by_id(sort_book[i + 1]);
			if ((!book1->get_book_genres().compare(gener)) && (book2->get_book_genres().compare(gener)))
				continue;

			if ((!book1->get_book_genres().compare(gener)) && (!book2->get_book_genres().compare(gener)))
			{
				if (book1->get_book_title() > book2->get_book_title())
					swap(sort_book[i], sort_book[i + 1]);
			}
			else
				if((book1->get_book_title()) > (book2->get_book_title()))
					swap(sort_book[i], sort_book[i + 1]);
			
			if (!book1->get_book_title().compare(book2->get_book_title()))
				if(book1->get_book_id() > book2->get_book_id())
					swap(sort_book[i], sort_book[i + 1]);
		}
	}
	return sort_book;
}

vector <int> good_reads::sort_book_first(vector<int> sort_book , string gener)
{
	sort_book = sort_book_by_gener(sort_book,gener);
	sort_book = sort_book_by_title(sort_book,gener);
	return sort_book;
}

void good_reads::print_book(vector <int> final)
{
	for(int i = 0 ; i < final.size() ; i++)
	{
		book* book1 = find_book_by_id(final[i]);
		cout << "id: " << book1-> get_book_id() << endl;
		cout << "Title: "<< book1-> get_book_title() << endl;
		cout << "Genre: "<< book1-> get_book_genres() << endl;
		writer* author = find_author_by_id(book1-> get_writer_id());
		cout << "Author: "<< author-> get_writer_name() << endl;
		cout << "***" << endl;
	}
}

void good_reads::show_book(int user_id, string gener, string mode)
{
	user* reader = find_user_by_id(user_id);
	vector <int> sort_book;
	if(!mode.compare(READ))
		sort_book = reader->get_read();
			
	else if(!mode.compare(WANT_TO_READ))
		sort_book = reader->get_want_to_read();
					
	else if(!mode.compare(CURR_READ))
		sort_book = reader->get_curr_read();

	sort_book = sort_book_first(sort_book,gener);
	print_book(sort_book);
}

float good_reads::calculate_credit(int id, int mode)
{
	comment_vec review = get_comment();

	int all_comments = review.size();

	int all_likes = 0;
	for(int i = 0 ; i < review.size() ; i++)
		all_likes += review[i].get_like();

	int person_like = 0 ;
	int person_comment = 0;
	for(int i = 0 ; i < review.size() ; i++)
		if(review[i].get_user_id() == id)
		{
			person_like += review[i].get_like();
			person_comment++;
		}
	long double credit;
	if(mode == JUST_CAL)
		credit = final_credit(all_comments, all_likes, person_like, person_comment,JUST_CAL);
	else
		credit = final_credit(all_comments, all_likes, person_like,person_comment);
	
	return credit;
}

void good_reads::show_best_book(float average,book temp_book)
{
	writer* author = find_author_by_id(temp_book.get_writer_id());
	cout << "id: " << temp_book.get_book_id() << endl;
	cout << "Title: " << temp_book.get_book_title() << endl;
	cout << "Genre: " << temp_book.get_book_genres() << endl;
	cout << "Author: " << author->get_writer_name() << endl;
	cout << "Average Rating: ";
	printf("%.2f\n" , average);
}

float good_reads::cal_average(comment_vec review , int book_id)
{
	int sum = 0;
	int comment_num = 0;
	float average;
	for (int i = 0; i < review.size(); i++)
		if (review[i].get_book_id() == book_id)
		{
			sum += review[i].get_rating();
			comment_num++;
		}
	average = float(sum) / float(comment_num);
	return average;
}

void good_reads::find_best_book()
{
	comment_vec review = get_comment();
	book_vec ketab = get_book();
	book temp_book;
	float max = 0 ;
	float average;
	for(int j = 0 ; j < ketab.size() ; j++)
	{
		int book_id = ketab[j].get_book_id();
		average = cal_average(review , book_id);
		if(average > max)
			{
				max = average;
				temp_book = ketab[j];
			}
	}
	show_best_book(max,temp_book);
}

void good_reads::print_best_reviwer(user temp_user , string type,vector<string> for_print)
{
	cout << type ;
	for (int i = 0; i < for_print.size(); i++)
	{
		if (i == for_print.size() - 1)
			cout << for_print[i] << endl;
		else
			cout << for_print[i] << ", ";
	}
}

void good_reads::show_best_reviwer(int num , user temp_user)
{
	cout << "id: "<< temp_user.get_id() << endl;
	cout << "Name: " << temp_user.get_name() << endl;
	cout << "Place of Birth: " << temp_user.get_country() << endl;
	cout << "Member Since: " << temp_user.get_member() << endl;

	vector <string> favoriate_gener = temp_user.get_favoriate_gener();
	print_best_reviwer(temp_user, "Favorite Genres: ", favoriate_gener);

	vector <int> current = temp_user.get_favoriate_writer();
	sort(current.begin(), current.end());
	vector <string> auther_temp;
	for(int k = 0 ; k < current.size() ; k++)
	{
		writer* author = find_author_by_id(current[k]);
		auther_temp.push_back(author->get_writer_name());
	}
	print_best_reviwer(temp_user, "Favorite Authors: ", auther_temp);
	cout << "Number of Books in Read Shelf: " << temp_user.get_read().size() << endl;
	cout << "Number of Books in Want to Read Shelf: " << temp_user.get_want_to_read().size() << endl;
	cout << "Number of Books in Currently Reading Shelf: " << temp_user.get_curr_read().size() << endl;
	cout << "Number of Likes: " << num << endl;
}

int good_reads::sum_review(comment_vec review,int user_id)
{
	int sum = 0;
	for (int i = 0; i < review.size(); i++)
		if (review[i].get_user_id() == user_id)
			sum += review[i].get_like();
	return sum;
}

void good_reads::find_best_reviewer()
{
	comment_vec review = get_comment();
	user_vec karbar = get_user();
	user temp_user;
	int max = 0;
	for (int j = 0; j < karbar.size(); j++)
	{
		int user_id = karbar[j].get_id();
		int sum = sum_review(review,user_id);
		
		if (sum > max)
		{
			max = sum;
			temp_user = karbar[j];
		}
	}
	show_best_reviwer(max, temp_user);
}

bool good_reads::is_favorite(book ketab, vector<string> fav_genres)
{
	for (int i = 0; i < fav_genres.size(); i++)
		if (!fav_genres[i].compare(ketab.get_book_genres()))
			return true;
	return false;
}

void good_reads::print_recommend(int finall)
{
	comment_vec review = get_comment();
	book* ketab = find_book_by_id(finall);
	writer* author = find_author_by_id(ketab->get_writer_id());
	cout << "id: " << finall << endl;
	cout << "Title: " << ketab->get_book_title() << endl;
	cout << "Genre: " << ketab->get_book_genres() << endl;
	cout << "Author: " << author->get_writer_name() << endl;
	cout << "Reviews:" << endl;
	int book_id = ketab->get_book_id();
	print_recommend_comment(review, book_id);
}

float good_reads::cal_rating(comment_vec review , int book_id , vector<float> user_credit)
{
	float temp_rating = 0;
	int number_of_comment = 0;
	for (int j = 0; j < review.size(); j++)
	{
		if (review[j].get_book_id() == book_id )
		{
			temp_rating += (review[j].get_rating() * user_credit[review[j].get_user_id()]);
			number_of_comment++;
		}
	}
	temp_rating /= float(number_of_comment);
	return temp_rating;
}

vector <float> good_reads::find_recommend(vector<float> user_credit,int id)
{
	comment_vec review = get_comment();
	book_vec ketab = get_book();
	vector <float> score_vec;
	int book_id;
	for(int book_id = 0 ; book_id < ketab.size() ; book_id++)
	{
		book_id = ketab[book_id].get_book_id();
		score_vec.push_back(cal_rating(review,book_id,user_credit));
	}
	return score_vec;
}

vector<float> good_reads::calculate_all_credit()
{
	vector<float> user_credit;
	user_vec karbar = get_user();
	for (int i = 0; i < karbar.size(); i++)
	{
		float credit = calculate_credit(karbar[i].get_id(), JUST_CAL);
		user_credit.push_back(credit);
	}
	return user_credit;
}

void good_reads::first()
{
	int id; cin >> id;
	vector<float> user_credit = calculate_all_credit();
	vector<float> score_vec = find_recommend(user_credit, id);
	book_vec ketab = get_book();
	user* curr_user = find_user_by_id(id);
	vector<string> fav_genres = curr_user->get_favoriate_gener();
	for (int i = 0; i < score_vec.size(); i++)
		{
			if (is_favorite(ketab[i], fav_genres))
				score_vec[i] += 5;
		}
	int	final = find_max(score_vec);
	print_recommend(final);
}

vector<int> good_reads::recommend_second(vector<float> score_vec,vector<float>user_credit, int id, vector <bool>& seen,vector <int>& main_best, int end)
{
	follow* follow_temp = find_follow_by_id(id);
	vector<int> followingg = follow_temp->get_following();
	
	
	
	if (!followingg.empty())
		if((!all_seen(seen, end,id)))
			if(seen[id] != SEEN)
			{
				seen[id] = SEEN;
				user* temp_user = find_user_by_id(id);
				vector <int> book_list = temp_user->get_read();
				vector<int> temp = find_three_max(book_list,score_vec);
				main_best.push_back(temp[0]);
				if (book_list.size() >= 2)
					main_best.push_back(temp[1]);
				if (book_list.size() >= 3)
					main_best.push_back(temp[2]);

				for (int i = 0; i < followingg.size(); i++)
					recommend_second(score_vec, user_credit, followingg[i], seen, main_best,end);
			}
	
	return main_best;
}

int good_reads::find_max_second(vector<int> main_best)
{ 
	sort(main_best.begin(),main_best.end());
	int max_count = 0;
	int res = main_best[0] ;
	int curr_count = 0 ;
	for (int i = 1; i < main_best.size(); i++)
	{
		if (main_best[i] == main_best[i - 1])
			curr_count++;
		else {
			if (curr_count > max_count) 
				{
					max_count = curr_count;
					res = main_best[i - 1];
				}
				curr_count = 0;
			}
	}
	if (curr_count > max_count)
		{
			max_count = curr_count;
			res = main_best[main_best.size() - 1];
			
		}
	return res;
}

void good_reads::second()
{
	int id; cin >> id;
	vector <float> user_credit = calculate_all_credit();
	vector<float> score_vec = find_recommend(user_credit, id);
	vector <bool> seen(get_user().size());
	seen[id]= SEEN;
	vector <int> main_best;
	int end = get_user().size();
	follow* user_f = find_follow_by_id(id);
	vector <int> temp_follow = user_f->get_following();
	
	for (int i = 0; i < temp_follow.size(); i++)
		recommend_second(score_vec,user_credit, temp_follow[i], seen, main_best , end);

	int book_id = find_max_second(main_best);
	print_recommend(book_id);
}


