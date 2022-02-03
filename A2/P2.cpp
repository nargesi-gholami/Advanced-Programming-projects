#include <iostream>
#include <vector>

#define ONE 1
#define ZERO 0

using namespace std;

int multiply(int index,vector<int> start,int num=ZERO)
{
	if(num==start.size())
  		 return ONE;
  	
  	else if(index==num)
		return multiply(index,start,num+ONE);

	else
		return start[num]*multiply(index,start,num+ONE);
}

void get_input(vector<int>&input)
{
	int temp;

	while(cin>>temp)
	{
	  input.push_back(temp);
	}
}

void print(vector<int>input,int current,int index)
{
	cout<<current;
	if(input.size()!=index)
		cout<<' ';
}

void calculate(vector<int>&input,int index=ZERO)
{
	if(index==input.size())
		return;

	int current=multiply(index,input);	
	print(input,current,index);
	calculate(input,index+ONE);
	input[index]=current;
}

int main()
{
	vector<int>input;
	get_input(input);
	calculate(input);
}