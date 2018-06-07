#include"getplan.h"
double min(double x,double y)
{
	return x<y?x:y;
}
bool getplan2(unordered_map<string,int> m,int flag,unordered_map<string,vmachine> &vm,server &serv,vector<unordered_map<string,int> > &res)
{
	if(flag == 0)
	{
		int maxmem = serv.mem;
		int maxcpu = serv.cpu;
		int maxvm = m.size();
		vector<string> data;
		for(auto itr = m.begin();itr != m.end();itr++)
			data.push_back(itr -> first);
		while(1)
		{
		vector<vector<vector<int> > > push(30);
		for(int i = 0;i < 30;i++)
		{
			push[i].resize(500);
			for(int j = 0;j < 500;j++)
				push[i][j].resize(300);
		}
		int j=0,k=0;
		for(int i = 1;i <= maxvm;i++)
		{
			for(j = maxmem,k = maxcpu;j > 0  && k > 0 ;j--,k--)
			{
				if(m[data[i-1]] <= 0 || j < vm[data[i - 1]].mem || k < vm[data[i - 1]].cpu )
				{
					push[i][j][k] = push[i-1][j][k];
				}
				else
				{
					push[i][j][k] = max(push[i-1][j-vm[data[i-1]].mem][k-vm[data[i-1]].cpu]+vm[data[i-1]].cpu,push[i-1][j][k]);
					
					for(int l = 2; l <= m[data[i - 1]];l++)
					{
						if((j < l * vm[data[i - 1]].mem )|| (k < l * vm[data[i - 1]].cpu))
							break;
				//		push[i][j-(l-1)*vm[data[i-1]].mem][k-(l-1)*vm[data[i-1]].cpu] = max(push[i ][j - l * vm[data[i - 1]].mem][k -l * vm[data[i - 1]].cpu] +  vm[data[i - 1]].cpu , push[i][j-(l-1)*vm[data[i-1]].mem][k-(l-1)*vm[data[i-1]].cpu]);
						push[i][j][k] = max(push[i][j -vm[data[i - 1]].mem][k -vm[data[i - 1]].cpu] +vm[data[i - 1]].cpu , push[i][j][k]);
					}
				}
			}
		}
		cout<<push[maxvm][maxmem][maxcpu]<<endl;
		int memcnt = maxmem,cpucnt = maxcpu;
		vector<int> v(maxvm,0);
		for(int i = maxvm; i >= 1;i--)
		{
			if(push[i][memcnt][cpucnt] == push[i - 1][memcnt][cpucnt])
				v[i - 1] = 0;
			else
			{
					v[i - 1] = (push[i][memcnt][cpucnt] - push[i-1 ][memcnt][cpucnt]) / vm[data[i - 1]].cpu;
					memcnt -= vm[data[i - 1]].mem * v[i - 1];
					cpucnt -= vm[data[i - 1]].cpu * v[i - 1];
			//		cout<<v[i-1]<<" ";
					//v[i - 1] ++;
			}
		}
		cout<<endl;
	//	v[0] = 2;//(int)min(memcnt / vm[data[0]].mem,cpucnt / vm[data[0]].cpu);
		unordered_map<string,int> cur;
		int f=0;
		for(int i = 0;i < v.size();i++)
		{
			if(v[i] > 0)
			{
				f = 1;
				cur[data[i]] = v[i];
				m[data[i]] -= v[i];
			}
		}
		if(f == 1)
			res.push_back(cur);
		int sum = 0;
		for(auto itr = m.begin(); itr != m.end();itr++)
			sum += itr->second;
		if(sum <= 0)
			break;
		}
	}
	else
	{
		int maxmem = serv.mem;
		int maxcpu = serv.cpu;
		int maxvm = m.size();
		vector<string> data;
		for(auto itr = m.begin();itr != m.end();itr++)
			data.push_back(itr -> first);
		while(1)
		{
		vector<vector<vector<int> > > push(30);
		for(int i = 0;i < 30;i++)
		{
			push[i].resize(500);
			for(int j = 0;j < 500;j++)
				push[i][j].resize(300);
		}

		for(int i = 1;i <= maxvm;i++)
		{
			for(int j = maxmem,k = maxcpu; m[data[i-1]] > 0 && j > 0 && k > 0 ;j--,k--)
			{
				if(j < vm[data[i - 1]].mem || k < vm[data[i - 1]].cpu)
				{
					push[i][j][k] = push[i-1][j][k];
					break;
				}
				else
				{
					for(int l = 1; l <= m[data[i - 1]];l++)
					{
						if(j < l * vm[data[i - 1]].mem || k < l * vm[data[i - 1]].cpu)
							break;
						push[i][j-(l-1)*vm[data[i-1]].mem][k-(l-1)*vm[data[i-1]].cpu] = max(push[i - 1][j - l * vm[data[i - 1]].mem][k -l * vm[data[i - 1]].cpu] + vm[data[i - 1]].mem , push[i - 1][j-(l-1)*vm[data[i-1]].mem][k-(l-1)*vm[data[i-1]].cpu]);
					}
				}
			}
		}
		int memcnt = maxmem,cpucnt = maxcpu;
		vector<int> v(maxvm,0);
		for(int i = maxvm; i >= 1;i--)
		{
			if(push[i][memcnt][cpucnt] == push[i - 1][memcnt][cpucnt])
				v[i - 1] = 0;
			else
			{
				for(int k = 1;k <= m[data[i -1]];k++)	
				{
					if(push[i][memcnt][cpucnt] == push[i - 1][memcnt][cpucnt] || memcnt < vm[data[i -1 ]].mem || cpucnt < vm[data[i - 1]].cpu )
						break;
					memcnt -= vm[data[i - 1]].mem;
					cpucnt -= vm[data[i - 1]].cpu;
					v[i - 1] ++;
				}
			}
		}
	//	v[0] = 2;//(int)min(memcnt / vm[data[0]].mem,cpucnt / vm[data[0]].cpu);
		unordered_map<string,int> cur;
		int f=0;
		for(int i = 0;i < v.size();i++)
		{
			if(v[i] > 0)
			{
				f = 1;
				cur[data[i]] = v[i];
				m[data[i]] -= v[i];
			}
		}
		if(f == 1)
			res.push_back(cur);
		int sum = 0;
		for(auto itr = m.begin(); itr != m.end();itr++)
			sum += itr->second;
		if(sum <= 0)
			break;
		}
	}
}
