#include <stdio.h>
#include <math.h>

#define Num 41
#define ORD 3
#define VER 7					//...Number of Vertices	
#define VER_ARR VER+ORD+1		//...Number of parameter u
#define rad -0.3
#define BP 7
#define PI 3.1415926535
#define TINY 1.0e-20

double ang_to_rad(double);

double cacu_BP_sn(double, double, double, double, double);
double cacu_BP_un(double, double);
void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot);
double cacu_Nki(double, double, double, double, double, double, double);
void matrix_inversion_using_elementary_operation( double original[BP][BP], double inverse[BP][BP], int dim);	
void LU_Method(double a[BP][BP], double b[BP], int dim, double resl[BP]);


main()
{
	FILE *BPxy=fopen("BPxy.dat","wt");
	FILE *test=fopen("test.dat","wt");
	FILE *CP=fopen("CP.dat","wt");

	int i, j, k, cacl_KV, spn[Num], spn_dev[Num], n, cout, cot, uNt, Nv;
	double U[VER_ARR], N[ORD+1][VER], N_sig[Num][VER];	
	double ksi[VER], eta[VER], d;

	double BaseP_x[BP], BaseP_y[BP], BP_sn[BP], BP_un[BP];
	double BP_N[ORD+1][BP], temp_BP_N[BP][BP], ktemp_BP_N[BP][BP], etemp_BP_N[BP][BP], inv_temp_BP_N[BP][BP];
	double BP_ksi[BP], BP_eta[BP];

	for(i=0;i<BP;i++)
	{
		BaseP_x[i] = i * 30;
		BaseP_y[i] = sin(ang_to_rad(BaseP_x[i]));
		fprintf(BPxy, "%lf %lf\n", BaseP_x[i], BaseP_y[i]);
	}

	for(i=0;i<BP;i++)
	{
		if(i==0)
		{
			BP_sn[i] = 0.0;
		}
		else
		{
			BP_sn[i] = cacu_BP_sn(BP_sn[i-1], BaseP_x[i], BaseP_x[i-1], BaseP_y[i], BaseP_y[i-1]);
		}
		
	}

	for(i=0;i<BP;i++)
	{
		BP_un[i] = cacu_BP_un(BP_sn[BP-1], BP_sn[i]);
	}
	
	create_Uni_Knot_Ver(&cacl_KV, VER, ORD, U);
	for(cout=0;cout<VER;cout++)
	{
		for(n=0;n<BP;n++)
		{
			for(k=0;k<=ORD;k++)
			{	
				for(i=0;i<VER;i++)
				{	
					if(k==0)
					{
						if(BP_un[n]>=U[i] && BP_un[n]<U[i+1])
						{
							BP_N[k][i] = 1.0;
						}
						else
						{
							BP_N[k][i] = 0.0;
						}
					}
					else if(k==ORD&&n==BP-1&&i==VER-1)
					{
						BP_N[k][i] = 1.0;				
					}
					else
					{
						BP_N[k][i] = cacu_Nki(BP_un[n], U[i], BP_N[k-1][i], U[i+k], BP_N[k-1][i+1], U[i+k+1], U[i+1]);
					}
				}
				if(k==ORD)
				{				
					temp_BP_N[n][cout] = BP_N[ORD][cout];
				}
			}
		}
	}
	
	for(i=0;i<BP;i++)
	{
		for(j=0;j<BP;j++)
		{
			fprintf(test,"%lf ", temp_BP_N[i][j]);
			ktemp_BP_N[i][j] = temp_BP_N[i][j];
			etemp_BP_N[i][j] = temp_BP_N[i][j];
		}
		fprintf(test, "\n");
	}
	
//	matrix_inversion_using_elementary_operation(temp_BP_N,inv_temp_BP_N,BP);

	LU_Method(ktemp_BP_N, BaseP_x, BP, ksi);
	LU_Method(etemp_BP_N, BaseP_y, BP, eta);

	for(i=0;i<VER;i++)
	{
		fprintf(CP, "%lf %lf\n", ksi[i], eta[i]);
	}

	return 0;
}

double ang_to_rad(double ANG)
{
	double temp_rad, temp_ang;
	temp_ang=ANG;
	temp_rad=(temp_ang*PI)/180;
	return temp_rad;
}

double cacu_BP_sn(double sn_1, double xn, double xn_1, double yn, double yn_1)
{
	double temp_sn_1, temp_xn, temp_xn_1, temp_yn, temp_yn_1, temp_resl;
	temp_sn_1=sn_1; temp_xn=xn; temp_xn_1=xn_1; temp_yn=yn; temp_yn_1=yn_1;
	temp_resl=temp_sn_1+sqrt(pow((temp_xn-temp_xn_1),2)+pow((temp_yn-temp_yn_1),2));
	return temp_resl;
}

double cacu_BP_un(double sNv_1, double sn)
{
	double temp_sNv_1, temp_sn, temp_resl;
	temp_sNv_1=sNv_1; temp_sn=sn;
	temp_resl=((double)(BP-ORD)/temp_sNv_1)*temp_sn;
	return temp_resl;
}

void create_Uni_Knot_Ver(int *u_num, int n, int p, double *knot)
{
	int temp_m, temp_n, temp_p, i, j, cot;
	double maxknotvalue;
	temp_n=n; temp_p=p;
	temp_m=temp_n+temp_p+1;
	maxknotvalue=(double)(temp_m-2*(temp_p+1)+1);	
	for(cot=0;cot<VER_ARR;cot++)
	{
		knot[cot]=0.0;
	}
	for(j=0;j<=p;j++) 
	{
		knot[j]=0.0;
		knot[temp_m-j]=maxknotvalue;
	}
	for(j=p+1,i=1;j<=n;j++) 
	{
		knot[j]=(double)i++;
	}
	*u_num = temp_m;
}//..ComputeUniformKnotVector()

