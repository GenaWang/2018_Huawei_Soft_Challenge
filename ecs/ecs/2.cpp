#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
void getar1(vector<double> &fx,vector<double> &fxh,int length)
{
	int i,j;
	int N = fx.size();
	vector<double> x(N + length);
	for(int i = 0;i < N;i++)
		x[i] = fx[i];
	double *y;
	y=new double[N];

	double xn,temp;
	for(i=0,temp=0;i<N;i++)
	{
		temp+=x[i];
	}
	xn=temp/double(N);
	for(i=0;i<N;i++)
	{
		y[i]=x[i];//-xn;
	}
	int p,point=1;
	double AIC[11],A[10],DD;
	for(p=1;p<11;p++)//参数估计
	{
		double *a,*Ra,*R;
		a=new double[p];
		Ra=new double[p];
		R=new double[p+1];
		double **Rb;
		Rb=new double *[p];
		for(i=0;i<p;i++)
		{
			Rb[i]=new double[p];
		}
		for(i=0;i<p+1;i++)
		{
			temp=0;
			for(j=0;j<N-i;j++)
			{
				temp=temp+y[j]*y[j+i];
			}
			R[i]=temp/double(N);
		}
		for(i=0;i<p;i++)
		{
			Ra[i]=R[i+1];
		}
		for(i=0;i<p;i++)
		{
			for(j=0;j<p;j++)
			{
				Rb[i][j]=R[labs(i-j)];
			}
		}
		for(i=0;i<p;i++)//解方程
		{
			double dd=Rb[i][i];
			int kk=i;
			for(j=i+1;j<p;j++)
			{
				if(fabs(Rb[j][i])>fabs(dd))
					{
					    dd=Rb[j][i];
					    kk=j;
					}
			}
			if(kk!=i)
			{
				for(j=0;j<p;j++)
				{
					dd=Rb[i][j];
					Rb[i][j]=Rb[kk][j];
					Rb[kk][j]=dd;
				}
				dd=Ra[kk];
				Ra[kk]=Ra[i];
				Ra[i]=dd;
			}
			double r=Rb[i][i];
			for(j=0;j<p;j++) 
				Rb[i][j]=Rb[i][j]/r;
			Ra[i]=Ra[i]/r;
			for(j=i+1;j<p;j++)
			{
				double s=Rb[j][i];
				for(int nn=0;nn<p;nn++) 
					Rb[j][nn]=Rb[j][nn]-s*Rb[i][nn];
				Ra[j]=Ra[j]-s*Ra[i];
			}
		}
		for(i=0;i<p;i++)
		{
			for(j=0;j<p-i-1;j++)
			{
				Ra[j]=Ra[j]-Ra[p-i-1]*Rb[j][p-i-1];
			}
		}
		for(i=0;i<p;i++)
		{
			a[i]=Ra[i];
		}
		double D=R[0];
		for(i=0,temp=0;i<p;i++)
		{
			temp+=R[i+1]*a[i];
		}
		D=D-temp;
		AIC[p]=log(D)+2*p/double(N);
		if(p==1)
		{
			DD=D;
			for(i=0;i<p;i++)
			{
				A[i]=a[i];
			}
		}
		if(AIC[p]<AIC[point])
		{
			point=p;
			DD=D;
			for(i=0;i<p;i++)
			{
				A[i]=a[i];
			}
		}
	}
	double *x1;
	x1=new double[N+length];
	double *x2;
	x2=new double[N+length];
	for(i=0;i<N;i++)
	{
		x1[i]=fx[i];
		x2[i]=x1[i];
	}
	for(i=point;i<N+length;i++)
	{
		x2[i]=0;
		for(j=0;j<point;j++)
		{
			x2[i]+=A[j]*x1[i-j-1];
		}
		x1[i] = x2[i];
	}
	for(int i = N;i < N+length;i++)
		fxh.push_back((x2[i] > 0 ? x2[i] : 0));
}
