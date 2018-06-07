#ifndef PRINT_H
#define PRINT_H

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"get_config.h"
using namespace std;
void print_config(server &server_info,unordered_map<string,vmachine> &vm_info,info &other_info);

void print_result(const string &file,const unordered_map<string,int> &vm,const vector<unordered_map<string,int> > &server);

void print_data(string &file,unordered_map<string,map<time_t,int> > &data);

#endif
