#include <stdio.h> 
#include <conio.h> 
#include <math.h>  
#define max_dimension 100 //超过500就会溢出！！fuck！  
void main() 
{  
	int n,i,j,k,t;//int变量n,i，j，k,t 
	float  a[max_dimension][max_dimension],l[max_dimension][max_dimension],u[max_dimension][max_dimension];  
	float b[max_dimension];  
	float x[max_dimension],y[max_dimension]; 
	double temp; //输入矩阵部分  
	printf("请输入矩阵维数:");  
	scanf("%d",&n);  
	printf("\n");   
	printf("请按行输入矩阵元素: ");  
	printf("\n\n");  
	for (i=0; i<n; i++) 
	{     
		printf("请输入矩阵第%d行元素的大小:",i+1);     
		for (j=0; j<n; j++)   
		{     
			scanf("%f",&a[i][j]);                      //第i行的值存在 a[i][j]里    
		}     
		printf("\n"); 
	}  
	printf("请输入常数项: ");                     // 输入常数项 
	for (i=0; i<n; i++)  
		scanf("%f",&b[i]);                           //存在 b[i]里  
	printf("所要计算的增广阵为 :\n\n");            // 所要计算的增广阵是a|b 
	for (i=0; i<n; i++) 
	{     
		for (j=0; j<n; j++)    
			printf("%f,",a[i][j]);    
		printf("%f",b[i]);    
		printf("\n"); 
	}  
	printf("\n"); //输入矩阵完毕  
	for(k=0; k<n-1;k++)   //??n-2??           
	{ 
		if (a[k][k]==0)   
		{   
			printf ("主对角元素=0，退出计算");
			getch();
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
	printf("所示消元之后的a矩阵为 :\n\n");   
	for (i=0; i<n; i++)     
	{     
		for (j=0; j<n; j++)    
			printf("%f,",a[i][j]);    
		printf("\n");  
	}//a矩阵已经成功分解 
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
	}  //显示分解好的l,u矩阵  
	printf("所示消元之后的l矩阵为 :\n\n");   
	for (i=0; i<n; i++)                       
	{     
		for (j=0; j<n; j++)    
			printf("%f,",l[i][j]);    
		printf("\n"); 
	}  
	printf("所示消元之后的u矩阵为 :\n\n");   
	for (i=0; i<n; i++)     
	{     
		for (j=0; j<n; j++)    
			printf("%f,",u[i][j]);    
		printf("\n"); 
	}  //显示完毕 //求解 
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
	printf("解出的中间解y[n] :\n");   
	for (i=0; i<n; i++)     
	{      
		printf("\n"); 
		printf("%f",y[i]); 
	}  
	printf("\n");//  
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
	printf("解出的最终解x[n] :\n");   
	for (i=0; i<n; i++)     
	{      
		printf("\n");  
		printf("%f",x[i]); 
	}  
	getch(); 
}
