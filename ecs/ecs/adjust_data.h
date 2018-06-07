#ifndef ADJUST_DATA_H
#define ADJUST_DATA_H
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include"aicc.h"
#include"exsmooth.h"
#include"leastsquare.h"
using namespace std;
void adjustarma(unordered_map<string,map<time_t,int> > &data,int flag,double limit);
void adjustbrain(unordered_map<string,map<time_t,int> > &data,int flag,double limit);
void adjustleastsquare(unordered_map<string,map<time_t,int> > &data,int flag,double limit);
void adjustexsmooth(unordered_map<string,map<time_t,int> > &data,int flag,double limit);
void difference(vector<double> &data);
void toorign(vector<double> &data);
#endif
