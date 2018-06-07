#ifndef GET_DATA_H
#define GET_DATA_H 
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
#include<sstream>
using namespace std;
void getdata(const string &file,unordered_map<string,map<time_t,int> > &data);

#endif
