#ifndef LEAST_SQUARE_H
#define LEAST_SQUARE_H
#include<vector>
#include<iostream>
using namespace std;
class leastsquare{
	public:
		leastsquare(vector<double> &x,vector<double> &y)
		{
			double t1 = 0,t2 = 0,t3 = 0,t4 = 0;
			int length = x.size();
			for(int i = 0;i < length;i++)
			{
				t1 += x[i] *  x[i];
				t2 += x[i];
				t3 += x[i] * y[i];
				t4 += y[i];
			}
			a = (t3 * length - t2 * t4) / (t1 * length - t2 * t2);
			b = (t1 * t4 - t2 * t3) / (t1 * length - t2 * t2);
		}
		double getY(double x)
		{
			return a * x + b;
		}

		void print()
		{
			cout << "y = "<< a <<"x + "<<b<<endl;
		}
	private:
		double a,b;
};
//void getleastsquare(vector<double> &y,vector<double> &yh,int length);
double getleastsquare(vector<double> &x,vector<double> &y,vector<double> &yh,time_t begintime ,time_t endtime);
#endif
