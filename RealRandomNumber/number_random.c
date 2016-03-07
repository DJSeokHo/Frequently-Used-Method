#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float cacu_randomNum(void);
main()
{
	float Q;
	int i;
	for(i=0;i<10;i++)
	{
		Q = cacu_randomNum();
		printf("%0.4f\n", Q);
	}
	
	return 0;
}

float cacu_randomNum(void)
{
	int IA, IM, IQ, IR, j, k, ran_num = 2;
	float AM, RNMX, ran;	
	IA=16807;
	IM=2147483647;
	IQ=127773;
	IR=2836;
	AM=1.0/(float)IM;
	RNMX=1.0-1.0e-8;
	if(ran_num<1)
	{
		if(ran_num<-1)
		{
			ran_num=-ran_num;
		}
		else
		{
			ran_num=1;
		}
	}
	
	for(j=1;j<=32;j++)
	{
		k=ran_num/IQ;
		ran_num=IA*(ran_num-k*IQ)-IR*k;
		if(ran_num<0) 
		{
			ran_num+=IM;
		}
	}
	
	ran=AM*ran_num;
	if(ran>RNMX) 
	{
		ran=RNMX;
	}
	return ran;	
}
