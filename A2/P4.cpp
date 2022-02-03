#include<iostream>
#include<string>
#include<functional>

using namespace std;

#define ZERO 0
#define ONE 1
#define FOUND 1

unsigned long int generatePasswordHash(string password)
{
	return hash<string>()(password);
}

bool check(string str,unsigned long int pass)
{
	if(pass==generatePasswordHash(str))
	{
		return true;
	}
	else 
		return false;
}

void decrypt(string start,int data_num,int index,int valid,string str,unsigned long int pass,int& check_found)
{
	if (index == valid)
		{
        if (check(str, pass))
            {
 				cout << str;
				check_found = FOUND;
 			}
		else
			return;
 		}
	 else
 		{
			for (int j = data_num ; j < start.length(); j++)
			{
				str += start[j];
				decrypt(start, j, index + 1, valid, str, pass, check_found);
				str.erase(str.end()-1);
			}
		}
}

void primary_decrypt(string start, int valid, string str, unsigned long int pass,int& check_found)

{
   for (int i = 0; i < start.length(); i++)
    {
      str = start[i];
      decrypt(start, ZERO, ONE, valid, str, pass, check_found);
    }

}

int main() 
{
	int valid;
	cin>>valid;

	string start;
	cin>>start;
	
	unsigned long int pass;
	cin>>pass;

	string str;
	int check_found = 0;
    primary_decrypt(start, valid, str, pass, check_found);
     
     if(check_found == ZERO)
		 cout << "NOT_FOUND";
	return 0;
}