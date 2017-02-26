#include <bits/stdc++.h>
#include "GradientDescent.h"

using namespace std;
using namespace GradientDescent;

element* readfile(fstream &file, int n, int f, int mode=0)
{
	element *set;
	set = new element[n];
	for(int i=0; i<n; i++)
		set[i].features = new float[f];
	string l;
	for(int i=0; i<n; i++)
	{
		getline(file,l);
		char *token;
		token = strtok(&l[0],",");
		int j=0;

		//tokenizing
		while(token != NULL)
		{
			if(j<f)
				set[i].features[j] = atof(token);
			else
			{
				if(mode == 0)
					set[i].group = atoi(token);
			}
			j++;
			token = strtok(NULL,",");
		}
	}
	return set;
}

int main()
{
	int n, no_of_features, no_of_groups, no_of_hidden_nodes;
	cout<<"Enter the Number of Elements in Training set :";
	cin>>n;
	cout<<"Enter the Number of Features :";
	cin>>no_of_features;
	cout<<"Enter the Number of Classes :";
	cin>>no_of_groups;
	fstream file;
	file.open("AND.csv");
	element* training_set = readfile(file,n,no_of_features);
	file.close();
  GD X(no_of_features, no_of_groups, n);
	for(int count = 0; count<100000; count++)
	{
		X.implement(training_set,count);
	}
	cout<<"Enter no of Elements in Test Set :";
	int m;
	cin>>m;
	file.open("ANDT.csv");
	element* test_set = readfile(file,m,no_of_features,1);
	X.test(test_set, m);
	file.close();
}
