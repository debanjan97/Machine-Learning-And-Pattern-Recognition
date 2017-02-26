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
    int no_of_features, no_of_groups, n;
    matrix *u, *w, *v, *t, *feature;
    float mse;
  public:
    GD(int f, int g, int n)
    {
      no_of_features = f;
      no_of_groups = g;
      
      this->n = n;
      w = new matrix(g,f);
      w->initialise(1);
      feature = new matrix(f);
      u = new matrix(g);
      v = new matrix(g);
      t = new matrix(g);
    }
    void implement(element *set, int iter)
    {
      if(iter == 0)
      {
        cout<<"Initial w => "<<"\n";
        w->printMatrix();
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
        float change;
        for(int j=0; j<no_of_groups; j++)
        {
          for(int k=0; k<no_of_features; k++)
          {
            float x = v->getValue(j);
            w->setValue((float)w->getValue(j,k)+eta*(t->getValue(j)-x)*x*(1 - x)*feature->getValue(k),j,k);
          }
        }
        if(iter == 9999)
        {
          cout<<"v for training set "<<i<<"=> "<<"\n";
          v->printMatrix();
        }
      }
      if(iter == 9999)
      {
        cout<<"Final w => "<<"\n";
        w->printMatrix();
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
        cout<<"v for test set"<<"\n";
        v->printMatrix();
        mse += v->error();
      }
      cout<<"Mean Square Error(Test) => "<<mse<<"\n";
    }


  };
}
