#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
//#include <algorithm>
using namespace std;

int solver(int, int, char*);
void snake(int, int, int, int, int*, char*);
void reverse_snake(int, int, int, int, int*, char*);
int arr_max(int, int, int*);

int main(int argc, char* argv[])
{
  string line;
  int case_no = 0;
  int t;
  // n rows, m cols
  int n, m, i, j;
  
  ifstream in(argv[1]);
  ofstream out("out.txt");
  if(in.is_open())
    {
      while(getline(in, line))
	{
	  if(case_no==0)
	    {
	      t = atoi(line.c_str());
	      cout << t << endl;
	      case_no++;
	    }
	  else if(case_no > t)
	    break;
	  else
	    {
	      stringstream s(line);
	      s >> n;
	      s >> m;
	      char* parking_lot = new char[n*m];
	      for(i=0;i<n;i++)
		{
		  getline(in, line);
		  for(j=0;j<m;j++)
		    parking_lot[i*m + j] = line.at(j);
		}
	      //cout<<char_l<<'\t'<<n<<endl;
	      out<<"Case #"<<case_no<<": "<<solver(n, m, parking_lot)<<endl;
	      case_no++;
	    }
	}
    }
  return 0;
}

int solver(int n, int m,  char* park_lot)
{
  int sol, i, j;
  /**
   * only when the queue turn downward, we can search left 
   * only when the queue turn rightward, we can search up
   * the lenght of queue is at most n+m-1 + 2*(max(n,m)-1)
   * start search from left top corner. give every point two values
   * one denotes its distance from the start point
   * the other denotes the biggest value on its path
   */
  int* maze = new int[n*m];
  int* reverse_maze = new int[n*m];
  for(i=0;i<n;i++)
    for(j=0;j<m;j++)
      {
	maze[i*m + j] = 0;
	reverse_maze[i*m + j] = 0;
      }
  // start point
  maze[0] = 1;
  reverse_maze[(n-1)*m+ m-1] = 1;

  sol = n + m -1;

  if(n>=3 && m>=3)
    {
      snake(0, 0, n, m, maze, park_lot);
      reverse_snake(n-1, m-1, n, m, reverse_maze, park_lot);
      for(i=0;i<n;i++)
	{
	  for(j=0;j<m;j++)
	    {
	      reverse_maze[i*m+j] += maze[i*m+j];
	      //cout<<maze[i*m+j]<<' ';
	    }
	  //cout<<endl;
	}
      int* mem_left = new int[n*m];
      int* mem_up = new int[n*m];
      int max_left, max_up, mark;
      for(i=0;i<n;i++)
	{
	  for(j=0;j<m;j++)
	    {
	      mem_left[i*m+j] = 0;
	      mem_up[i*m+j] = 0;
	    }
	}
      // build mem array
      for(i=1;i<n-1;i++)
	{
	  for(j=1;j<m;j++)
	    {
	      mark = 0;
	      if(reverse_maze[i*m+j]==m+n && reverse_maze[(i-1)*m+j] == m+n)
		{
		  while(reverse_maze[i*m+j-(++mark)] == m+n)
		    {
		      //mark++;
		      if(j-mark<=0)
			break;
		    }
		  while(reverse_maze[(i+1)*m+j-mark] != m+n)
		    {
		      mark--;
		      if(mark<=0)
			break;
		    }
		  mem_left[i*m+j] = n+m-1+2*mark;
		}
	    }
	}
      for(i=1;i<n;i++)
	{
	  for(j=1;j<m-1;j++)
	    {
	      mark = 0;
	      if(reverse_maze[i*m+j-1]==m+n && reverse_maze[i*m+j] == m+n)
		{
		  while(reverse_maze[(i-(++mark))*m+j] == m+n)
		    {
		      //mark++;
		      if(i-mark<=0)
			break;
		    }
		  while(reverse_maze[(i-mark)*m+j+1] != m+n)
		    {
		      mark--;
		      if(mark<=0)
			break;
		    }
		  mem_up[i*m+j] = n+m-1+2*mark;
		}
	    }
	}
      for(i=0;i<n;i++)
	{
	  for(j=0;j<m;j++)
	    {
	      cout<<mem_left[i*m+j]<<' ';
	    }
	  cout<<endl;
	}
      max_left = arr_max(n, m, mem_left);
      max_up = arr_max(n, m, mem_up);
      //cout<<max_left<<endl;
      //cout<<max_up<<endl;
      if(max_left>sol || max_up>sol)
	{
	  if(max_left>max_up)
	    sol = max_left;
	  else
	    sol = max_up;
	}
    }
  return sol;
}

int arr_max(int n, int m, int* arr)
{
  int i, j;
  int max = 0;
  for(i=0;i<n;i++)
    {
      for(j=0;j<m;j++)
	{
	  if(arr[i*m+j]>max)
	    max = arr[i*m+j];
	}
    }
  return max;
}

void snake(int y, int x, int n, int m, int* maze, char* park)
{
  // right
  if(x+1<m)
    if(park[y*m+x+1]!='#')
      {
	maze[y*m+x+1] = maze[y*m+x] + 1;
	snake(y, x+1, n, m, maze, park);
      }
  //down
  if(y+1<n)
    if(park[(y+1)*m+x]!='#')
      {
	maze[(y+1)*m+x] = maze[y*m+x]+1;
	snake(y+1, x, n, m, maze, park);
      }
}

void reverse_snake(int y, int x, int n, int m, int* maze, char* park)
{
  // left
  if(x-1>=0)
    if(park[y*m+x-1]!='#')
      {
	maze[y*m+x-1] = maze[y*m+x] + 1;
	reverse_snake(y, x-1, n, m, maze, park);
      }
  //up
  if(y-1>=0)
    if(park[(y-1)*m+x]!='#')
      {
	maze[(y-1)*m+x] = maze[y*m+x]+1;
	reverse_snake(y-1, x, n, m, maze, park);
      }
}
