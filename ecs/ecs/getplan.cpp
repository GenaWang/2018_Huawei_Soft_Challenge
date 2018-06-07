#include"getplan.h"
bool getplan(unordered_map<string,int> &om,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res)
{
	vector<string> data;
	unordered_map<string,int> m(om.begin(),om.end());
	for(auto itr = m.begin();itr != m.end();itr++)
	{
		data.push_back(itr->first);  
	}
	sort(data.begin(),data.end(),[&](string p,string q){
		if(flag == 0)//cpu
		{
			double a = 1,b = 1 - a;
			double cpuweight = a / serv.cpu,memweight = b /serv.mem;
			if(vm[p].cpu * cpuweight + vm[p] .mem * memweight > vm[q].cpu * cpuweight + vm[q].mem * memweight)
			{	
				cout<<vm[p].mem *memweight<<endl;
				return true;
			}
			//else if(vm[p].cpu == vm[q].cpu && vm[p].mem < vm[q].mem)
			//	return true;
			else
				return false;
	
		}
		else
		{
			
			double b = 0,a = 1 - b;
			double cpuweight = a / serv.cpu,memweight = b /serv.mem;
			if(vm[p].cpu * cpuweight + vm[p] .mem * memweight > vm[q].cpu * cpuweight + vm[q].mem * memweight)
				return true;
		//	else if(vm[p].mem == vm[q].mem && vm[p].cpu <vm[q].cpu)
		//		return true;
			else
				return false;
		}

	});
	for(unsigned int i = 0;i < data.size();i++)
	{
		if(m.find(data[i]) != m.end())
		{
			unordered_map<string,int> cur;
			cur[data[i]] = 1;
			res.push_back(cur);
			m[data[i]] = m[data[i]] - 1;
			break;
		}
	}
	for(unsigned int i = 0;i < data.size();i++)
	{
		string name = data[i];
		while(m[name] > 0)
		{
			int rescnt,j;
			j = 0;
			rescnt = res.size();
			for(;j < rescnt;j++)
			{
				int sumofcpu = 0,sumofmem = 0,vmcnt;
				auto p = res[j].begin(),end = res[j].end();
				for(; p != end;p++)
				{
					vmcnt = p->second;
					sumofcpu += vmcnt * vm[p->first].cpu;
					sumofmem += vmcnt * vm[p->first].mem;
				}
				if((sumofcpu + vm[name].cpu <= serv.cpu) && (sumofmem + vm[name].mem <= serv.mem))
				{
					res[j][name]++;
					break;
				}
			}
			if(j == rescnt)//没有合适的位置，需要加到最后面
			{
				unordered_map<string,int> last;
				last[name] = 1;
				res.push_back(last);
			}
			m[name]--;
		}
	}
	auto last_m = res[res.size() - 1];
	int sumofcpu = 0,sumofmem = 0,vmcnt = 0,restcpu,restmem;
	auto end = last_m.end();
	for(auto itr = last_m.begin();itr != end;itr++)
	{
		vmcnt = itr->second;
		sumofcpu += vmcnt * vm[itr->first].cpu;
		sumofmem += vmcnt * vm[itr->first].mem;
	}
	restcpu = serv.cpu - sumofcpu;
	restmem = serv.mem - sumofmem;
	int min;
	for(int i = 0;i < data.size(); i++)
	{
		if(restcpu <=0 || restmem <= 0)
			break;
	if(flag == 0)
	{
		min = restcpu / vm[data[i]].cpu;
		if(min > restmem / vm[data[i]].mem)
			min = restmem / vm[data[i]].mem;
	}
	else
	{
	/*	min = restmem / vm[data[i]].mem;
		if(min > restcpu / vm[data[i]].cpu)
			min = restcpu / vm[data[i]].cpu;
	*/	min = restcpu / vm[data[i]].cpu;
		if(min > restmem / vm[data[i]].mem)
			min = restmem / vm[data[i]].mem;
	}
	if(min > 0)
	{
		om[data[i]] += min;
		res[res.size() - 1][data[i]] += min;
		restcpu -= min * vm[data[i]].cpu;
		restmem -= min * vm[data[i]].mem;
	}

	}
	return true;
}
