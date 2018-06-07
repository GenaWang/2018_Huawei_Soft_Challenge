#ifndef GET_CONFIG_H
#define GET_CONFIG_H

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<sstream>
#include<unordered_set>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<ctime>
#include<cstdlib>
struct server{
	int cpu;
	int mem;
	int hard;
};
struct vmachine{
	int cpu;
	int mem;
};
struct info{
	int numofvm;
	int resource;
	time_t begintime;
	time_t endtime;
};
using namespace std;
void getconfig(const string &file,server &s,unordered_map<string,vmachine> &vm,info &inf);
#endif
