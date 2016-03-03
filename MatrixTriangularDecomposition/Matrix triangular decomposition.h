/*
  Matrix triangular decomposition.h
*/

void ludcmp(double **,int,int *,double *);
void lubksb(double **,int,int *,double *);
int *ivector(long nl, long nh);
double *dvector(long,long);
double **dmatrix(long,long,long,long);
void free_ivector(int *v, long nl, long nh);
void free_dvector(double *,long,long);
void free_dmatrix(double **,long,long,long,long);

void ludcmp(double **a, int n, int *indx, double *d){
	 int i,imax,j,k;
	 double big,dum,sum,temp;
	 double *vv;
	 vv=dvector(1,n);
	 *d=1.0;
	 for(i=1;i<=n;i++){
		 big=0.0;
		 for(j=1;j<=n;j++)
		 if((temp=fabs(a[i][j]))>big)big=temp;
			 vv[i]=1.0/big;
	 }
	 for(j=1;j<=n;j++){
		 for(i=1;i<j;i++){
			 sum=a[i][j];
			 for(k=1;k<i;k++) sum-=a[i][k]*a[k][j];
			 a[i][j]=sum;
		 }
		 big=0.0;
		 for(i=j;i<=n;i++){
			 sum=a[i][j];
			 for(k=1;k<j;k++)
			 sum-=a[i][k]*a[k][j];
			 a[i][j]=sum;
			 if ((dum=vv[i]*fabs(sum))>=big){
				 big=dum;
				 imax=i;
			 }
			}
			if(j!=imax){
			 for(k=1;k<=n;k++){
				 dum=a[imax][k];
				 a[imax][k]=a[j][k];
				 a[j][k]=dum;
			 }
			 *d=-(*d);
			 vv[imax]=vv[j];
			}
			indx[j]=imax;
			if(a[j][j]==0.0)a[j][j]=TINY;
			if(j!=n){
			 dum=1.0/(a[j][j]);
			 for(i=j+1;i<=n;i++)a[i][j]*=dum;
			}
	 }
	 free_dvector(vv,1,n);
}

void lubksb(double **a,int n,int *indx,double *b){
	 int i,ii=0,ip,j;
	 double sum;
	 for(i=1;i<=n;i++){
		 ip=indx[i];
		 sum=b[ip];
		 b[ip]=b[i];
		 if(ii)
			for(j=ii;j<=i-1;j++)sum-=a[i][j]*b[j];
		 else if(sum) ii=i;
			b[i]=sum;
	 }
	 for(i=n;i>=1;i--){
		 sum=b[i];
		 for(j=i+1;j<=n;j++)sum-=a[i][j]*b[j];
		 b[i]=sum/a[i][i];
	 }
}
double *dvector(long nl, long nh){
	double *v;
	v=(double *)malloc((size_t)((nh-nl+2)*sizeof(double)));
return v-nl+1;
}
void free_dvector(double *v,long nl,long nh){free((char *)(v+nl-1));}
double **dmatrix(long nrl,long nrh,long ncl,long nch){
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;
	m=(double **)malloc((size_t)((nrow+1)*sizeof(double*)));
	m+= 1;
	m-= nrl;
	m[nrl]=(double *)malloc((size_t)((nrow*ncol+1)*sizeof(double)));
	m[nrl] += 1;
	m[nrl] -= ncl;
	for(i=nrl+1;i<=nrh;i++)m[i]=m[i-1]+ncol;
	return m;
}
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch){
	free((char*) (m[nrl]+ncl-1));
	free((char*) (m+nrl-1));
}
int *ivector(long nl,long nh){
	int *v;
	v=(int *)malloc((size_t)((nh-nl+1)*sizeof(int)));
return v-nl;
}
void free_ivector(int *v,long nl,long nh){
	 free((char*) (v+nl));
}
