#include "BigNumber.h"
#include "stdio.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"31",2);
	
	printDecimal(A);

	if (IsPrimeNumber(&A))
		printf("is Prime Number.\n\n");
	else
		printf("is Not Prime Number.\n\n");
}
