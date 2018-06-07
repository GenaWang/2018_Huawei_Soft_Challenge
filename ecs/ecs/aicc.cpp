#include"aicc.h"
#define H 100000  // 给所有的AICC赋一个较大的初值
using namespace std;
#define Q 2
#define P 2
inline int abs(int x)
{
	return fabs(x);
}


void getarma(vector<double> &x,vector<double> &xh,int STEP)
{
	int i,j,p,q,m,n,k,h,N;
   	double val;
   	double aicc[50][5][5]={H},xip[60][5][5][5]={0},xiq[60][5][5][5]={0};// xip,xiq,分别记录当m,p,q定时，ARMA对应项的系数
	double sita[20],fai[20];//sitaj[][]记录信息预报时的Sita，sitap[120][120]记录后来求预报时的Sita；
   	double sum,s,L,sigema[60][5][5];// ki[][]记录转化后的k(i,j),R[]记录计算约化似然函数时要用的r
    double sp;//xj[]记录m,p,q都确定时一步预报值	
	double min; // 记录当前AICC的最小值
   	vector<double> r;  
   	vector<double> faij;
   	vector<double> rj;
   	vector<double> vj;
   	vector<double> vp;
   	vector<double> R;
   	vector<double> xj;
   	vector<vector<double> >  sitaj, sitap,ki;    
   	        
   	N = x.size();
	
   	for(int k = 0;k < N;k++)
	{
		sum=0;
		for(int i = 1;i < N-k;i++)
		{
			sum += (x[i])*(x[i+k]);	
		}
		r.push_back(sum/double(N-1));
	}
	x.resize(N + STEP);
	r.resize(N + STEP);
	faij.resize(N + STEP);
	rj.resize(N + STEP);
	vj.resize(N + STEP);
	vp.resize(N + STEP);
	R.resize(N + STEP);
	xj.resize(N + STEP);
	xh.resize(STEP);
	sitaj.resize(N + STEP);
	sitap.resize(N + STEP);
	ki.resize(N + STEP);

	for(int i = 0 ;i < N+STEP;i++)
	{
		sitaj[i].resize(N + STEP);
		sitap[i].resize(N + STEP);
		ki[i].resize(N + STEP);	
	}
	
	min=100000.0;
	vj[0]=r[0];
	sitaj[1][1]=r[1]/r[0];
	vj[1]=r[0]-sitaj[1][1]*sitaj[1][1]*vj[0];
	for(n=2;n<=N-2;n++)
	{
		sitaj[n][n]=r[n]/vj[0];
		for(k=1;k<=n-1;k++)
		{
			sum=0;
			for(j=0;j<=k-1;j++)
				sum=sum+sitaj[k][k-j]*sitaj[n][n-j]*vj[j];
			sitaj[n][n-k]=(r[n-k]-sum)/vj[k];
		}
		sum=0;
		for(j=0;j<=n-1;j++)
			sum=sum+sitaj[n][n-j]*sitaj[n][n-j]*vj[j];
		vj[n]=r[0]-sum;
	}

	       //对m从2-30进行遍历p={1，2}q={1，2，3}时m,p,q确定的情况下所得系数分别存放在xip[m][p][q][] xiq[m][p][q][]中
	for(m=2;m<=30&&m<N;m++)
		for(q=1;q<m&&q<=Q;q++)
			for(p=1;p+q<=m&&p<=P&&(p+q)<N-3;p++) 
			{

				sitaj[m][0]=1;
				if(p==1)
					faij[p]=xip[m][p][q][1]=sitaj[m][q+1]/sitaj[m][q];
				else
				{
					faij[1]=xip[m][p][q][1]=(sitaj[m][q+2]*sitaj[m][q-1]-sitaj[m][q+1]*sitaj[m][q])/(sitaj[m][q+1]*sitaj[m][q-1]-sitaj[m][q]*sitaj[m][q]);
					faij[2]=xip[m][p][q][2]=(sitaj[m][q+2]*sitaj[m][q]-sitaj[m][q+1]*sitaj[m][q+1])/(sitaj[m][q]*sitaj[m][q]-sitaj[m][q+1]*sitaj[m][q-1]);
				}
				for(i=1;i<=20&&i<N;i++)
					if(i>p) faij[i]=0;
				for(j=1;j<=q;j++)
				{
					sum=0;			
					for(i=1;i<=j;i++)
				     	sum+=faij[i]*sitaj[m][j-i];
					xiq[m][p][q][j]=sitaj[m][j]-sum;
				}

			}

		//求AICC和BIC 
			int M;
			vector<double> sitaz(N+STEP,1);
			for(m=2;m<=30;m++)
				for(q=1;q<m&&q<=Q;q++)
					for(p=1;p<=P&&p+q<=m&&(p+q)<N-3;p++)
					{
						//首先把rx(i-j)转换为k(i,j);
						if(p>=q) M=p;
						else M=q;
						for(i=1;i<=N - 1;i++)
							for(j=1;j<=N - 1;j++)
							{
								if(i<=M&&j<=M)
									ki[i][j]=r[abs(i-j)]/vj[m];
								else if((i<=M||j<=M)&&(i<=2*M&&j<=2*M))
								{
									ki[i][j]=0;
									for(n=1;n<=p;n++)
										ki[i][j]=ki[i][j]+xip[m][p][q][n]*r[abs(n-abs(i-j))];
									ki[i][j]=(r[abs(i-j)]-ki[i][j])/vj[m];
								}
								else if(i>M&&j>M&&q>=abs(i-j))
								{
									for(n=1;n<=N;n++)
									{
										if(n>q) sitaz[n]=0;
										else sitaz[n]=xiq[m][p][q][n];
									}
									ki[i][j]=0;
									for(n=0;n<=q-abs(i-j);n++)
										ki[i][j]+=sitaz[n]*sitaz[n+abs(i-j)];
								}
								else ki[i][j]=0;
							}        // 求k(i,i)结束
							
					                //运用命题5.2.2的新息递归算法求出求解约化似然函数所要用到的系数
							vp[0]=ki[1][1];
	                        sitap[1][1]=ki[2][1]/ki[1][1];
	                        vp[1]=ki[2][2]-sitap[1][1]*sitap[1][1]*vp[0];
                       	    for(n=2;n<=N-2;n++)
							{
	                            sitap[n][n]=ki[n+1][1]/vp[0];
	                     	    for(k=1;k<=n-1;k++)
								{
		                        	sum=0;
		                     	    for(j=0;j<=k-1;j++)
				                   		sum=sum+sitap[k][k-j]*sitap[n][n-j]*vp[j];
			                         sitap[n][n-k]=(ki[n+1][k+1]-sum)/vp[k];
								}
		                       sum=0;
		                       for(j=0;j<=n-1;j++)
									sum=sum+sitap[n][n-j]*sitap[n][n-j]*vp[j];
		                       vp[n]=ki[n+1][n+1]-sum;			   
							} 
							for(i=0;i<=N-2;i++)
							{                        //检验m，p，q所确定的过程是否是因果的如果求得的均方误差中有负数说明该过程非因果
							   	if(vp[i]<0)
								{
									aicc[m][p][q]=H;
									goto loop;
								}
							}
							
							                                         //到此约化似然函数所需要的数据均已求出
                                                                 //利用5.3.9式对xj(n+1)进行预报
							xj[1]=0; 
							for(i=1;i<=N-1;i++)
							{
								xj[i+1]=0;
								if(p<=q) M=q;
								else M=p;
								if(i<=M)
								{

									for(j=1;j<=i;j++)
										xj[i+1]+=sitap[i][j]*(x[i+1-j]-xj[i+1-j]);
								}
								else
								{
									if(i<N-1)
									{
										for(j=1;j<=p;j++)
											xj[i+1]+=xip[m][p][q][j]*x[i+1-j];
										for(j=1;j<=q;j++)
											xj[i+1]+=sitap[i][j]*(x[i+1-j]-xj[i+1-j]);
									}
									else
									{
										for(j=1;j<=p;j++)
											xj[i+1]+=xip[m][p][q][j]*x[i+1-j];
										for(j=1;j<=q;j++)
											xj[i+1]+=sitap[i-1][j]*(x[i+1-j]-xj[i+1-j]);
									}
								}									
							}

							//到处求出了xj(n+1)			
							// 开始求R[i];
							for(i=0;i<=N-2;i++)
							   	R[i]=vp[i]/vj[m]; 
							s=0;
							for(j=1;j<=N-1;j++)
								s+=(x[j]-xj[j])*(x[j]-xj[j])/R[j-1];
							L=log(s/(N-1));
							for(i=1;i<=N-1;i++)
								L+=log(R[i-1])/(N-1);
							aicc[m][p][q]=-2*L+2*(p+1+q)*(N-1)/(N-1-p-q-2);// 求出aicc
							if(aicc[m][p][q]<min)                 //求出aicc当前最小时的h步预报
							{
								//
								for(h=2;h<=STEP;h++)
								{   
	
									xj[N-1+h]=0;
									if(q>=h)
									{
										for(i=1;i<=p;i++)
											xj[N-1+h]+=xip[m][p][q][i]*xj[N-1+h-i];
										for(i=h;i<=q;i++)
										{
											xj[N-1+h]+=sitap[N-2][j]*(x[N-1+h-j]-xj[N-1+h-j]);
										}
									}
									else
									{
										for(i=1;i<=p;i++)
										{
											xj[N-1+h]+=xip[m][p][q][i]*xj[N-1+h-i];	

										}						
									}										
								}
								for(i=N;i<N+STEP;i++)
									xh[i-N]=xj[i];           //用xh记录h步预报的结果
								min=aicc[m][p][q];
							}
loop:;
				   }
						/*for(i=N;i<N+STEP;i++)
							fp2 << xh[i] << ", ";
						*/							
}







