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
#define FOR_OUTPUT 0
#define SELECTION_NAME 1
#define SELECTION_UNIT 2
#define NO_CLASS "0"
#define EMPTY "0"

struct Schedule
{
	int start;
	int end;
	int min_start;
	int min_end;
	int start_exception;
	int end_exception;
	string day_exception;
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
void read_schedule(ifstream& inputFile, course& current);
void read_schedule_one(ifstream& inputFile, course& current);
void read_schedule_two(ifstream& inputFile, course& current);
void read_schedule_three(ifstream& inputFile, course& current);
void read_grades(char*address, lesson_v& student_grade);
void get_first_line(ifstream& inputFile);
void put_information(courseTable& student_course, ifstream& inputFile, string temp);
void put_grades(lesson_v& student_grade, ifstream&  inputFile, string temp);
void find_takable_corses(vector <int>& token_course, courseTable student_course, lesson_v student_grade);
void check_pass_courses(courseTable& student_course, lesson_v student_grade);
void calculate_gpa(float& GPA, lesson_v student_grade);
void number_of_takable_corses(float GPA, int& valid_course);
bool check(courseTable student_course, int course_number, vector <int> token_course);
bool check_time(courseTable student_course, int course_number, int i, string time1);
bool checkClassTime(courseTable student_course, int course_number, int i, string time1, string time2);
bool check_all_time(courseTable student_course, int course_number, int i);
void take_valid_course(courseTable student_course, int valid_course, vector <int>  token_course, vector < int >& final_course);
void sort_takeble_course(vector <int>& token_course, courseTable student_course, int mode);
void generate_output(vector <int> final_course);
void swap_vec(vector <int>& token_course, int j);


int main(int argc, char* argv[])
{
	courseTable student_course;
	lesson_v student_grade;

	read_course_info(argv[1], student_course);
	read_grades(argv[2], student_grade);

	vector <int> token_course;
	find_takable_corses(token_course, student_course, student_grade);

	sort_takeble_course(token_course, student_course, SELECTION_UNIT);
	sort_takeble_course(token_course, student_course, SELECTION_NAME);

	float GPA = 0;
	calculate_gpa(GPA, student_grade);

	int valid_course;
	number_of_takable_corses(GPA, valid_course);

	vector < int > final_course;
	take_valid_course(student_course, valid_course, token_course, final_course);
	sort_takeble_course(final_course, student_course, FOR_OUTPUT);

	generate_output(final_course);
}

void read_course_info(char*address, courseTable& student_course)
{
	ifstream inputFile;
	inputFile.open(address);

	get_first_line(inputFile);

	string temp;
	while (getline(inputFile, temp, ','))
	{
		put_information(student_course, inputFile, temp);
	}

	inputFile.close();
}

void get_first_line(ifstream& inputFile)
{
	string temp;
	getline(inputFile, temp, '\n');
}

void put_information(courseTable& student_course, ifstream& inputFile, string temp)
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

void read_schedule_course(ifstream& inputFile, course& current)
{
	read_schedule(inputFile, current);

	if (current.units < 3)
		read_schedule_one(inputFile, current);

	else if (current.units == 3)
		read_schedule_two(inputFile, current);

	else
		read_schedule_three(inputFile, current);
}

void read_schedule(ifstream& inputFile, course& current)
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
}

void read_schedule_one(ifstream& inputFile, course& current)
{
	string temp;
	getline(inputFile, temp, ',');
	current.time.min_end = stoi(temp);

	current.time.day2 = NO_CLASS;
	current.time.day3 = NO_CLASS;
	current.time.start_exception = DONT_HAVE;
}

void read_schedule_two(ifstream& inputFile, course& current)
{
	current.time.day_exception = EMPTY;
	string temp;
	getline(inputFile, temp, '/');
	current.time.min_end = stoi(temp);

	getline(inputFile, temp, '-');
	current.time.day2 = temp;
	current.time.day3 = NO_CLASS;

	getline(inputFile, temp, ':');
	int start = stoi(temp);
	if (start != current.time.start)
	{
		current.time.start_exception = start;
		current.time.day_exception = current.time.day2;
	}

	getline(inputFile, temp, '-');
	getline(inputFile, temp, ':');
	int end = stoi(temp);
	if (end != current.time.end)
	{
		current.time.end_exception = end;
		current.time.day_exception = current.time.day3;
	}

	if (current.time.day_exception != current.time.day2)
	{
		current.time.day_exception = EMPTY;
		current.time.start_exception = DONT_HAVE;
		current.time.end_exception = DONT_HAVE;
	}
	getline(inputFile, temp, ',');
}

void read_schedule_three(ifstream& inputFile, course& current)
{
	current.time.day_exception = EMPTY;
	string temp;
	getline(inputFile, temp, '/');
	current.time.min_end = stoi(temp);

	getline(inputFile, temp, '-');
	current.time.day2 = temp;

	getline(inputFile, temp, ':');
	int start = stoi(temp);
	if (start != current.time.start)
	{
		current.time.start_exception = start;
		current.time.day_exception = current.time.day2;
	}

	getline(inputFile, temp, '-');
	getline(inputFile, temp, ':');
	int end = stoi(temp);
	if (end != current.time.end)
	{
		current.time.end_exception = end;
		current.time.day_exception = current.time.day3;
	}

	getline(inputFile, temp, '/');
	getline(inputFile, temp, '-');
	current.time.day3 = temp;

	getline(inputFile, temp, ':');
	start = stoi(temp);
	if (start != current.time.start)
	{
		current.time.start_exception = start;
		current.time.day_exception = current.time.day2;
	}
	getline(inputFile, temp, '-');
	getline(inputFile, temp, ':');
	end = stoi(temp);
	if (end != current.time.end)
	{
		current.time.end_exception = end;
		current.time.day_exception = current.time.day3;
	}
	if (current.time.day_exception != current.time.day3 && current.time.day_exception != current.time.day2)
	{
		current.time.day_exception = EMPTY;
		current.time.start_exception = DONT_HAVE;
		current.time.end_exception = DONT_HAVE;
	}
	getline(inputFile, temp, ',');
}

