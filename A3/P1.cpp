#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define READ 1
#define NOT_READ 0
#define DONT_HAVE 0
#define FIRST 1
#define SECOND 2
#define FOR_OUTPUT 1
#define NO_CLASS "0"

struct Schedule
{
	int start;
	int end;
	int min_start;
	int min_end;
	string day1;
	string day2;
	string day3;
};
typedef struct Schedule schedule;

struct Course {
	int id;
	string name;
	int units;
	schedule time;
	int prerequisites;
	bool read;
};

struct grades
{
	int id;
	float grade;
};

typedef struct grades lesson_s;
typedef struct Course course;
typedef vector<course> courseTable;
typedef vector<lesson_s> lesson_v;

void read_course_info(char*address, courseTable& student_course);
void read_schedule_course(ifstream& inputFile, course& current);
void read_grades(char*address, lesson_v& student_grade);
void get_first_line(ifstream& inputFile);
void find_takable_corses(vector <int>& token_course, courseTable student_course, lesson_v student_grade);
void sort_takeble_course_name(vector <int>& token_course, courseTable student_course, int mode);
void check_pass_courses(courseTable& student_course, lesson_v student_grade);
void generate_output(vector <int> final_course);
void swap_vec(vector <int>& token_course, int j);

int main(int argc, char* argv[])
{
	courseTable student_course;
	lesson_v student_grade;

	read_course_info(argv[FIRST], student_course);
	read_grades(argv[SECOND], student_grade);

	vector <int> token_course;
	find_takable_corses(token_course, student_course, student_grade);

	sort_takeble_course_name(token_course , student_course, FOR_OUTPUT);

	generate_output(token_course);

}

void read_course_info(char*address, courseTable& student_course)
{
	ifstream inputFile;
	inputFile.open(address);
	get_first_line(inputFile);

	string temp;
	while (getline(inputFile, temp, ','))
	{
		course current;
		current.id = stoi(temp);
		getline(inputFile, temp, ',');
		current.name = temp;
		getline(inputFile, temp, ',');
		current.units = stoi(temp);
		read_schedule_course(inputFile, current);
		getline(inputFile, temp, '\n');
		current.prerequisites = stoi(temp);
		current.read = NOT_READ;
		student_course.push_back(current);
	}
	inputFile.close();
}

void get_first_line(ifstream& inputFile)
{
	string temp;
	getline(inputFile, temp, '\n');
}

void read_schedule_course(ifstream& inputFile, course& current)
{
	string temp;
		getline(inputFile, temp, '-');
		current.time.day1 = temp;
		getline(inputFile, temp, ':');
		current.time.start = stoi(temp);
		getline(inputFile, temp, '-');
		current.time.min_start = stoi(temp);
		getline(inputFile, temp, ':');
		current.time.end = stoi(temp);
	if (current.units < 3)
		{
			getline(inputFile, temp, ',');
			current.time.min_end = stoi(temp);
			current.time.day2 = NO_CLASS;
			current.time.day3 = NO_CLASS;
		}
	else if (current.units == 3)
		{
			getline(inputFile, temp, '/');
			current.time.min_end = stoi(temp);
			getline(inputFile, temp, '-');
			current.time.day2 = temp;
			current.time.day3 = NO_CLASS;
			getline(inputFile, temp, ',');
		}
	else
		{
			getline(inputFile, temp, '/');
			current.time.min_end = stoi(temp);
			getline(inputFile, temp, '-');
			current.time.day2 = temp;
			getline(inputFile, temp, '/');
			getline(inputFile, temp, '-');
			current.time.day3 = temp;
			getline(inputFile, temp, ',');
		}
			
}

void read_grades(char*address, lesson_v& student_grade)
{
	ifstream inputFile;
	inputFile.open(address);
	get_first_line(inputFile);

	string temp;
	while (getline(inputFile, temp, ','))
	{
		lesson_s current;
		current.id = stoi(temp);
		getline(inputFile, temp, '\n');
		current.grade = stof(temp);
		student_grade.push_back(current);
	}
}

void find_takable_corses(vector <int>& token_course, courseTable student_course, lesson_v student_grade)
{
	check_pass_courses(student_course, student_grade);

	for (int course_number = 0; course_number < student_course.size(); course_number++)
	{
		if (student_course[course_number].read == READ)
			continue;

		else if (student_course[course_number].prerequisites == DONT_HAVE)
			token_course.push_back(student_course[course_number].id);
		

		else if (student_course[student_course[course_number].prerequisites - 1].read == READ)
				token_course.push_back(student_course[course_number].id);
	}

}

void check_pass_courses(courseTable& student_course, lesson_v student_grade)
{
	for (int course_number = 0 ; course_number < student_grade.size() ; course_number++)
		if (student_grade[course_number].grade >= 10)
			student_course[student_grade[course_number].id - 1].read = READ;
}

void sort_takeble_course_name(vector <int>& token_course, courseTable student_course, int mode)
{
		for (int i = 0 ; i < token_course.size() - 1; i++)
		{
			for (int j = 0 ; j < token_course.size() - i - 1; j++)
			{
				if (student_course[token_course[j] - 1].name > student_course[token_course[j + 1] - 1].name)
					swap_vec(token_course , j);
			}
		}
}

void generate_output(vector <int> final_course)
{
	for (int i = 0; i < final_course.size(); i++)
	{
		cout << final_course[i] << endl;
	}
}

void swap_vec(vector <int>& token_course, int j )
{
	int temp;
	temp = token_course[j];
	token_course[j] = token_course[j + 1];
	token_course[j + 1] = temp;

}