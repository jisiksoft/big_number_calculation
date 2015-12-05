#include "BigNumber.h"
#include "stdio.h"
#include <time.h>

/*
//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"2",1);
	BIG_DECIMAL N = CreateDecimal((unsigned char*)"31",2);
	BIG_DECIMAL one = CreateDecimal((unsigned char*)"1", 1);

	BIG_DECIMAL result = MINUS(&(MULTIPLY_EXPONENT(&A, &N)), &one);

	if (IsPrimeNumber(&result))
		printf("2^31 - 1 is Prime Number.\n");
	else
		printf("Not Prime Number.\n");
}
*/

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"2",1);
	BIG_DECIMAL N = CreateDecimal((unsigned char*)"43112609",8);
	BIG_DECIMAL one = CreateDecimal((unsigned char*)"1", 1);

	time_t now;
	time(&now);
	printf("Starting...\n%s", ctime(&now));

	BIG_DECIMAL result = MINUS(&(MULTIPLY_EXPONENT(&A, &N)), &one);

	time(&now);
	printf("Calculation is Finished.\n%s", ctime(&now));

	FILE *fp;
	if ((fp=fopen("result.txt", "wt"))==NULL)
		printf("file open error. \n");

	fprintDecimal(fp, result);

	fclose(fp);
}
