#include"evaluate.h"
double evaluatevm(const vector<int> &x,const vector<int> &y)
{
	if(x.size() != y.size())
		return 0;
	double sumgap = 0,sumx = 0,sumy = 0;
	int n = x.size();
	for(int i = 0;i < n;i++)
	{
		sumgap += (x[i] - y[i]) * (x[i] - y[i]);
		sumx += x[i] * x[i];
		sumy += y[i] * y[i];
	}	
	return 1-sqrt(sumgap / n)/(sqrt(sumx / n) + sqrt(sumy / n));
}
double evaluate(const vector<int> &x,const vector<int> &y,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res)
{
	double val = evaluatevm(x,y);//获得预测比例
	cout<<val<<endl;
	int servcnt = res.size();
	int servercpu = 0,servermem = 0;
	int cpu = 0,mem = 0;
	if(flag == 0)
	{
		servercpu = servcnt * serv.cpu; //cpu总数
		for(unsigned int i = 0;i < res.size();i++)
		{
			int sumofcpu = 0,sumofmem = 0;
			auto itr = res[i].begin(),end = res[i].end();
			for(;itr != end;itr++)
			{
				sumofcpu += vm[itr->first].cpu * itr->second; //资源数=个数*每个cpu的资源	
				sumofmem += vm[itr->first].mem * itr->second;
			}
			if(sumofcpu > serv.cpu || sumofmem > serv.mem)
				return 0;
			cpu += sumofcpu;
		}
		cout<<"cpu "<<cpu<<"  sum "<<servercpu<<endl;
		return double(cpu) / double(servercpu) * val;
	}
	else
	{
		servermem = servcnt * serv.mem; //mem总数
		for(unsigned int i = 0;i < res.size();i++)
		{
			int sumofcpu = 0,sumofmem = 0;
			auto itr = res[i].begin(),end = res[i].end();
			for(;itr != end;itr++)
			{
				sumofcpu += vm[itr->first].cpu * itr->second; //资源数=个数*每个mem的资源	
				sumofmem += vm[itr->first].mem * itr->second;
			}
			if(sumofcpu > serv.cpu || sumofmem > serv.mem)
				return 0;
			mem += sumofmem;
		}
		return double(mem) / double(servermem) * val;
	}
}
