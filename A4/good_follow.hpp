#ifndef FOLLOW
#define FOLLOW "FOLLOW"

#include <vector> 

class follow
 {
	public:
		follow(int id_f, std::vector <int> following_f , std::vector <int> follower_f);
		int get_id();
		std::vector <int> get_following();
		std::vector <int> get_follower();
	private:
		int id;
		std::vector <int> following;
		std::vector <int> follower;
 };
 #endif