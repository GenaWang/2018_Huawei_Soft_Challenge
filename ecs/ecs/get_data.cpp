#include"get_data.h"

void getdata(const string &file,unordered_map<string,map<time_t,int> > &data)
{
	string id,flavorname,cdate,ctime,curtime = "00:00:00";
	time_t createtime;
	ifstream in(file);
	tm duration;
	while(1)
	{
		in >> id >> flavorname >> cdate >> ctime;
		if(in.fail() == true)
		{
			break;
		}

		strptime((cdate + curtime).c_str(),"%Y-%m-%d %H:%M:%S",&duration);
		createtime = mktime(&duration)/86400;
		data[flavorname][createtime]++;
	}
}
/*
int main(int argc,char *argv[])
{
	unordered_map<string,map<time_t,int> > data;
	clock_t begin,end;

	begin = clock();
	getdata(argv[1],data);
	end = clock();
	cout << "read data spend " << float(end-begin)/CLOCKS_PER_SEC << " secs"<<endl;
	cout << endl;

	cout << "summary :" << endl;
	cout << endl;
	
	cout << "name	" << "createtime	" << "num" <<endl;
	for(auto itr = data.begin();itr != data.end();itr++)
	{
		for(auto i = itr -> second.begin();i != itr->second.end();i++)
		{
			cout << itr->first <<  "  " << i->first << "  " << i->second << endl;
		}
		
	}
	
}
*/
