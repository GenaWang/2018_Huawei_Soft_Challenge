#include"print.h"

void print_config(server &server_info,unordered_map<string,vmachine> &vm_info,info &other_info)
{
//print server info (cpu ,mem(MB) ,hard)
	cout << "server info : cpu " << server_info.cpu << " mem " << server_info.mem << " hard " << server_info.hard << endl;
	cout << endl;
//print vm num(name,cpu,mem)
	cout << "num of vmchine types " << vm_info.size() << endl;
	cout << endl;
	for(auto itr = vm_info.begin();itr != vm_info.end();itr++)
	{
		cout << "flavor name " << itr->first << " num of cpu " << itr->second.cpu << " mem " << itr->second.mem << endl;
	}
	cout << endl;
//print resource type
	cout << "resource " << ((other_info.resource == 0) ? "CPU" : " MEM") << endl;
	cout << endl;
//print time
	time_t begintime = other_info.begintime , endtime = other_info.endtime;
	cout << "begintime " << ctime(&(begintime *= 86400)) << endl;
	cout << "endtime " << ctime(&(endtime *= 86400)) << endl;
	cout << "dur days " << (endtime - begintime)/86400 + 1 <<endl;
	cout << endl;
	
}

void print_data(string &file,unordered_map<string,map<time_t,int> > &data)
{
	
	ofstream out(file);
	for(auto itr = data.begin();itr != data.end();itr++)
	{
		for(auto i = itr -> second.begin();i != itr->second.end();i++)
		{
			out << itr->first <<  "  " << i->first << "  " << i->second << endl;
		}
		
	}
}

void print_result(const string &file,const unordered_map<string,int> &vm,const vector<unordered_map<string,int> > &server)
{
	ofstream out(file);
	int sum = 0;
	auto itr = vm.begin(), end = vm.end();
	for(;itr != end;itr++)
	{
		sum += itr->second;
	}
	out << sum <<" "<<endl;
	for(auto itr = vm.begin();itr != vm.end();itr++)
	{
		out << itr->first << " " << itr->second << endl;
	}
	out << endl;

	out << server.size() <<endl;
	
	for(unsigned int i = 0;i < server.size();i++)
	{
		out << i+1 << " ";
		for(auto itr = server[i].begin();itr != server[i].end();itr++)
		{
			out << itr->first << " "<< itr->second << " ";
		}
		out << endl;
	}
}

