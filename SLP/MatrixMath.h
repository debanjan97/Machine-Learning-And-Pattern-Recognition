#include <bits/stdc++.h>
#define e 2.71828
using namespace std;
namespace MatrixMath{
  float wan;
  class matrix{
    int row, column;
    float **m;
    void alloc()
    {
      m = new float* [row];
      for(int i=0; i<row; i++)
        m[i] = new float [column];
    }
  public:
    matrix(int row, int column)
    {
      this->row = row;
      this->column = column;
      alloc();
    }
    matrix(int row)
    {
      this->row = row;
      this->column = 1;
      alloc();
    }
    void setValue(float val,int i, int j=0)
    {
      m[i][j] = val;
    }
    float getValue(int i, int j=0)
    {
      return m[i][j];
    }
    void initialise(int mode)
    {
      if(mode == 0)
      {
        for(int i=0; i<row; i++)
        {
          for(int j=0; j<column; j++)
            setValue(0.0,i,j);
        }
      }
      else
      {
        srand(mode);
        for(int i=0; i<row; i++)
          for(int j=0; j<column; j++)
          {
            int ran = rand()%2;
            if(ran == 0)
      				wan = -1*(rand()%100)/100.0;
      			else
      				wan = 1*(rand()%100)/100.0;
              setValue(wan,i,j);
          }
      }
    }
    int getRow()
    {
      return this->row;
    }
    int getColumn()
    {
      return this->column;
    }
    void printMatrix()
    {
      for(int i=0; i<row; i++)
      {
        for(int j=0; j<column; j++)
          cout<<this->getValue(i,j)<<"  ";
        cout<<"\n\n";
      }
    }
    void sigmoid(matrix ob)
    {
      for(int i=0; i<row; i++)
      {
        for(int j=0; j<column; j++)
          this->setValue(1.0/(1+pow(e,-1*ob.getValue(i,j))),i,j);
      }
    }
    void multiply(matrix ob1, matrix ob2)
    {
      for(int i=0; i<ob1.getRow(); i++)
      {
        for(int j=0; j<ob2.getColumn(); j++)
        {
          this->setValue(0.0,i,j);
          for(int k=0; k<ob1.getColumn(); k++)
          {
            this->setValue(this->getValue(i,j)+ob1.getValue(i,k)*ob2.getValue(k,j),i,j);
          }
        }
      }
    }
    float error()
    {
      float mse = 0.0;
      for(int i=0; i<row; i++)
      {
        float check;
        for(int j=0; j<column; j++)
        {
          if(getValue(i,j)>0.7)
            check = 1.0;
          else
            check = 0.0;
          mse += (check - getValue(i,j))*(check - getValue(i,j));
        }
      }
      return mse;
    }
  /*  matrix operator*(matrix);
    matrix operator=(matrix);*/

  };
/*  matrix matrix::operator*(matrix ob)
  {
    matrix temp(this->getRow(), ob.getColumn());
    //temp.initialise(0.0);
    for(int i=0; i<this->getRow(); i++)
    {
      for(int j=0; j<ob.getColumn(); j++)
      {
        temp.setValue(0.0,i,j);
        for(int k=0; k<this->getColumn(); k++)
          temp.setValue(temp.getValue(i,j)+this->getValue(i,k)*ob.getValue(k,j),i,j);
      }
    }
    return temp;
  }
  matrix matrix::operator=(matrix ob)
  {
    for (int i = 0; i < row; i++)
    {
      for(int j=0; j<column; j++)
        ob.setValue(this->getValue(i,j),i,j);
    }
    return *this;
  }*/
}
