/* ArraySearching */

#include <stdio.h>
#define SIZE 100

/* function prototype */
int linearSearch( const int array[], int key, int size );

/* function main begins program execution */

main()
{
	int a[SIZE];
	int x;
	int searchKey;
	int element;

	/* create data */
	for(x=0;x<SIZE;x++)
	{
		a[x]=2*x;
	}

	printf( "Enter integer search key:\n");
	scanf( "%d", &searchKey);

	element = linearSearch(a, searchKey, SIZE);

	if(element != -1)
	{
		printf("Found value in element %d\n", element );
	}
	else
	{
		printf("Value not found\n");
	}

	return 0;
}

int linearSearch( const int array[], int key, int size)
{
	int n; /*counter */
	for( n = 0; n<size; ++n)
	{
		if(array[n] == key )
		{
			return n;
		}
	}

	return -1;
}