double cacu_Nki(double u, double ui, double Nk_1i, double ui_k, double Nk_1i_1, double ui_k_1, double ui_1)
{
	double resl, temp_u, temp_ui, temp_Nk_1i, temp_ui_k, temp_Nk_1i_1, temp_ui_k_1, temp_ui_1, temp_left, temp_right;
	temp_u=u; temp_ui=ui; temp_Nk_1i=Nk_1i; temp_ui_k=ui_k; temp_Nk_1i_1=Nk_1i_1; temp_ui_k_1=ui_k_1; temp_ui_1=ui_1;
	if(((temp_u-temp_ui)*temp_Nk_1i)==0 || (temp_ui_k-temp_ui)==0)
	{
		temp_left=0.0;
	}
	else
	{
		temp_left=((temp_u-temp_ui)*temp_Nk_1i)/(temp_ui_k-temp_ui);
	}
	
	if(((temp_ui_k_1-temp_u)*Nk_1i_1)==0 || (temp_ui_k_1-temp_ui_1)==0)
	{
		temp_right=0.0;
	}
	else
	{
		temp_right=((temp_ui_k_1-temp_u)*Nk_1i_1)/(temp_ui_k_1-temp_ui_1);
	}		
	resl=temp_left+temp_right;
	return resl;
}

void matrix_inversion_using_elementary_operation(double original[BP][BP], double inverse[BP][BP], int dim)
{
	int row, column, pivot_column, max_index;
	double max_value, ftemp1, ftemp2, pivot_value;
	for( row = 0; row < dim; row++ )
		for( column = 0; column < dim; column++ ){
			if( row == column )
				inverse[row][column] = 1;
			else
				inverse[row][column] = 0;
		}
		for( pivot_column = 0; pivot_column < dim; pivot_column++ ){
			max_index = original[0][column];
			max_value = 0;
			for( row = pivot_column; row < dim; row++ )
				if( original[row][pivot_column]*original[row][pivot_column] > max_value*max_value ){
					max_index = row;
					max_value = original[row][pivot_column];
				}
				if(pivot_column != max_index )
					for( column = 0; column < dim; column++ ){
						ftemp1 = original[pivot_column][column];
						ftemp2 = inverse[pivot_column][column];
						original[pivot_column][column] = original[max_index][column];
						inverse[pivot_column][column] = inverse[max_index][column];
						original[max_index][column] = ftemp1;
						inverse[max_index][column] = ftemp2;
					}
					pivot_value = original[pivot_column][pivot_column];
					for(column = 0; column < dim; column++ ){
						original[pivot_column][column] /= pivot_value;
						inverse[pivot_column][column] /= pivot_value;
					}
					for( row = 0; row < dim; row++ )
						if( row != pivot_column ){
							ftemp1 = original[row][pivot_column];
							for( column = 0; column < dim; column++ ){

								original[row][column] -= ftemp1*original[pivot_column][column];
								inverse[row][column] -= ftemp1*inverse[pivot_column][column];

							}
						}
		}
}

void LU_Method(double a[BP][BP], double b[BP], int dim, double resl[BP])
{
	int i, j, k, t, n;
	double l[BP][BP], u[BP][BP], x[BP], y[BP], temp;
	n = dim;

	for(k=0;k<n-1;k++)    
	{ 
		if (a[k][k]==0)   
		{   
			printf ("All of mian line element are 0, exit");
			return;  
		}  
		for(i=k+1;i<n;i++)  
		{   
			for(j=0;j<k;j++)   
			{    
				a[i][k]=a[i][k]-a[j][k]*a[i][j];   
			}   
			a[i][k]=a[i][k]/a[k][k];  
		}  
		for(j=k+1;j<n;j++)  
		{   
			for(i=0;i<k+1;i++)   
			{    
				a[k+1][j]=a[k+1][j]-a[k+1][i]*a[i][j];   
			}  
		} 
	}  
	for(i=0; i<n; i++) 
	{  
		for(j=0; j<n; j++)  
		{   
			u[i][j]=0;  
		} 
	}  
	for(i=0; i<n; i++) 
	{  
		for(j=i; j<n; j++)  
		{   
			u[i][j]=a[i][j];  
		} 
	}  
	for(i=0; i<n; i++) 
	{  
		for(j=0; j<n; j++) 
		{   
			l[i][j]=0;  
		} 
	}  
	for(i=0; i<n; i++) 
	{  
		l[i][i]=1; 
	}  
	for(i=n-1; i>-1; i--) 
	{  
		for(j=0;j<i;j++)  
		{   
			l[i][j]=a[i][j];  
		} 
	}
	y[0]=b[0];  
	for(i=1; i<n; i++) 
	{  
		temp=0;  
		for(t=0;t<=i-1;t++)  
		{   
			temp=temp+l[i][t]*y[t];  
		}  
		y[i]=b[i]-temp; 
	}  
	x[n-1]=y[n-1]/u[n-1][n-1]; 
	for(i=n-2; i>=0; i--) 
	{  
		temp=0;  
		for(t=i+1;t<n;t++)  
		{  
			temp=temp+u[i][t]*x[t];  
		}  
		x[i]=(y[i]-temp)/u[i][i]; 
	}    
	for (i=0; i<n; i++)     
	{      
		resl[i] = x[i];
	}
}
