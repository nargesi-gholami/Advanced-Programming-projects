#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define ENCRYPT "encrypt"
#define DECRYPT "decrypt"
#define SIMPLE "simple"
#define COMPLICATED "complicated"
#define ENCRYPT_FILE 1
#define DECRYPT_FILE 0
#define SIMPLE_FILE 1
#define COMPLICATED_FILE 0
#define RAND 11

string get_input()
{
	string input;
	cin >> input;
	return input;
}

int which_type()
{
	string type = get_input();
	if (!type.compare(SIMPLE))
		return SIMPLE_FILE;
	else if (!type.compare(COMPLICATED))
		return COMPLICATED_FILE;
}

int calculate_seed(string pass)
{
	int seed = 0;
	for (int i = 0; i <= pass.length(); i++)
		seed += int(pass[i]);
	return seed;
}

vector <int> read_file_encrypt()
{
	vector <int> code;
	string input_address = get_input();
	ifstream input(input_address);
	string temp;
	getline(input, temp, '\0');
	for (int i = 0 ; i < temp.length() ; i++)
		code.push_back((int)temp[i]);
	return code;
}

void print_in_file_encrypt(vector<int> code)
{
	string output_address = get_input();
	ofstream output(output_address);
	for (int i = 0; i < code.size(); i++)
		output << code[i] << endl;
}

vector <int> encrypt_simple(vector <int> code, string  pass)
{
	for (int i = 0; i < code.size(); i++)
		code[i] += int(pass[i % pass.length()]);
	return code;
}

vector <int> encrypt_complicated(vector <int> code, string pass)
{
	srand(calculate_seed(pass));
	for (int i = 0; i < code.size(); i++)
		code[i] -= (rand() % RAND);
	return code;
}

vector <int> enter_order_encrypt(int type, vector <int> code, string  pass)
{
	if (type == SIMPLE_FILE)
		code = encrypt_simple(code, pass);
	else if (type == COMPLICATED_FILE)
		code = encrypt_complicated(code, pass);
	return code;
}

void encrypt(int type)
{
	string pass = get_input();
	vector <int> code = read_file_encrypt();
	code = enter_order_encrypt(type, code, pass);
	print_in_file_encrypt(code);
}
///
vector <int> read_file_decrypt()
{
	vector <int> code;
	string input_address = get_input();
	ifstream input(input_address);
	int temp;
	while (input.good())
	{
		input >> temp;
		code.push_back(temp);
	}
	return code;
}

void print_in_file_decrypt(const vector<int> code)
{
	vector <char> current;
	for (int i = 0; i < code.size(); i++)
		current.push_back((char)code[i]);
	string output_address = get_input();
	ofstream output(output_address);
	for (int i = 0; i < current.size(); i++)
		output << current[i];
}
void print_vec(vector <int> code)
{
	for (int i = 0; i < code.size(); i++)
		cout << code[i] << endl;
}
vector <int> decrypt_complicated(vector <int> code, string  pass)
{
	srand(calculate_seed(pass));
	for (int i = 0; i < code.size(); i++)
		code[i] -= (rand() % RAND);
	return code;
}

vector <int> decrypt_simple(vector <int> code, string pass)
{
	for (int i = 0; i < code.size(); i++)
		code[i] -= int(pass[i % pass.length()]);
	return code;
}

vector <int> enter_order_decrypt(int type, vector <int> code, string  pass)
{
	if (type == SIMPLE_FILE)
		code = decrypt_simple(code, pass);
	else if (type == COMPLICATED_FILE)
		code = decrypt_complicated(code, pass);
	return code;
}

void decode(int type)
{
	string pass = get_input();
	vector <int> code = read_file_decrypt();
	code = enter_order_decrypt(type, code, pass);
	print_in_file_decrypt(code);
}

int which_file_kind()
{
	string file_kind = get_input();
	if (!file_kind.compare(ENCRYPT))
		return ENCRYPT_FILE;
	else if (!file_kind.compare(DECRYPT))
		return DECRYPT_FILE;
}

void enter_orders()
{
	int file_kind_ = which_file_kind();
	int type = which_type();
	if (file_kind_ == ENCRYPT_FILE)
		encrypt(type);
	else if (file_kind_ == DECRYPT_FILE)
		decode(type);
}

int main()
{
	enter_orders();
	system("pause");
	return 0;
}


