#include"getar.h"

#define M  	420         
#define d 	10          
#define L 	8           
#define m 	12          
#define L1 	8          
#define m1 	12         
int N = 200;
int c = 10;           
double Yuanshi[M];
double Yuans[M];           
double Lingjzh[M];         
double Mean;               
double Jijsc[M];           
double acv[M];             
double acf[M];             
double pacf[M];           
double dl[M][M];           
double v[M];               
double mxx[M][M];        
double mxv[M];             
double mxdata[M];          
double w[M];             
double w1[M];              // 残差数据存储数组(残差定义2)
double yuc[M]={0,-0.4609,-0.3841,-0.1235,0.0494,0.2782,0.5598,0.7035,0.8834,0.8040,0.5205};  // 预测(对数)所得数据存储数组
int yuce[M];            // 预测所得数据存储数组



void part_1()            // ***** 零均值化 *****
{
	int i,j;
	float sum=0;         // sum用于求和然后取均值
	for(i=1;i<=N;i++)
		sum=sum+Yuans[i];
	Mean=sum/N;
	for(i=1;i<=N;i++)
		Lingjzh[i]=Yuans[i]-Mean;

	for(j=1;j<=N;j++)          
	{
			printf("%8.4f  ",Lingjzh[j]);
		    if(j%10==0)
				printf("\n");
	}
}


void part_2()            // ***** 延迟d步差分，删除季节项，d=10 *****
{
	int i,j;
	for(i=1;i<=N-d;i++)
		Jijsc[i]=Lingjzh[i+10]-Lingjzh[i];           // 数据存储在前101个单元

	for(j=1;j<=N-d;j++)          
	{
			printf("%8.4f  ",Jijsc[j]);
		    if(j%10==0)
				printf("\n");
	}
}


void part_3()            // ***** 计算样本自协方差函数和自相关系数函数 *****
{
	int j,h;
	float sum=0,mean;        // sum和mean用于求样本X的和与均值
	for(j=1;j<=N-d;j++)
		sum=sum+Jijsc[j];
	mean=sum/(N-d);
	for(h=0;h<N-d;h++)
	{
		acv[h]=0;
		for(j=1;j<=N-d-h;j++)
			acv[h]=acv[h]+(Jijsc[j+h]-mean)*(Jijsc[j]-mean);
		acv[h]=acv[h]/(N-d);
	}

	if(acv[0]==0)
		printf("acv[0]=0\n");
	else
		for(h=0;h<N-d;h++)
			acf[h]=acv[h]/acv[0];
	for(j=0;j<N-d;j++)          
	{
			printf("%8.4f  ",acf[j]);
		    if((j+1)%10==0)
				printf("\n");
	}
}


void part_4_1()           // ***** 平稳性检验（逆序检验）*****
{
	int i,j,AU=0,AV=0;          // AU和AV分别为各小段均值与方差的逆序总数 
	float a[L],b[L];    // a[L]、b[L]分别存放各小段的均值、方差
	float EA,VA;                // EA和VA为逆序总数的理论期望和理论方差(逆序检验)
	for(i=0;i<L;i++)      // a[L]求值
	{
		a[i]=0;
		for(j=1;j<=m;j++)
			a[i]=a[i]+(float)Jijsc[i*L+j];
		a[i]=a[i]/m;
	}
	for(i=0;i<L;i++)      // b[L]求值
	{
		b[i]=0;
		for(j=1;j<=m;j++)
			b[i]=b[i]+(float)(Jijsc[i*L+j]-a[i])*(Jijsc[i*L+j]-a[i]);
		b[i]=b[i]/m;
	}
    for(i=0;i<L-1;i++)       // 计算均值与方差的逆序总数
	{
		for(j=i+1;j<L;j++)
		{
			if(a[j]>a[i])
				AU++;
			if(b[j]>b[i])
				AV++;
		}
	}
	EA=(float)L*(L-1)/4;          // 逆序总数的理论期望
	VA=(float)L*(2*L*L+3*L-5)/72;    // 逆序总数的理论方差
}


