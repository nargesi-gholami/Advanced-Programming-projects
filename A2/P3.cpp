#include <iostream>
#include <vector>

using namespace std;

#define ZERO 0
#define SEEN 1
#define EMPTY 0

void init_board(vector<vector<int>>& board,int m,int n)
{
    int current;
    for(int i=0;i<m;i++)
    {
        vector<int>temp;
        for(int j=0;j<n;j++)
        {
            cin>>current;
            temp.push_back(current);
        }
        board.push_back(temp);
    }
}

void init_visit(vector<vector<int>>& vec,int m,int n)
{
    for(int i=0;i<m;i++)
    {
        vector<int>temp;
        for(int j=0;j<n;j++)
        {
            temp.push_back(ZERO);
        }
        vec.push_back(temp);
    }
}

bool isVisit(vector<vector<int>> visited,int i,int j)
{
    if(visited[i][j]==SEEN)
        return false;
    else
        return true;
}

bool isEmpty(vector<vector<int>> board,int i,int j)
{
    if(board[i][j]==EMPTY)
        return false;
    else
        return true;
}

bool isPermit(vector<vector<int>> board,int i,int j)
{
     if((i >= 0) && (i < board.size()) && (j < board[i].size()) && (j >= 0))
        return true;
    else 
        return false;
}

int find_max(vector<int> max_sum)
{
    int max=0;
    for(int i=0;i<max_sum.size();i++)
    {
           if(max_sum[i]>max)
             max=max_sum[i];
    }
    return max;
}

void print_answer(int max)
{
    cout<<max;
}

bool check(vector<vector<int>> board, vector<vector<int>>& visited, int i, int j)
{
  if (isPermit(board, i, j))
  {
      if (isEmpty(board, i, j) && isVisit(visited, i, j))
          return true;
  }
     return false;
}

void find_trove(int max_trove,vector<int>& max,vector<vector<int>>& visited,vector<vector<int>> board,int i,int j)
{
    visited[i][j]=SEEN;
    max_trove+=board[i][j];

    if(check(board,visited,i+1,j))
        find_trove(max_trove,max,visited,board,i+1,j);
    
    if(check(board,visited,i,j+1))
        find_trove(max_trove,max,visited,board,i,j+1);

    if(check(board,visited,i-1,j))
        find_trove(max_trove,max,visited,board,i-1,j);

    if(check(board,visited,i,j-1))
        find_trove(max_trove,max,visited,board,i,j-1);
  
        max.push_back(max_trove);
        visited[i][j]=ZERO;
}

void solve(vector<vector<int>> board,vector<vector<int>> visited,vector<int>& max)
{
    for(int i=0;i<board.size();i++)
    {
       for(int j=0;j<board[i].size();j++)
        {
           int max_trove=0;
           if(isEmpty(board,i,j))
           find_trove(max_trove,max,visited,board,i,j);
        }
    }
}

int main()
{
    int m,n;
    cin>>m>>n;

    vector<vector<int>> board;
    init_board(board,m,n);

    vector<vector<int>> visited;
    init_visit(visited,m,n);

    vector<int> max;

    solve(board,visited,max);

    int max_trove;
    max_trove=find_max(max);
    print_answer(max_trove);
}