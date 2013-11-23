#include <iostream>
#include <fstream>
//#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
  string line;
  int line_no = 1;
  int case_line = 2;
  int case_no = 1;
  int t, n, l, h, i, start;
  bool inrec;
  char cur;
  bool first = false;
  bool rec = true;
  //cout<< argc << endl;

  ifstream in(argv[1]);
  ofstream out("out.txt");
  if(in.is_open())
    {
      while(getline(in, line))
	{
	  //stringstream s(line);
	  if(line_no == 1)
	    {
	      t << atoi(line.c_str());
	      line_no++;
	      continue;
	    }
	  if(line_no == case_line)
	    {
	      if(case_no != 1)
		{
		  if(h!=l)
		    rec = false;
		  if(rec)
		    out << "YES"<<endl; 
		  else
		    out << "NO"<<endl;
		}
	      rec = true;
	      first = false;
	      inrec = false;
	      n << atoi(line.c_str());
	      case_line += n+1;
	      out << "Case #"<< case_no  << ": ";
	      case_no++;
	      line_no++;
	      continue;
	    }
	  line_no++;
	  if(rec == false)
	    continue;
	  // find and handle first line, store start  and l
	  if(!first)
	    {
          for(i=0;i<n;i++)
          {
	    line.at(i) >> cur;
	    if(!first && cur == '#')
	      {
		first = true;
		start = i;
		l = 1;
		h = 1;
		inrec = true;
		continue;
	      }
	    if(first && cur == '#' && inrec)
	      l++;
	    else if(first && inrec)
	      inrec = false;
	    else if(first && cur == '#')
	      rec = false;
	  }
	    }
	  // handle other line
	  for(i=0;i<start;i++)
	    {
	      line.at(i) >> cur;
	      if(cur=='#')
		rec = false;
	      continue;
	    }
	  for(i=start;i<start+l;i++)
	    {
	      line.at(i) >> cur;
	      if(cur == '.')
		rec = false;
	      continue;
	    }
	  for(i=start+l;i<n;i++)
	    {
	      line.at(i) >> cur;
	      if(cur=='#')
		rec = false;
	      continue;
	    }
	  h++;
	  if(h > l)
	    rec = false;
	  //line_no++;
	}
      in.close();
    }
  else
    cout<< "Can't open the file"<<endl;
  return 0;
}