void part_4_2()           // ***** 平稳性检验（分段检验）*****
{
	int i,j,k,sign=0;          
	float a[L1],b[L1];    // a[L1]、b[L1]分别存放各小段的均值、方差
    float Vu=0,Vv=0;        // 该三项分别为a[L1],b[L1]的理论均方差
	for(i=0;i<L1;i++)      // a[L1]求值
	{
		a[i]=0;
		for(j=0;j<m1;j++)
			a[i]=a[i]+(float)Jijsc[i*L1+j];
		a[i]=a[i]/m1;
	}
	for(i=0;i<L1;i++)      // b[L1]求值
	{
		b[i]=0;
		for(j=0;j<m1;j++)
			b[i]=b[i]+(float)(Jijsc[i*L1+j]-a[i])*(Jijsc[i*L1+j]-a[i]);
		b[i]=b[i]/m1;
	}
    for(i=0;i<m1;i++)         // 计算Vu，即a[L1]的理论均方差
		Vu=Vu+(1-(i+1)/m1)*acf[i+1];
	Vu=(Vu*2+1)*acv[0]/m1;
    for(i=0;i<m1;i++)         // 计算Vv，即b[L1]的理论均方差
		Vv=Vv+(1-(i+1)/m1)*acf[i+1]*acf[i+1];
	Vv=(Vv*2+1)*acv[0]*acv[0]*2/m1;
	for(i=0;i<L1;i++)
		for(j=i+1;j<L1;j++)
			if(fabs(a[i]-a[j])>2.77*sqrt(Vu))
			{
				sign=1;
				break;
			}
	if(sign==0)
		for(i=0;i<L1;i++)
			for(j=i+1;j<L1;j++)
				if(fabs(b[i]-b[j])>2.77*sqrt(Vv))
				{
					sign=1;
				    break;
				}
}


void part_5()            // ***** 计算样本偏自相关系数，Durbin-Levinson算法 *****
{
	int i,j;
    v[0]=acv[0];
	dl[1][1]=acv[1]/acv[0];
	v[1]=v[0]*(1-dl[1][1]*dl[1][1]);
	for(i=2;i<N-d;i++)
	{
		dl[i][i]=0;
		for(j=1;j<=i-1;j++)
			dl[i][i]=dl[i][i]+dl[i-1][j]*acv[i-j];
		dl[i][i]=(acv[i]-dl[i][i])/v[i-1];
		for(j=1;j<=i-1;j++)
			dl[i][j]=dl[i-1][j]-dl[i][i]*dl[i-1][i-j];
		v[i]=v[i-1]*(1-dl[i][i]*dl[i][i]);
	}
	pacf[0]=1.0;
	for(i=1;i<N-d;i++)
		pacf[i]=dl[i][i];

	for(j=0;j<N-d;j++)          
	{
			printf("%8.4f  ",pacf[j]);
		    if((j+1)%10==0)
				printf("\n");
	}
}


void part_6()    // ***** AR(p)模型初估计,Durbin-Levinson *****
{
	int i,j;
	float Aic,Bic,Fpe;

	for(i=1;i<=6;i++)
	{
		Aic=log(v[i])+2.0*i/(N-d);
	    Bic=log(v[i])+i*log(N-d)/(N-d);
	    Fpe=v[i]*(N-d+i)/(N-d-i);
	}
	
}