void read_grades(char*address, lesson_v& student_grade)
{
	ifstream inputFile;
	inputFile.open(address);

	get_first_line(inputFile);

	string temp;
	while (getline(inputFile, temp, ','))
	{
		put_grades(student_grade, inputFile, temp);
	}
}

void put_grades(lesson_v& student_grade, ifstream&  inputFile, string temp)
{
	lesson_s current;
	current.id = stoi(temp);
	getline(inputFile, temp, '\n');
	current.grade = stof(temp);
	student_grade.push_back(current);
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
	for (int course_number = 0; course_number < student_grade.size(); course_number++)
		if (student_grade[course_number].grade >= 10)
			student_course[student_grade[course_number].id - 1].read = READ;
}

bool check(courseTable student_course, int course_number, vector <int> final_course)
{
	if (final_course.empty())
		return true;

	for (int i = 0; i < final_course.size(); i++)
		if (check_all_time(student_course, course_number, final_course[i]))
			return false;

	return true;
}

bool check_all_time(courseTable student_course, int course_number, int final)
{
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day1, (student_course[final - 1].time.day1)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day1, (student_course[final - 1].time.day2)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day1, (student_course[final - 1].time.day3)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day2, (student_course[final - 1].time.day1)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day2, (student_course[final - 1].time.day2)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day2, (student_course[final - 1].time.day3)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day3, (student_course[final - 1].time.day1)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day3, (student_course[final - 1].time.day2)))
		return true;
	if (checkClassTime(student_course, course_number - 1, final - 1, student_course[course_number - 1].time.day3, (student_course[final - 1].time.day3)))
		return true;



	return false;
}

bool check_time(courseTable student_course, int course_number, int i, string time1)
{
	 if(student_course[course_number].time.start_exception != DONT_HAVE)
	     if(time1.compare(student_course[course_number].time.day_exception))
	         if (student_course[course_number].time.start_exception  < student_course[i].time.start || student_course[course_number].time.start_exception  >= student_course[i].time.end)
	             if (student_course[course_number].time.end_exception  <= student_course[i].time.start || student_course[course_number].time.end_exception > student_course[i].time.end)
	                 if (!student_course[course_number].time.start_exception  < student_course[i].time.start && student_course[course_number].time.end_exception > student_course[i].time.end)
                     return false;

	if (student_course[course_number].time.start < student_course[i].time.start || student_course[course_number].time.start >= student_course[i].time.end)
		if (student_course[course_number].time.end <= student_course[i].time.start || student_course[course_number].time.end > student_course[i].time.end)
			if ((student_course[course_number].time.start > student_course[i].time.start && student_course[course_number].time.end > student_course[i].time.end)
			|| (student_course[course_number].time.start < student_course[i].time.start && student_course[course_number].time.end < student_course[i].time.end))
				return false;


	return true;
}

bool checkClassTime(courseTable student_course, int course_number, int final, string time1, string time2)
{
	if (!time1.compare(time2))
		if (time1 != NO_CLASS)
			if (check_time(student_course, course_number, final, time1))
				return true;

	return false;
}

void calculate_gpa(float& GPA, lesson_v student_grade)
{
	for (int i = 0; i < student_grade.size(); i++)
		GPA += student_grade[i].grade;

	GPA = GPA / student_grade.size();
}

void number_of_takable_corses(float GPA, int& valid_course)
{
	if (GPA >= 17)
		valid_course = 24;
	if (GPA < 17)
		valid_course = 20;
}

void take_valid_course(courseTable student_course, int valid_course, vector <int>  token_course, vector <int>& final_course)
{
	int take_unit = 0;
	for (int course_number = 0; (course_number < token_course.size()); course_number++)
	{
		if (check(student_course, token_course[course_number], final_course))
		{
			take_unit += student_course[token_course[course_number] - 1].units;

			if ((take_unit <= valid_course))
				final_course.push_back(token_course[course_number]);
		}
	}
}

void sort_takeble_course(vector <int>& token_course, courseTable student_course, int mode)
{
	for (int i = 0; i < token_course.size() - 1; i++)
	{
		for (int j = 0; j < token_course.size() - i - 1; j++)
		{
			if (mode == SELECTION_NAME)
			{
				if (student_course[token_course[j] - 1].units == student_course[token_course[j + 1] - 1].units)
					if (student_course[token_course[j] - 1].name > student_course[token_course[j + 1] - 1].name)
						swap_vec(token_course, j);
			}

			else if (mode == SELECTION_UNIT)
			{
				if (student_course[token_course[j] - 1].units < student_course[token_course[j + 1] - 1].units)
					swap_vec(token_course, j);
			}

			else if (mode == FOR_OUTPUT)
			{
				if (student_course[token_course[j] - 1].name > student_course[token_course[j + 1] - 1].name)
					swap_vec(token_course, j);
			}
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

void swap_vec(vector <int>& token_course, int j)
{
	int temp;
	temp = token_course[j];
	token_course[j] = token_course[j + 1];
	token_course[j + 1] = temp;
}