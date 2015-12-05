#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, B, result;

	A = CreateDecimal((unsigned char*)"10005690",8);
	B = CreateDecimal((unsigned char*)"6923",4);
	
	result = MINUS(&A, &B);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"10104",5);

	result = MinusDigit(&A, 7);
	printDecimal(result);
}
