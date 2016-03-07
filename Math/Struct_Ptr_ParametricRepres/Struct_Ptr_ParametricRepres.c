//************************************************************************
//
//				This program is show how to use Newton difference
//				method to calculate an example.
//											   ----made by SeokHo
//
//************************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define IT 400

typedef struct
{
	double basex;
	double basey;
}BasePoints;

typedef struct 	//need init to {0.0,0.0}
{
	double x;
	double y;
}LinePoints;

main()
{
	FILE *test=fopen("test.dat","wt");
	FILE *basep=fopen("basep.dat","wt");
	
	double *temp_X, *temp_Y, **d, *t, *a, *b;
	int i, j, n;
	double *item;

	BasePoints *BP;
	LinePoints *LP;

	BP = (BasePoints*)malloc(sizeof(BasePoints) * N);
	LP = (LinePoints*)malloc(sizeof(LinePoints) * IT);

	item = (double*)malloc(sizeof(double) * N);
	a = (double*)malloc(sizeof(double) * N);
	b = (double*)malloc(sizeof(double) * N);
	t = (double*)malloc(sizeof(double) * N);
	d = (double**)malloc(sizeof(double *) * N);
	d[0] = (double*)malloc(sizeof(double) * N * N);
	for(i=1; i<N; i++)
	{
		d[i] = d[i-1] + N;
	}

//..init	In this example, we calculate ln(x) function while x = 6.0
/*
	basex[0] = 0.0; 
	basex[1] = 8.0;
	basex[2] = 19.0;
	basex[3] = 18.0;
	basex[4] = 27.0;
	basex[5] = 19.0;
	basex[6] = 2.0;

	basey[0] = 0.0;
	basey[1] = 3.0;
	basey[2] = 12.0;
	basey[3] = 32.0;
	basey[4] = 45.0;
	basey[5] = 48.0;
	basey[6] = 46.0;
*/

	BP[0].basex = 0.0; 
	BP[1].basex = 1.0;
	BP[2].basex = 1.0;
	BP[3].basex = 0.0;
	BP[4].basex = 0.0;

	BP[0].basey = 0.0;
	BP[1].basey = 0.0;
	BP[2].basey = 1.0;
	BP[3].basey = 1.0;
	BP[4].basey = 0.0;

	for(n=0;n<N;n++)
	{
		fprintf(basep, "%lf %lf\n", BP[n].basex, BP[n].basey);
	}
	
	for(n=0;n<N;n++)	//...Here mean's we know t0, we get t for n=1,...N-1
	{
		if(n==0)
		{
			t[n] = 0.0;
		}
		else
		{
			t[n] = sqrt(pow((BP[n].basex - BP[n-1].basex), 2) + pow((BP[n].basey - BP[n-1].basey), 2)) + t[n-1];
		}
	}
	
//...calculate coe a  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = BP[i].basex;				//...dependent variable is x
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		a[i] = d[0][i];
	}
	
	for(n=0;n<IT;n++)
	{	
		temp_X = (double*)malloc(sizeof(double));
		temp_Y = (double*)malloc(sizeof(double));
		*temp_X = (double)n/100;		//!!!!!!!!!!!!!!!!!!!!...here is important about the value
		*temp_Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (*temp_X - t[j]);
			}
			
			item[i] = item[i] * a[i];		
			*temp_Y += item[i];
		}
		*temp_Y += a[0];
		LP[n].x = *temp_Y;
		free(temp_X);
		free(temp_Y);
	}

//...calculate coe b  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = BP[i].basey;				//...dependent variable is y
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		b[i] = d[0][i];
	}
	for(n=0;n<IT;n++)
	{
		temp_X = (double*)malloc(sizeof(double));
		temp_Y = (double*)malloc(sizeof(double));
		*temp_X = (double)n/100;	//!!!!!!!!!!!!!!!!!!!!...here is important about the value
		*temp_Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (*temp_X - t[j]);
			}
			
			item[i] = item[i] * b[i];		
			*temp_Y += item[i];
		}
		*temp_Y += b[0];
		LP[n].y = *temp_Y;
		fprintf(test, "%lf %lf\n",LP[n].x, LP[n].y);
		free(temp_X);
		free(temp_Y);
	}
	
	free(item);
	free(a);
	free(b);
	free(t);
	free(d[0]);
	free(d);
	free(BP);
	free(LP);

	return 0;
}
