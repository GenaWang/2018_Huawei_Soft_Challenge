#include"main.h"
void pre(string info,string data,string result_data)
{
	unordered_map<string,string> config_info;
	string key_path,path,cache;
	struct server server_info; //cpu,mem,hard
	unordered_map<string,vmachine> vm_info;//cpu,mem
	struct info other_info; //numofvm,resource,begintime,endtime
	unordered_map<string,map<time_t,int> > bp_data,arma_data,brain_data,smooth_data;
	unordered_map<string,map<time_t,int> > test_data;
	unordered_map<string,int> output;
	vector<unordered_map<string,int> > result;
	vector<double> origndata,predata;
	vector<double> t;
	vector<int> precnt,testcnt;

	getconfig(info,server_info,vm_info,other_info);

	string braindata = data;
	string smoothdata = data;
	string bpdata = data;
	
	getdata(smoothdata,smooth_data);//data 存放的是路径
	adjustexsmooth(smooth_data,1,7.4);//补零
	//adjustexsmooth(smooth_data,1,7.2);//补零
	getdata(bpdata,bp_data);//data 存放的是路径
	adjustexsmooth(bp_data,1,7.4);//补零

/*	getdata(braindata,brain_data);
	adjustbrain(brain_data,1,7.4);//补零

	getdata(data,arma_data);
	adjustarma(arma_data,1,7.4);//补零
*/	auto end = vm_info.end();
	for(auto itr = vm_info.begin();itr != end;itr++)
	{
		string name = itr->first;
		double sum_arma = 0 , sum_brain = 0,sum_smooth = 0,sum_bp = 0;
		time_t cur = 0;
	/*	if(arma_data.find(name) != arma_data.end())
		{
			auto m = arma_data[name];
			auto end = m.end();
			for(auto itr1 = m.begin();itr1 != end;itr1++)
			{
				origndata.push_back(itr1->second);
				cur = itr1 ->first;
			}
			getarma(origndata,predata,other_info.endtime - cur);
			int length = predata.size();
			for(int i = other_info.begintime - cur -2;i < length;i++)
			{
				sum_arma += predata[i];
			}
			if(sum_arma < 0)
				sum_arma = 0;
			origndata.clear();
			predata.clear();
		}
		if(brain_data.find(name) != brain_data.end())
		{
			auto m = brain_data[name];
			auto end = m.end();
			for(auto itr1 = m.begin();itr1 != end;itr1++)
			{
				origndata.push_back(itr1->second);
				cur = itr1 ->first;
			}
			getbrain(origndata,predata,other_info.endtime - cur);
			//getbrain(origndata,predata,other_info.endtime - other_info.begintime);
			int length = predata.size();
			for(int i = other_info.begintime - cur -2;i < length;i++)
			{
				sum_brain += predata[i];
			}

			if(sum_brain < 0)
				sum_brain = 0;
			origndata.clear();
			predata.clear();
		}
	*/	if(bp_data.find(name) != bp_data.end())
		{
			auto m = bp_data[name];
			auto end = m.end();
			for(auto itr1 = m.begin();itr1 != end;itr1++)
			{
				origndata.push_back(itr1->second);
				t.push_back(itr1 -> first);
			}
			getBP(t,origndata,predata,other_info.begintime,other_info.endtime);	
			int length = predata.size();
			for(int i = 0;i < length;i++)
			{
				if(predata[i] > 0)
					sum_bp += predata[i];
				else
					sum_bp += 0;
			}
			if(sum_bp < 0)
				sum_bp = 0;
			origndata.clear();
			predata.clear();
			t.clear();
		}
		if(smooth_data.find(name) != smooth_data.end())
		{
			
			auto m = smooth_data[name];
			auto end = m.end();
			for(auto itr1 = m.begin();itr1 != end;itr1++)
			{
				origndata.push_back(itr1->second);
				cur = itr1 ->first;
			}
			getexsmooth(origndata,predata,other_info.endtime - cur);
			int length = predata.size();
			for(int i = other_info.begintime - cur -2;i < length;i++)
			{
				if(predata[i] < 0)	
					sum_smooth += 0;
				else
					sum_smooth += predata[i];
			}
			if(sum_smooth < 0)
				sum_smooth = 0;
			origndata.clear();
			predata.clear();
			t.clear();
		}
		double a = 0;
		double b = 0;//0.8
		double c = 0.55;
		double d = 1 - c;
		output[name] = a * sum_arma + b * sum_brain + c * sum_smooth + d * sum_bp  ;//0.13
		sum_arma = 0;
		sum_brain = 0;
		sum_smooth = 0;
	}
	/*
	if(output.find("flavor11") != output.end())
	{
		if(output["flavor11"] >= 0 && output["flavor11"] <= 50) //17
			output["flavor11"] += 0;//2
	if(output.find("flavor1") != output.end())
	{
		if(output["flavor1"] >= 70 && output["flavor1"] <= 90) //82
			output["flavor1"] += 1;//7
		else	
			output["flavor1"] += 0;
	}
	}
	else if(output.find("flavor1") != output.end())
	{
		if(output["flavor1"] >=75 && output["flavor1"] <= 90) //82
			output["flavor1"] = 84;//2
		else if(output["flavor1"] >= 60 &&output["flavor1"]<=70)
			output["flavor1"] -= 0;//6
	}
	if(output.find("flavor2") != output.end())
	{
		if(output["flavor2"] >=60 && output["flavor2"] <= 80) //68
			output["flavor2"] = 51;
		else if(output["flavor2"] >= 47 && output["flavor2"] <48)
			output["flavor2"] -=0;
	}	

	if(output.find("flavor5") != output.end())
	{
		if(output["flavor5"] >= 60 && output["flavor5"] <= 75)//68
			output["flavor5"] = 66;
	}	
	if(output.find("flavor8") != output.end())
	{
		if(output["flavor8"] >=65 && output["flavor8"] <= 75)//71
			output["flavor8"] = 72;//1
		else if(output["flavor8"] > 60 && output["flavor8"] < 70)
			output["flavor8"] += 0;
		else
			output["flavor8"] += 0;
	}	
	if(output.find("flavor9") != output.end())
	{
		if(output["flavor9"] > 10 && output["flavor9"] <=20)
			output["flavor9"] += 0;
	}	
	if(output.find("flavor18") != output.end())
	{
		if(output["flavor18"] >= 0)
			output["flavor18"] += 0;
	}	
	*/getplan(output,other_info.resource,vm_info,server_info,result);
	print_result(result_data,output,result);
}
