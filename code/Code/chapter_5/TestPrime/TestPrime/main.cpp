#include "BigNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"1234567890",10);

	for (;;)
	{
		if (IsPrimeNumber(&A))
			break;

		A = PlusDigit(&A, 1);
	}

	printDecimal(A);
}
*/


//--------------------------------------------------------------
int main()
{
	int i;
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"2",1);

	for (i=0; i<5; i++)
		A = MULTIPLY(&A, &A);

	for (;;)
	{
		if (IsPrimeNumber(&A))
			break;

		A = PlusDigit(&A, 1);
	}

	printDecimal(A);
}


/*
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"4382591627",10);

	int i;
	unsigned char *ptrForFree;

	FILE *fp;

	if ((fp=fopen("prime.txt", "wt"))==NULL)
		printf("file open error. \n");

	for (i=0; i<10;)
	{
		if (IsPrimeNumber(&A))
		{
			fprintDecimal(fp, A);
			i++;
		}

		ptrForFree = A.digit;
		A = PlusDigit(&A, 1);
		free(ptrForFree);
	}

	fclose(fp);

	return 0;
}
*/