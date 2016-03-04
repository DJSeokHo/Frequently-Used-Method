#include <stdio.h>
#define SIZE 15

int binarySearch( const int b[], int searchKey, int low, int high );

main()
{
	int a[SIZE];
	int i;
	int key;
	int result;

	for(i=0;i<SIZE;i++)
	{
		a[i]=2*i;
	}

	printf("Enter a number between 0 and 28: ");
	scanf("%d", &key);

	result = binarySearch(a,key,0,SIZE-1);
	
	if(result!=-1)
	{
		printf("\n%d found in array element %d\n", key, result);
	}

	else
	{
		printf("\n%d not found\n", key);
	}

	return 0;
}

int binarySearch(const int b[], int searchKey, int low, int high)
{
	int middle;

	while( low <= high )
	{
		middle = (low + high)/2;

		if( searchKey == b[middle] )
		{
			return middle;
		}
		else if( searchKey < b[middle] )
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}

	return -1;
}
