#include"adjust_data.h"
#include"test.h"
void adjustarma(unordered_map<string,map<time_t,int> > &data,int flag,double limit)
{
	double mean = 0,sum = 0,min = 0,max = 0;
	auto itr0 = data.begin();
	auto itr1 = data.end();
	vector<double> origndata,predata;
	for(auto itr = itr0;itr != itr1;itr++)
	{
		auto i0 = itr->second.begin();
		auto i1 = itr->second.end();
		auto i = i0;
		auto j = i;
		j++;
		sum = 0;
		min = i0 -> second;
		for(auto k = i;k != i1;k++)
		{
			sum += k->second;
			if(k -> second > max)
				max = k->second;
			else if(k -> second < min)
				min = k -> second;	
		}
		mean = sum / itr->second.size();
		sum = 0;
		for(auto j = i0;j != i1;j++)
		{
			sum +=  (data[itr->first][j->first] - mean) * (data[itr->first][j->first] - mean);
		}
		//double var = sum / itr->second.size();
		for(auto j = i0;j != i1;j++)//数据最高限制在平均值的limit倍
		{
			if(j->second / mean >= limit)
				data[itr->first][j->first] = mean*limit + 0.5;
		}
		for(; flag && (j != i1) ;j++)
		{
			if(j->first - i->first >1)
			{
				for(time_t t = i->first + 1 ; t < j->first ; t++)
				{
					
					if(j->first - i->first < 7)//连续7天内没有值，则平滑一下
					{
						data[itr->first][t] = double((data[itr->first][t-1]+data[itr->first][t+1])/2+0.5) ; 
					}
					else if(j->first - i->first > 15)//连续超过15天以上，则前面的数据不具备参考意义，直接删除
					{
						data[itr->first][t] = 0;//min; 
					/*	for(auto k = i0;k != j;k++)
							data[itr->first].erase(k);
						i0=itr->second.begin();
						break;
					*/
					}
					else
					{
						data[itr->first][t] = 0;//min; 
					}
					
				}
			}
			i = j;
		}
	}
}

void adjustbrain(unordered_map<string,map<time_t,int> > &data,int flag,double limit)
{
	double mean = 0,sum = 0,min = 0,max = 0;
	auto itr0 = data.begin();
	auto itr1 = data.end();
	for(auto itr = itr0;itr != itr1;itr++)
	{
		auto i0 = itr->second.begin();
		auto i1 = itr->second.end();
		auto i = i0;
		auto j = i;
		j++;
		sum = 0;
		min = i0 -> second;
		for(auto k = i;k != i1;k++)
		{
			sum += k->second;
			if(k -> second < min)
				min = k -> second;	
			else if(k -> second > max)
				max = k -> second;
		}
		mean = sum / itr->second.size();
		sum = 0;
		for(auto j = i0;j != i1;j++)//数据最高限制在平均值的limit倍
		{
			if(j->second / mean >= limit)
				data[itr->first][j->first] = mean*limit + 0.5;
		}
		for(; flag && (j != i1) ;j++)
		{
			if(j->first - i->first >1)
			{
				for(time_t t = i->first + 1 ; t < j->first ; t++)
				{
					
					if(j->first - i->first <5)
					{
						data[itr->first][t] = 0; 
					}
					else if(j->first - i->first > 14)//连续超过14天以上，则前面的数据不具备参考意义，直接删除
					{
						data[itr->first][t] = 0; 
					/*	for(auto k = i0;k != j;k++)
							data[itr->first].erase(k);
						i0=itr->second.begin();
						break;
					*/	

					}
					else
					{
						data[itr->first][t] = 0; 
					}
					
				}
			}
			i = j;
		}
	}
}

void adjustexsmooth(unordered_map<string,map<time_t,int> > &data,int flag,double limit)
{
	double mean = 0,sum = 0,min = 0,max = 0;
	auto itr0 = data.begin();
	auto itr1 = data.end();
	for(auto itr = itr0;itr != itr1;itr++)
	{
		auto i0 = itr->second.begin();
		auto i1 = itr->second.end();
		auto i = i0;
		auto j = i;
		string name = itr -> first;
		j++;
		sum = 0;
		min = i0 -> second;
		for(auto k = i;k != i1;k++)
		{
			sum += k->second;
		//	if(k -> second < min)
		//		min = k -> second;	
		//	else if(k -> second > max)
		//		max = k -> second;
		}
		mean = sum / itr->second.size();
		sum = 0;
		for(auto j = i0;j != i1;j++)//数据最高限制在平均值的limit倍
		{
			if(j->second / mean >= limit)
				data[name][j->first] = mean*limit + 0.5;
		}
		//vector<double> x,y,yh;
		for(; flag && (j != i1) ;j++)
		{
/*			x.push_back(i->first);
			y.push_back(i->second);
			if(j->first - i->first >3 &&j->first-i->first<=8)
			{
				getlocalweight(x,y,yh,i->first +1,j->first-1);
				time_t end = j->first;
				int p=0;
				for(time_t t = i->first + 1 ; t < end ; t++)
				{
					//data[name][t] = 0; 
					data[name][t] = yh[p++]; 
				}
				yh.clear();
				x.clear();
				y.clear();
			}
			else
*/			{
				time_t end = j->first;
				for(time_t t = i->first + 1 ; t < end ; t++)
				{
					data[name][t] = 0; 
				}
			}
			i = j;
		}
	}
}
