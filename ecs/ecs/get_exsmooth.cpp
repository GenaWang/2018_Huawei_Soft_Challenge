#include"exsmooth.h"
void getexsmooth(vector<double> &x,vector<double> &xh,int length)
{
/*	double sum=0;
	double mean=0;
	for(int i = 0;i<x.size();i++)
		sum+=x[i];
	mean=sum/x.size();
	for(int i = 0;i<length;i++)
		xh.push_back(mean);
*/
	vector<double> first_pinghua;
	vector<double> second_pinghua;
	int N = x.size();
	double A[N];				
	double B[N];				
	double a = 0.05;//0.05			    
	double initial = x[0];               
	first_pinghua.push_back(initial);	
	
	for(int i = 1 ; i < N ; i++)
	{
		first_pinghua.push_back(a * x[i]+(1 - a) * first_pinghua[i-1]);
	}
	
	second_pinghua.push_back(initial);	
	
	for(int i = 1 ; i < N ; i++)
	{
		second_pinghua.push_back(a * first_pinghua[i] + (1 - a) * second_pinghua[i-1]);
	}

	
	for(int i = 0 ; i < N ; i++)
	{
		A[i] = 2 * first_pinghua[i] - second_pinghua[i];
		B[i] = ( a/(1-a) ) * (first_pinghua[i] - second_pinghua[i]);
	}
	

	for(int i = 0 ; i < length ; i++)
	{
		xh.push_back(A[N-1] + B[N-1] * (i+1));
	}

}
