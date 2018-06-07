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
double w1[M];              // �в����ݴ洢����(�в��2)
double yuc[M]={0,-0.4609,-0.3841,-0.1235,0.0494,0.2782,0.5598,0.7035,0.8834,0.8040,0.5205};  // Ԥ��(����)�������ݴ洢����
int yuce[M];            // Ԥ���������ݴ洢����



void part_1()            // ***** ���ֵ�� *****
{
	int i,j;
	float sum=0;         // sum�������Ȼ��ȡ��ֵ
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


void part_2()            // ***** �ӳ�d����֣�ɾ�������d=10 *****
{
	int i,j;
	for(i=1;i<=N-d;i++)
		Jijsc[i]=Lingjzh[i+10]-Lingjzh[i];           // ���ݴ洢��ǰ101����Ԫ

	for(j=1;j<=N-d;j++)          
	{
			printf("%8.4f  ",Jijsc[j]);
		    if(j%10==0)
				printf("\n");
	}
}


void part_3()            // ***** ����������Э������������ϵ������ *****
{
	int j,h;
	float sum=0,mean;        // sum��mean����������X�ĺ����ֵ
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


void part_4_1()           // ***** ƽ���Լ��飨������飩*****
{
	int i,j,AU=0,AV=0;          // AU��AV�ֱ�Ϊ��С�ξ�ֵ�뷽����������� 
	float a[L],b[L];    // a[L]��b[L]�ֱ��Ÿ�С�εľ�ֵ������
	float EA,VA;                // EA��VAΪ�����������������������۷���(�������)
	for(i=0;i<L;i++)      // a[L]��ֵ
	{
		a[i]=0;
		for(j=1;j<=m;j++)
			a[i]=a[i]+(float)Jijsc[i*L+j];
		a[i]=a[i]/m;
	}
	for(i=0;i<L;i++)      // b[L]��ֵ
	{
		b[i]=0;
		for(j=1;j<=m;j++)
			b[i]=b[i]+(float)(Jijsc[i*L+j]-a[i])*(Jijsc[i*L+j]-a[i]);
		b[i]=b[i]/m;
	}
    for(i=0;i<L-1;i++)       // �����ֵ�뷽�����������
	{
		for(j=i+1;j<L;j++)
		{
			if(a[j]>a[i])
				AU++;
			if(b[j]>b[i])
				AV++;
		}
	}
	EA=(float)L*(L-1)/4;          // ������������������
	VA=(float)L*(2*L*L+3*L-5)/72;    // �������������۷���
}


void part_4_2()           // ***** ƽ���Լ��飨�ֶμ��飩*****
{
	int i,j,k,sign=0;          
	float a[L1],b[L1];    // a[L1]��b[L1]�ֱ��Ÿ�С�εľ�ֵ������
    float Vu=0,Vv=0;        // ������ֱ�Ϊa[L1],b[L1]�����۾�����
	for(i=0;i<L1;i++)      // a[L1]��ֵ
	{
		a[i]=0;
		for(j=0;j<m1;j++)
			a[i]=a[i]+(float)Jijsc[i*L1+j];
		a[i]=a[i]/m1;
	}
	for(i=0;i<L1;i++)      // b[L1]��ֵ
	{
		b[i]=0;
		for(j=0;j<m1;j++)
			b[i]=b[i]+(float)(Jijsc[i*L1+j]-a[i])*(Jijsc[i*L1+j]-a[i]);
		b[i]=b[i]/m1;
	}
    for(i=0;i<m1;i++)         // ����Vu����a[L1]�����۾�����
		Vu=Vu+(1-(i+1)/m1)*acf[i+1];
	Vu=(Vu*2+1)*acv[0]/m1;
    for(i=0;i<m1;i++)         // ����Vv����b[L1]�����۾�����
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


void part_5()            // ***** ��������ƫ�����ϵ����Durbin-Levinson�㷨 *****
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


void part_6()    // ***** AR(p)ģ�ͳ�����,Durbin-Levinson *****
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


void part_7()   // ***** AR(p)ģ��Ԥ�� *****
{
	float macv[M],x1,x2,t;
	int i,h;
	int p=2,q=0;
	float fi0=1,fi1=1.0009,fi2=-0.2173,sgmf=0.0694;
	x1=(fi1+sqrt(fi1*fi1+4*fi2))/2;      // �����
	x2=fi1-x1; 
	x1=1/x1;
	x2=1/x2;
	t=sgmf*x1*x1*x2*x2/((x1*x2-1)*(x2-x1));
	for(i=0;i<M;i++)
		macv[i]=t*(pow(x1*x1-1,-1)*pow(x1,1-i)-pow(x2*x2-1,-1)*pow(x2,1-i));
	int n,j,k;                // ***** ����Ϊ��Ϣ�㷨 *****
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
	for(n=1;n<=N-d;n++)     // һ��Ԥ��(1,2...102)
	{
		mxdata[n+1]=0;
		for(j=1;j<=n;j++)
			mxdata[n+1]=mxdata[n+1]+mxx[n][j]*(Jijsc[n+1-j]-mxdata[n+1-j]);
	}
    for(h=2;h<=c;h++)      // h��Ԥ��(103,104...)
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


void part_8_1()          // ***** AR(p)ģ������Ŷȼ���(�������) *****
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


void part_8_2()    // ***** AR(p)ģ������Ŷȼ���(�����ϵ������) *****
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

	for(int i = 1;i <= N;i++)               // ***** ��ԭʼ����ȡ����(��10Ϊ��) *****
		Yuans[i]=(double)Yuanshi[i];
	
	part_1();      // ���ֵ��
	part_2();      // d�����
	part_3();      // ��Э������������ϵ�����������
	part_4_1();    // ƽ���Լ���(�������)
	part_4_2();    // ƽ���Լ���(�ֶμ���)
	part_5();      // ƫ�����ϵ�����������
	part_6();      // AR(p)ģ�ͳ�����
	part_7();      // AR(p)ģ��Ԥ��
	part_8_1();    // AR(p)ģ������Ŷȼ���(�������)
	part_8_2();    // AR(p)ģ������Ŷȼ���(�����ϵ������)
    	for(int i=N+1;i<=N+c;i++)               // ***** ��ԭʼ����ȡ����(��10Ϊ��) *****
		xh.push_back(yuc[i]);
	
}

