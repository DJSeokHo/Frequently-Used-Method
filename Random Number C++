#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

#define SN 11

using namespace std;

int main(void)
{
	ofstream SalNumber;
	SalNumber.open("SalNumber.dat");

	int SalNumInt[SN], i;
	char SalNumChar[SN];
	srand(time(NULL));    

	for(i=0;i<SN;i++)  
	{
		SalNumInt[i] = rand()%10+0;
		itoa(SalNumInt[i], &SalNumChar[i], 10);
	//	cout<<i+1<<" Random number: "<<SalNumInt[i]<<endl;
		cout<<i+1<<" Random number: "<<SalNumChar[i]<<endl;
	//	SalNumber<<SalNum[i]<<endl;
	}

	return 0;
	
//	fprintf(test, "%lf\n", 0.5);

}
