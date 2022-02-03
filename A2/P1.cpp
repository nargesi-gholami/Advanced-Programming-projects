#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define FIRST 0
#define TWO 2

void reverse_string(string& str,int first,int last)
{
    if(first>=last)
    {
        return;
    }
    swap(str[first],str[last]);
    reverse_string(str,first+1,last-1);
}

void encrypt(string start)
{
    if(start.length()==1)
    {
        cout<<start;
        return;
    }

    string str1;
    string str2;

    int mid=start.length()/TWO;
    str1=start.substr(FIRST,mid);
    str2=start.substr(mid,start.length());

    reverse_string(str1,FIRST,str1.length()-1);
    reverse_string(str2,FIRST,str2.length()-1);
    
    encrypt(str2);
    encrypt(str1);
}

int main()
{
    string start;
    cin>>start;
    encrypt(start);
}

