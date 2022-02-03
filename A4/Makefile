all: GoodReads.out

GoodReads.out: GoodReads.o good_read.o function.o good_writer.o good_user.o good_book.o good_comment.o good_follow.o
	g++ -std=c++11 GoodReads.o good_read.o function.o good_writer.o good_user.o good_book.o good_comment.o good_follow.o -o GoodReads.out

GoodReads.o: GoodReads.cpp function.hpp good_book.hpp good_comment.hpp good_follow.hpp good_user.hpp good_writer.hpp good_read.hpp
	g++ -std=c++11 -c GoodReads.cpp

good_read.o: good_read.cpp good_read.hpp good_book.hpp good_comment.hpp good_follow.hpp good_user.hpp good_writer.hpp function.hpp
	g++ -std=c++11 -c good_read.cpp

function.o: function.cpp function.hpp good_book.hpp good_comment.hpp good_follow.hpp good_user.hpp good_writer.hpp good_read.hpp
	g++ -std=c++11 -c function.cpp

good_writer.o: good_writer.cpp good_writer.hpp
	g++ -std=c++11 -c good_writer.cpp

good_user.o: good_user.cpp good_user.hpp
	g++ -std=c++11 -c good_user.cpp

good_book.o: good_book.cpp good_book.hpp
	g++ -std=c++11 -c good_book.cpp

good_follow.o: good_follow.cpp good_follow.hpp
	g++ -std=c++11 -c good_follow.cpp

good_comment.o: good_comment.cpp good_comment.hpp
	g++ -std=c++11 -c good_comment.cpp

clean:
	rm *.out
	rm a.out
