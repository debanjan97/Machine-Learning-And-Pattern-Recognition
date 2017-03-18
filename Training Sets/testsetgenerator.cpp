#include <iostream>
#include <fstream>
#include<cstdlib>
#include <time.h>

using namespace std;

int main()
{
  int count[5]={0}, flag=0;
  fstream file;
  float i, j;
  time_t seconds;
  srand((int)time(0));
  file.open("test.csv",ios::out|ios::ate);
  while(flag < 5)
  {
    int r = rand()%2+1;
    int s = rand()%2+3;
    if(r*s == 3)
    {
      i = rand()%40000/100.0;
      j = rand()%40000/100.0;
    }
    if(r*s == 4)
    {
      i = -1*rand()%40000/100.0;
      j = rand()%40000/100.0;
    }
    if(r*s == 6)
    {
      i = rand()%40000/100.0;
      j = -1*rand()%40000/100.0;
    }
    if(r*s == 8)
    {
      i = -1*rand()%40000/100.0;
      j = -1*rand()%40000/100.0;
    }
    if(i*j > 1)
    {
      if(i>0 && j>0)
      {
        if(count[0] < 20)
        {
          count[0]++;
          file<<i<<","<<j<<"\n";
	        //cout<<i<<","<<j<<","<<"1"<<"\n";
          if(count[0] == 20)
            flag++;
        }
      }
      else
      {
        if(count[2] < 20)
        {
          count[2]++;
          file<<i<<","<<j<<"\n";
          //cout<<i<<","<<j<<","<<"3"<<"\n";
          if(count[2] == 20)
            flag++;
        }
      }
    }
    else if(i*j < -1)
    {
      if(i < 0)
      {
        if(count[1] < 20)
        {
          count[1]++;
          file<<i<<","<<j<<"\n";
          //cout<<i<<","<<j<<","<<"2"<<"\n";
          if(count[1] == 20)
            flag++;
        }
      }
      else
      {
        if(count[3] < 20)
        {
          count[3]++;
          file<<i<<","<<j<<"\n";
          //cout<<i<<","<<j<<","<<"4"<<"\n";
          if(count[3] == 20)
            flag++;
        }
      }
    }
    else
    {
      if(count[4] < 20)
      {
        count[4]++;
        file<<i<<","<<j<<"\n";
        //cout<<i<<","<<j<<","<<"5"<<"\n";
        if(count[4] == 20)
          flag++;
      }
    }
  }
}
