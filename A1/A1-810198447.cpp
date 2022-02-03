#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void read_file_encrypt(vector<int>&code)
{
	string input_address;
	cin >> input_address;
	ifstream input;
	input.open(input_address.c_str());
	char temp;
	if (input.is_open())
	{
		while (!input.eof())
		{
			input >> temp;
			code.push_back((int)temp);
		}
		code.pop_back();
		input.close();
	}
}

void print_in_file_encrypt(vector<int> &code)
{
	string output_address;
	cin >> output_address;
	ofstream output;
	output.open(output_address.c_str());
	if (output.is_open())
	{
		for (int i = 0; i < code.size(); i++)
		{
			output << code[i] << endl;
		}
		output << endl;
		output.close();
	}
}

void read_file_decrypt(vector<int> &code)
{
	string input_address;
	cin >> input_address;
	ifstream input;
	int temp;
	input.open(input_address.c_str());
	if (input.is_open())
	{
		while (!input.eof())
		{
			input >> temp;
			code.push_back(temp);
		}
		code.pop_back();
		input.close();
	}
}

void print_in_file_decrypt(vector<int> &code)
{
	vector<char>current;
	for (int i = 0; i < code.size(); i++) 
	{
		current.push_back((char)code[i]);
	}
	string output_address;
	cin >> output_address;
	fstream output;
	output.open(output_address.c_str());
	if (output.is_open())
	{
		for (int i = 0; i < current.size(); i++)
		{
			output << current[i];
		}
		output << endl;
		output.close();
	}
}

void complicated_decode(vector<int>&code, const char* ramz)
{
	int ramz_size = strlen(ramz);
	int ssrand=0;
	for (int i = 0; i < ramz_size; i++)
		ssrand += int(ramz[i]);
	srand(ssrand);
	for (int i = 0; i < code.size(); i++){
		code[i] -= (rand() % 11);
	}
}

void simple_decode(vector<int> &code, const char* ramz)
{
	int ramz_size = strlen(ramz);
	for (int i = 0; i < code.size(); i++)
	{
		code[i] -= int(ramz[i % ramz_size]);
	}
}

void make_complicated_code(vector<int> &code, const char* ramz)
{
	int ramz_size = strlen(ramz);
	int ssrand=0;
	for (int i = 0; i < ramz_size; i++)
		ssrand += int(ramz[i]);
	srand(ssrand);
	for (int i = 0; i < code.size(); i++)
		code[i] += (rand() % 11);
}

void make_simple_code(vector<int> &code,const char*ramz)
{
	int ramz_size = strlen(ramz);
	for(int i=0;i < code.size(); i++)
	{
		code[i] += int(ramz[i % ramz_size]);
	}
}

void encrypt_simple()
{
	vector<int> code;
	string ramz_temp;
	cin >> ramz_temp;
	const char* ramz = ramz_temp.data();
	read_file_encrypt(code);
	make_simple_code(code,ramz);
	print_in_file_encrypt(code);
}

void encrypt_complicated()
{
	vector<int> code;
	string ramz_temp;
	cin >> ramz_temp;
	const char* ramz = ramz_temp.data();
	read_file_encrypt(code);
	make_complicated_code(code,ramz);
	print_in_file_encrypt(code);
}

void decrypt_simple()
{
	vector<int> code;
	string ramz_temp;
	cin >> ramz_temp;
	const char* ramz = ramz_temp.data();
	read_file_decrypt(code);
	simple_decode(code,ramz);
	print_in_file_decrypt(code);
}

void decrypt_complicated()
{
	vector<int> code;
	string ramz_temp;
	cin >> ramz_temp;
	const char* ramz = ramz_temp.data();
	read_file_decrypt(code);
	complicated_decode(code,ramz);
	print_in_file_decrypt(code);
}

void entrance()
{
	string FileKind;
	string type;
	cin >> FileKind;
	cin >> type;
	if (FileKind == "encrypt")
	{
		if (type == "simple")
			encrypt_simple();

		else if (type == "complicated")
			encrypt_complicated();
	}

	else if (FileKind == "decrypt")
	{
		if (type == "simple")
			decrypt_simple();

		else if (type == "complicated")
			decrypt_complicated();
	}

}

int main() 
	{
	entrance();
	}

 
