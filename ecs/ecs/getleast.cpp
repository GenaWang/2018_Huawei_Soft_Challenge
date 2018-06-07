#include"leastsquare.h"
/*void getleastsquare(vector<double> &y,vector<double> &yh,int length)
{
	int len = y.size();
	vector<double> x;
	for(int i = 0;i < len;i++)
		x.push_back(i + 1);
	leastsquare lsq(x,y);
	for(int i = 0;i < length;i++)
	{
		yh.push_back(lsq.getY(len + i + 1));
	}
}
*/

double getleastsquare(vector<double> &x,vector<double> &y,vector<double> &yh,time_t begintime ,time_t endtime)
{
	int len = y.size();
	//vector<double> x;
	//for(int i = 0;i < len;i++)
	//	x.push_back(i + 1);
	leastsquare lsq(x,y);
	for(time_t i = begintime;i <= endtime;i++)
	{
		double res = lsq.getY(i);
	//	if(res >= 0)
			yh.push_back(res);
	//	else
	//		yh.push_back(0);
	}
	double var = 0;
	double testy;

	for(int i = 0;i < len;i++)
	{
		testy = lsq.getY(x[i]);
		var += (y[i] - testy) * (y[i] - testy);
	}
	return var / len;
}
