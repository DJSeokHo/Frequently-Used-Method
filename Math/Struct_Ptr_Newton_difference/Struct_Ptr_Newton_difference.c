#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9
#define PI 3.1415926535
#define LinePointsNumber 450

void ang_to_rad(double *ANG);                        //trans degree to radian

typedef struct 
{
	double x;
	double y;
}NodePoints;

typedef struct
{
	double X;
	double Y;
}LinePoints;

main()
{
	FILE *test=fopen("test.dat","wt");
	FILE *ELL=fopen("ell.dat","wt");
	
	int i, j, n;
	double *ALPA, **d, *resul_d, *item;

	NodePoints *NP;
	LinePoints *LP;
	
	NP = (NodePoints*)malloc(sizeof(NodePoints) * N);
	ALPA = (double*)malloc(sizeof(double) * N);
	resul_d = (double*)malloc(sizeof(double) * N);
	item = (double*)malloc(sizeof(double) * N);
	d = (double**)malloc(sizeof(double *) * N);//分配指针数组
	d[0] = (double*)malloc(sizeof(double) * N * N);//一次性分配所有空间
	for(i=1; i<N; i++)
	{
		d[i] = d[i-1] + N;
	}

//..init	In this example, we calculate a quarter of ellipse
	for(i=0;i<N;i++)
	{
		ALPA[i] = ((double)i / (N-1)) * (PI / 2.0);
	}
	for(i=0;i<N;i++)
	{
		NP[i].x = 1.0 - cos(ALPA[i]);
		NP[i].y = 0.1 * sin(ALPA[i]);
		fprintf(ELL, "%lf %lf\n", NP[i].x, NP[i].y);
	}
	free(ALPA);

	for(i=0;i<N;i++)
	{
		d[i][0] = NP[i].y;
	}

	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (NP[i+j].x - NP[i].x);
		}
	}
	
	for(i=0;i<N;i++)
	{
		resul_d[i] = d[0][i];
	}
	free(d[0]);
	free(d);

	for(n=0;n<LinePointsNumber;n++)
	{
		LP = (LinePoints*)malloc(sizeof(LinePoints));
		LP->X = (double)n / LinePointsNumber;
		LP->Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (LP->X - NP[j].x);
			}
			
			item[i] = item[i] * resul_d[i];		
			LP->Y += item[i];
		}
		LP->Y += resul_d[0];
		fprintf(test, "%lf %lf\n", LP->X, LP->Y);
		free(LP);
	}
	free(item);
	free(NP);
	free(resul_d);
	return 0;
}
