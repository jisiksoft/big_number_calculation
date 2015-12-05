#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, B, result;

	A = CreateDecimal((unsigned char*)"241",3);
	B = CreateDecimal((unsigned char*)"11",2);
	
	result = DIVIDE(&A, &B);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"456789",6);
	B = CreateDecimal((unsigned char*)"123",3);
	
	result = DIVIDE(&A, &B);
	printDecimal(result);

	A = CreateDecimal((unsigned char*)"123456789012345678901234567890",30);
	B = CreateDecimal((unsigned char*)"1234567890",10);
	
	result = DIVIDE(&A, &B);
	printDecimal(result);
}
