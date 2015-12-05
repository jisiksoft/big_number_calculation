#include "BigNumber.h"
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, result, one;
	unsigned char *ptrForFree;

	A = CreateDecimal((unsigned char*)"1234567890",10);
	one = CreateDecimal((unsigned char*)"1",1);
	
	while(!IsEqual(&A, &one))
	{
		result = Factorize(&A);

		printDecimal(result);

		ptrForFree = A.digit;
		A = DIVIDE(&A, &result);
		free(ptrForFree);
		free(result.digit);
	}
}
