//**************************************************
//****  dichotomy Cubic Equations solution  ********
//**************************************************

#include <stdio.h>
#include <math.h>
double CubicEquationssolution( double, double );
double CubicEquationssolution( double x, double rz )
{
	double xz = 0, fz = 0, fo = 0, ft = 0;
	double xo = -100, xt = 100; //scope
	double phs = 1, Uinf = 1;
	do{
		fo = ( Uinf * ( -1 ) ) * xo * xo * xo + phs * xo * xo + ( ( Uinf * x * x - rz ) * ( -1 ) ) * xo + ( phs * x * x ); //x,rz: variable
		if( fo == 0 )
		{
			xz = xo;
			goto loop;
		}
		ft = ( Uinf * ( -1 ) ) * xt * xt * xt + phs * xt * xt + ( ( Uinf * x * x - rz ) * ( -1 ) ) * xt + ( phs * x * x ); //x,rz: variable
		if( ft == 0 )
		{
			xz = xt;
			goto loop;
		}
	}while( fo * ft > 0 );
	do{
		xz = ( xo + xt ) / 2;
		fz = ( Uinf * ( -1 ) ) * xz * xz * xz + phs * xz * xz + ( ( Uinf * x * x - rz ) * ( -1 ) ) * xz + ( phs * x * x );
		if( fz == 0 )
			break;
		if( fz * fo < 0 )
		{
			xt = xz;
			ft = fz;
		}
		else
		{
			xo = xz;
			fo = fz;
		}
	}while( fabs( fz ) >= 1e-5 );
loop:	return xz;
};

main()
{
	double y; 
	y = CubicEquationssolution( 0, 1 );
	printf( "%0.5lf", y );
	return 0;
}
