#ifndef EVALUATE_H
#define EVALUATE_H
#include<vector>
#include<cmath>
#include<unordered_map>
#include"get_config.h"
using namespace std;
double evaluatevm(const vector<int> &x,const vector<int> &y);
double evaluate(const vector<int> &x,const vector<int> &y,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res);
#endif
