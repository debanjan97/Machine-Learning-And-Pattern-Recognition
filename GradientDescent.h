#include <bits/stdc++.h>
#include "MatrixMath.h"
#define eta 0.1

using namespace std;
using namespace MatrixMath;

namespace GradientDescent{
  struct element
  {
  	float *features;
  	int group;
  };

  class GD
  {
    int no_of_features, no_of_groups, no_of_hidden_nodes, n;
    matrix *u, *v, *u1, *v1, *w, *w1, *t, *feature;
    float mse;
  public:
    GD(int f, int g, int h, int n)
    {
      no_of_features = f;
      no_of_groups = g;
      no_of_hidden_nodes = h;
      this->n = n;
      w = new matrix(h,f);
      w->initialise(1);
      w1 = new matrix(g, h);
      w1->initialise(2);
      feature = new matrix(f);
      u = new matrix(h);
      v = new matrix(h);
      u1 = new matrix(g);
      v1 = new matrix(g);
      t = new matrix(g);
    }
    void implement(element *set, int iter)
    {
      if(iter == 0)
      {
        cout<<"Initial w => "<<"\n";
        w->printMatrix();
        cout<<"Initial w1 => "<<"\n";
        w1->printMatrix();
      }
      for(int i=0; i<n; i++)
      {
        mse = 0.0;
        t->initialise(0);
        for(int j=0; j<no_of_features; j++)
          feature->setValue(set[i].features[j],j);
        t->setValue(1.0,set[i].group-1);
        u->multiply(*w,*feature);
        v->sigmoid(*u);
        u1->multiply(*w1,*v);
        v1->sigmoid(*u1);
        float change;
        for(int j=0; j<no_of_groups; j++)
        {
          for(int k=0; k<no_of_hidden_nodes; k++)
          {
            float x = v1->getValue(j);
            w1->setValue((float)w1->getValue(j,k)+eta*(t->getValue(j)-x)*x*(1 - x)*v->getValue(k),j,k);
          }
        }
        for(int j=0; j<no_of_hidden_nodes; j++)
        {
            float y = v->getValue(j);
          for(int k=0; k<no_of_features; k++)
          {
            change = 0.0;
            for(int z=0; z<no_of_groups; z++)
            {
              float x = v1->getValue(z);
              change +=(t->getValue(z) - x)*x*(1 - x)*w1->getValue(z,j);
            }
            change *= y*(1 - y)*feature->getValue(k)*eta;
            w->setValue((float)w->getValue(j,k)+change,j,k);
          }
        }
        if(iter == 9999)
        {
          cout<<"v1 for training set "<<i<<"=> "<<"\n";
          v1->printMatrix();
          /*mse += v1->error();*/
        }
      }
      if(iter == 9999)
      {
        cout<<"Final w => "<<"\n";
        w->printMatrix();
        cout<<"Final w1 => "<<"\n";
        w1->printMatrix();
      }
    }
    matrix test(element *set, int m)
    {
      mse = 0.0;
      for(int i=0; i<m; i++)
      {
        t->initialise(0);
        for(int j=0; j<no_of_features; j++)
          feature->setValue(set[i].features[j],j);
        u->multiply(*w,*feature);
        v->sigmoid(*u);
        u1->multiply(*w1,*v);
        v1->sigmoid(*u1);
        cout<<"v1 for test set"<<"\n";
        v1->printMatrix();
        mse += v1->error();
      }
      cout<<"Mean Square Error(Test) => "<<mse<<"\n";
    }


  };
}
