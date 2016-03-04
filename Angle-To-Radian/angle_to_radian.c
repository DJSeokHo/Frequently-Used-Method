/*

Code by seokho(SHI HAO)

*/

#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

float ang_to_rad(float);                        //trans degree to radian
float rad_to_ang(float);
float cacu_slope(float, float, float, float);	//cacu_betam

main()
{
	float x1, y1, x2, y2, cosbetam, sinbetam, betam, slope;

	slope = -1.0;

	printf("%0.4f\n", rad_to_ang(slope));
	return 0;
}

float ang_to_rad(float ANG)
{
	float temp_rad, temp_ang;
	temp_ang=ANG;
	temp_rad=(temp_ang*PI)/180;
	return temp_rad;
	temp_rad=0; temp_ang=0;
}

float rad_to_ang(float RAD)
{
	float temp_ang_, temp_rad_;
	temp_rad_=RAD;
	temp_ang_ = temp_rad_/PI*180;
	return temp_ang_;
	temp_rad_=0; temp_ang_=0;
}

float cacu_slope(float X1, float X2, float Y1, float Y2)
{
	float temp_slope, temp_x1, temp_x2, temp_y1, temp_y2;
	temp_x1=X1; temp_x2=X2; temp_y1=Y1; temp_y2=Y2;
	temp_slope=(temp_y2-temp_y1)/(temp_x2-temp_x1);
	return temp_slope;
	temp_slope=0; temp_x1=0; temp_x2=0; temp_y1=0; temp_y2=0;
}
