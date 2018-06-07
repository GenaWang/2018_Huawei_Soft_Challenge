#ifndef GET_PLAN_H
#define GET_PLAN_H
#include"get_config.h"
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std;
bool getplan(unordered_map<string,int> &m,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res);

bool getplan2(unordered_map<string,int> m,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res);
#endif
