#include"get_config.h"

void getconfig(const string &file,server &s,unordered_map<string,vmachine> &vm,info &inf)
{
	string flavorname,resourcename,begindate,cbegintime,enddate,cendtime;
	int cpu,mem;
	tm duration;
	string timeform = "00:00:00"; 
	ifstream in(file);

	in >> s.cpu;
	in >> s.mem;
	in >> s.hard;
	s.mem <<= 10;
	s.hard <<= 10;
	
	in >> inf.numofvm;

	for(int i = 0;i < inf.numofvm;i++)
	{
		in >> flavorname;
		in >> cpu;
		in >> mem;
		vm[flavorname].cpu = cpu;
		vm[flavorname].mem = mem;
	}
	in >> resourcename;
	if(resourcename == "CPU")
		inf.resource = 0;
	else
		inf.resource = 1;

	in >> begindate;
	in >> cbegintime;
	in >> enddate;
	in >> cendtime;

	strptime((begindate + timeform).c_str(),"%Y-%m-%d %H:%M:%S",&duration);
	inf.begintime=mktime(&duration)/86400 + 1;

	strptime((enddate + timeform).c_str(),"%Y-%m-%d %H:%M:%S",&duration);
	inf.endtime=mktime(&duration)/86400 + 1;
}
/*
int main(int argc,char *argv[])
{
	server s;
	unordered_map<string,vmachine> vm;
	info inf;
	clock_t begin,end;
	
	begin = clock();
	getconfig(argv[1],s,vm,inf);
	end = clock();
	cout << endl;
	cout << "read configuration file spend " << double(end - begin)/CLOCKS_PER_SEC << " secs" << endl;
	cout << endl;
	
	cout << "server info : cpu " << s.cpu << " mem " << s.mem << " hard " << s.hard << endl;
	cout << endl;
	
	cout << "num of vmchine types " << vm.size() << endl;
	cout << endl;
	for(auto itr = vm.begin();itr != vm.end();itr++)
	{
		cout << "flavor name " << itr->first << " num of cpu " << itr->second.cpu << " mem " << itr->second.mem << endl;
	}
	cout << endl;

	cout << "resource " << ((inf.resource == 0) ? "CPU" : " MEM") << endl;
	cout << endl;

	time_t begintime=inf.begintime,endtime=inf.endtime;
	cout << "begintime " << ctime(&(begintime *= 86400)) << endl;
	cout << "endtime " << ctime(&(endtime *= 86400)) << endl;
	cout << "dur days " << (endtime - begintime)/86400 + 1 <<endl;
	cout << endl;
}
*/