void part_7()   // ***** AR(p)模型预测 *****
{
	float macv[M],x1,x2,t;
	int i,h;
	int p=2,q=0;
	float fi0=1,fi1=1.0009,fi2=-0.2173,sgmf=0.0694;
	x1=(fi1+sqrt(fi1*fi1+4*fi2))/2;      // 根求解
	x2=fi1-x1; 
	x1=1/x1;
	x2=1/x2;
	t=sgmf*x1*x1*x2*x2/((x1*x2-1)*(x2-x1));
	for(i=0;i<M;i++)
		macv[i]=t*(pow(x1*x1-1,-1)*pow(x1,1-i)-pow(x2*x2-1,-1)*pow(x2,1-i));
	int n,j,k;                // ***** 下面为新息算法 *****
	mxv[0]=macv[0];
	for(n=1;n<M;n++)
	{
		for(k=0;k<=n-1;k++)
		{
			mxx[n][n-k]=0;
		    for(j=0;j<=k-1;j++)
				mxx[n][n-k]=mxx[n][n-k]-mxx[k][k-j]*mxx[n][n-j]*mxv[j];
		    mxx[n][n-k]=(mxx[n][n-k]+macv[n-k])/mxv[k];
		}
		mxv[n]=0;
		for(j=0;j<=n-1;j++)
			mxv[n]=mxv[n]-mxx[n][n-j]*mxx[n][n-j]*mxv[j];
		mxv[n]=mxv[n]+macv[0];
	}
	mxdata[1]=0;
	for(n=1;n<=N-d;n++)     // 一步预报(1,2...102)
	{
		mxdata[n+1]=0;
		for(j=1;j<=n;j++)
			mxdata[n+1]=mxdata[n+1]+mxx[n][j]*(Jijsc[n+1-j]-mxdata[n+1-j]);
	}
    for(h=2;h<=c;h++)      // h步预报(103,104...)
	{
		mxdata[N-d+h]=0;
		for(j=h;j<=N-d+h-1;j++)
			mxdata[N-d+h]=mxdata[N-d+h]+mxx[N-d+h][j]*(Jijsc[N-d+h-j]-mxdata[N-d+h-j]);
	}
    for(i=d+1;i<=N+c;i++)
		yuc[i]=yuc[i-d]+mxdata[i-d];
	for(i=1;i<=N+c;i++)
		yuc[i]=yuc[i]+Mean;

}


void part_8_1()          // ***** AR(p)模型拟和优度检验(逆序检验) *****
{
	int i,h;
	float wmean=0,rou[M],sum=0,Qww[M]={0};
	for(i=1;i<=N-d;i++)
		w[i]=(Jijsc[i]-mxdata[i])/pow(mxv[i-1],0.5);

	int T=0;
	float miu,sgmf;
	for(i=2;i<N-d;i++)
		if(w[i]>w[i-1]&&w[i]>w[i+1])
			T++;
	for(i=2;i<N-d;i++)
		if(w[i]<w[i-1]&&w[i]<w[i+1])
			T++;
	miu=2.0*(N-d-2)/3;
    sgmf=(float)(16*(N-d)-29)/90;

}


void part_8_2()    // ***** AR(p)模型拟和优度检验(自相关系数检验) *****
{
	int i,j,k,M1=30;
	float fi1=1.0009,fi2=-0.2173,r[M],rou[M],Q=0;
	w1[1]=Jijsc[1];
	w1[2]=Jijsc[2];
	for(i=3;i<=N-d;i++)
		w1[i]=Jijsc[i]-fi1*Jijsc[i-1]-fi2*Jijsc[i-2];

	for(i=1;i<=N-d;i++)
	{
		printf("%8.4f  ",w1[i]);
		if(i%10==0)
			printf("\n");
	}
    for(k=0;k<=M1;k++)
	{
		r[k]=0;
		for(j=1;j<=N-d-k;j++)
			r[k]=r[k]+w1[j]*w1[j+k];
		r[k]=r[k]/(N-d);
	}
    for(j=0;j<=M1;j++)
		rou[j]=r[j]/r[0];
    for(j=1;j<=M1;j++)
		Q=Q+rou[j]*rou[j];
	Q=Q*(N-d);
}
void getar(vector<double> &x,vector<double> &xh,int length)
{
	N = x.size() + 1;
	c = length;
	for(int i = 0;i < N-1;i++)
		Yuanshi[i+1] = x[i];

	for(int i = 1;i <= N;i++)               // ***** 对原始数据取对数(以10为底) *****
		Yuans[i]=(double)Yuanshi[i];
	
	part_1();      // 零均值化
	part_2();      // d步差分
	part_3();      // 自协方差函数和自相关系数函数的求解
	part_4_1();    // 平稳性检验(逆序检验)
	part_4_2();    // 平稳性检验(分段检验)
	part_5();      // 偏自相关系数函数的求解
	part_6();      // AR(p)模型初估计
	part_7();      // AR(p)模型预测
	part_8_1();    // AR(p)模型拟和优度检验(逆序检验)
	part_8_2();    // AR(p)模型拟和优度检验(自相关系数检验)
    	for(int i=N+1;i<=N+c;i++)               // ***** 对原始数据取对数(以10为底) *****
		xh.push_back(yuc[i]);
	
}

