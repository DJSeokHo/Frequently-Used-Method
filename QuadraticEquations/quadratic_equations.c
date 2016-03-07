#include <stdio.h>
#include <math.h>
double ans( double, double, double );
double QuadraticEquations( double, double, double );

void main()
{
	double re;
	re = QuadraticEquations( 2, -1, 1 );
	printf( "%0.5lf", re );
}

double QuadraticEquations( double a, double b, double c )
{
	double x;
	if( a != 0 )
	{
		x = ans( a, b, c );
		return x;
	}
	else
	{
		printf( "no solution!" );
		return 0;
	}
}

double ans(double a,double b,double c)
{
	double d, x1, x2, s;
	d = b * b - 4 * a * c;
	if(d<0)
	{
		printf( "no solution!\n" );
		return 0;
	}
	else
	{
		s = sqrt( d );
		x1 = ( -b + s ) / ( 2 * a ), x2 = ( -b -s ) / ( 2 * a );
		return x1;
	}
}
