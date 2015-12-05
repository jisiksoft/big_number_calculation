#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, B, result;

	A = CreateDecimal((unsigned char*)"51359",5);
	B = CreateDecimal((unsigned char*)"99962763",8);
	
	result = PLUS(&A, &B);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"99995",5);

	result = PlusDigit(&A, 7);
	printDecimal(result);
}
