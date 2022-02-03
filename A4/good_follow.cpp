 #include "good_follow.hpp"


int follow:: get_id() { return id; }
std::vector<int> follow:: get_following() { return following; }
std::vector<int> follow:: get_follower() { return follower; }

 follow::follow(int id_f, std::vector<int> following_f, std::vector<int> follower_f)
 {
	 id = id_f;
	 following = following_f;
	 follower = follower_f;
 }
