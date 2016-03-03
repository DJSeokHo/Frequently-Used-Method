#include <stdio.h>

#define N 20

void Crout_method(float original[N][N], float L[N][N], float U[N][N], int dim);

main()
{
	int i, j, k, num_eq, num_var;
	float coeff[N][N], L[N][N], U[N][N], known[N];
	float ftemp, y[N], var[N];

	printf("Enter the number of Equations. :");
	scanf("%d", &num_eq);
	num_var=num_eq;
	for(i=0;i<num_eq;i++)
	{
		printf("**************************************\n");
		printf("%Enter the coefficients of eq. %d.\n",i+1);
		for(j=0;j<num_var;j++)
		{
			printf("coefficient of variable %d. :");
			scanf("%f",&coeff[i][j]);
		}
		printf("Enter the Known Value of eq. %d: ",i+1);
		scanf("%f", &known[i]);
	}
	printf("****************************************\n");

	printf("\n\n Entered Equations :\n");
	for(i=0;i<num_eq;i++)
	{
		for(j=0;j<num_var;j++)
		{
			printf("%10.3f * X%d", coeff[i][j], j+1);
			if(j!=num_var-1)
				printf("+");
			else
				printf("=");
		}
		printf("10.3f\n", known[i]);
	}

	for(i=0;i<num_eq;i++)
	{
		for(j=0;j<num_eq;j++)
		{
			L[i][j]=U[i][j]=0.0;
		}
	}

	Crout_method(coeff,L,U,num_eq);

	y[0]=known[0]/L[0][0];
	for(i=1;i<num_eq;i++)
	{
		ftemp=0;
		for(j=0;j<i;j++)
			ftemp+=L[i][j]*y[j];
		ftemp=known[i]-ftemp;
		y[i]=ftemp/L[i][i];
	}

	var[num_eq-1]=y[num_eq-1];
	for(i=num_eq-2;i>=0;i--)
	{
		ftemp=0;
		for(j=i+1;j<num_eq;j++)
			ftemp+=U[i][j]*var[j];
		var[i]=y[i]-ftemp;
	}
	printf("Result:\n");
	for(i=0;i<num_var;i++)
		printf("X%d=%10.3f\n",i+1,var[i]);
}

void Crout_method(float original[N][N], float L[N][N], float U[N][N], int dim)
{
		int i, row, column;
	float ftemp;
	for(row=0;row<dim;row++)
		L[row][0]=original[row][0];
	for(row=0;row<dim;row++)
		U[row][row]=1.0;
	for(column=1;column<dim;column++)
		U[0][column]=original[0][column]/original[0][0];
	for(column=1;column<dim;column++)
	{
		for(row=column;row<dim;row++)
		{
			ftemp=0.0;
			for(i=0;i<column;i++)
				ftemp+=L[row][i]*U[i][column];
			L[row][column]=original[row][column]-ftemp;
		}
		for(row=column+1;row<dim;row++)
		{
			ftemp=0;
			for(i=0;i<column;i++)
				ftemp+=L[column][i]*U[i][row];
			ftemp=original[column][row]-ftemp;
			U[column][row]=ftemp/L[column][column];
		}
	}
}

