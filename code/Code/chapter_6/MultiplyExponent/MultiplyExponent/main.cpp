#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, E, result;

	A = CreateDecimal((unsigned char*)"12345",5);
	E = CreateDecimal((unsigned char*)"97",2);
	
	result = MULTIPLY_EXPONENT(&A,&E);

	printDecimal(result);
}
