#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, B, result;

	A = CreateDecimal((unsigned char*)"11111",5);
	B = CreateDecimal((unsigned char*)"123",3);
	
	result = MULTIPLY(&A, &B);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"54321",5);

	result = MultiplyDigit(&A, 7);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"12345678901234567890",20);
	B = CreateDecimal((unsigned char*)"1234567890",10);
	
	result = MULTIPLY(&A, &B);
	printDecimal(result);
}
