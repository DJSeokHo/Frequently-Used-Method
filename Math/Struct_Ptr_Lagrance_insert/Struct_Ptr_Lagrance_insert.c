//************************************************************************
//
//				This program is show how to using Lagrance insert
//				method to calculate an example of polynomial in 3 
//				base point.
//											   ----made by SeokHo
//
//************************************************************************
#include <stdio.h>
#include <stdlib.h>

#define N 10		//...number of base point
#define LinePointsNumber 100

typedef struct 
{
	double xi, yi;
}NodePoints;

typedef struct 
{
	double x, y;
}LinePoints;

main()
{
	FILE *test = fopen("test.dat","wt");

	double *fz, *fm, *Li;
	int i, j, p;
	double speclcase=0.0;

	NodePoints *NP;
	LinePoints *LP;

	NP = (NodePoints*)malloc(sizeof(NodePoints) * N);

	NP[0].xi = 0.10; NP[0].yi = 0.90;
	NP[1].xi = 0.15; NP[1].yi = 0.86;
	NP[2].xi = 0.30; NP[2].yi = 0.78;
	NP[3].xi = 0.40; NP[3].yi = 0.67;
	NP[4].xi = 0.50; NP[4].yi = 0.60;
	NP[5].xi = 0.60; NP[5].yi = 0.55;
	NP[6].xi = 0.70; NP[6].yi = 0.48;
	NP[7].xi = 0.85; NP[7].yi = 0.42;
	NP[8].xi = 0.90; NP[8].yi = 0.38;
	NP[9].xi = 1.00; NP[9].yi = 0.36;
	

	for(p=0;p<LinePointsNumber;p++)
	{
		LP = (LinePoints*)malloc(sizeof(LinePoints));
		LP->x = (double)p/LinePointsNumber;
		LP->y = 0.0;
		speclcase = 0.0;
		fz = (double*)malloc(N*sizeof(double));
		fm = (double*)malloc(N*sizeof(double));
		for(i=0;i<N;i++)
		{
			fz[i] = 1.0;
			fm[i] = 1.0;
		}
		//...Calculate Lagrance result polynomials Li
		for(i=0;i<N;i++)
		{
			Li = (double*)malloc(N*sizeof(double));
			for(j=0;j<=N-1;j++)
			{
				if(i!=j)
				{
					fz[i] *= (LP->x - NP[j].xi);
					fm[i] *= (NP[i].xi - NP[j].xi);
					Li[i] = fz[i] / fm[i];
				}
			}
		//	printf("%d  %lf\n", i+1, Li[i]);	//..check value
			LP->y += NP[i].yi * Li[i];					//..y is result
			speclcase += Li[i];					//..special case
	
		}

		free(fz);
		free(fm);
		free(Li);
		
	//	printf("%lf  %0.2f\n", LP->y, speclcase);	//..check value
		fprintf(test, "%lf %lf\n", LP->x, LP->y);
		free(LP);
	}
	free(NP);

	return 0;
}

