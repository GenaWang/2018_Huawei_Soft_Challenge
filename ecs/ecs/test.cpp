#include<iostream>    
#include<cmath>
#include<cstdio>
#include<vector>
using namespace std;    
    
int Number;    
const float learningRate=1;//0.000005;         
const float errorThr=1; //variance threshold    
const int MAX=10;     //Max times of iteration    
int k = 0.01;
    
    
//lwr(局部线性回归)    
double weightValue(double xi,double x){    
    float weight = 0.0;    
     weight=pow(xi-x,2);    
    float tempWeight = exp(-(weight/(2*k*k)));    
    if(tempWeight<0.2)    
        tempWeight = 0.0;    
    return tempWeight;    
}    
    
double multiPly(double x1,double x2){    
    double temp = 0.0;    
        temp += x1*x2;    
    return temp;    
}    
    
double addVectorData(double x1,double x2){    
    double temp;    
        temp = x1+x2;    
    return temp;    
}    
    
double minusVectorData(double x1,double x2){    
    double temp;    
        temp = x1-x2;    
    return temp;    
}    
    
double numberMultiVectorData(double para,double x1){    
    double temp;    
        temp = x1*para;    
    return temp;    
}    
double costFunction(vector<double> &parameter,vector<double> &inputData,vector<double> &inputResultData,double object){    
    double costValue = 0.0;    
    double tempValue = 0.0;    
    double weightedValue = 0.0;    
    for(int i=0;i<Number;i++){    
        tempValue = 0.0;    
            
        //consider all the parameters although most of them is zero    
        for(int j=0;j<Number;j++)    
            tempValue += multiPly(parameter[j],inputData[i]);    
        costValue += weightValue(inputData[i],object)*pow((inputResultData[i]-tempValue),2);        
    }    
    
    return (costValue/2*4);    
}    
    
    
double LocallyWeightedAgression(vector<double> &parameter, vector<double> &inputData,vector<double> &resultData, int objectVector){    
    float tempValue = 0.0;    
    float errorCost = 0.0;    
    float weightedValue = 0.0;    
    errorCost=costFunction(parameter,inputData,resultData,objectVector);    
    if(errorCost<errorThr)    
        return 1;    
    for(int iteration=0;iteration<MAX;iteration++){    
    
        //stochastic    
        for(int i=0;i<Number;i++){    
            //calculate the h(x)    
            weightedValue = weightValue(inputData[i],objectVector);    
            tempValue=0.0;    
            for(int j=0;j<Number;j++)    
                tempValue+=multiPly(parameter[j],inputData[i]);    
            //update the parameter by stochastic(随机梯度下降)    
           // printf("the next parameter is ");    
            for(int ii=0;ii<Number;ii++){    
                parameter[ii]=addVectorData(parameter[ii],numberMultiVectorData(weightedValue*learningRate*(resultData[i]-tempValue),inputData[i]));    
                }    
            }    
           // printf("\n");    
            errorCost=costFunction(parameter,inputData,resultData,objectVector);    
           // printf("error cost is %f\n",errorCost);    
            if(errorCost<errorThr)    
                break;    
        }//end stochastic one time    
    
    
    //calculate the object vector    
    double resultValue = 0.0;    
    for(int i=0;i<Number;i++){    
        resultValue += weightValue(inputData[i],objectVector)*multiPly(parameter[i],objectVector);    
    }    
    //printf("result value is %f \n",resultValue);    
    return resultValue;    
}    
    
int getlocalweight(vector<double> &fx,vector<double> &y,vector<double> &yh,time_t begintime,time_t endtime)
{
	vector<double> localParameter(endtime - fx[0] + 1,0.0);
	double fx0 = fx[0];
	for(int i = 0;i < fx.size();i++)
	{
		fx[i] = fx[i] - fx0 + 1;
	}
	Number = fx.size();
	int objectData=fx[fx.size() - 1];
        double res;
	for(int i = begintime - fx0 +1 ;i <= endtime - fx0 + 1;i++)
	{
		objectData = i;
    		res=LocallyWeightedAgression(localParameter,fx,y,objectData); 
		if(i >= begintime - fx0 + 1)
			if(res >= 0)
				yh.push_back(res);
			else
				yh.push_back(0);
	/*	Number++;
		fx.push_back(objectData);
		if(res >=0)
			y.push_back(res);
		else
			y.push_back(0);
	*/
	}

}
