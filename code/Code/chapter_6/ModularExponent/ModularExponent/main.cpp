#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A, E, M, result;

	A = CreateDecimal((unsigned char*)"12345",5);
	E = CreateDecimal((unsigned char*)"97",2);
	M = CreateDecimal((unsigned char*)"23456",5);
	
	result = MODULAR_EXPONENT(&A, &E, &M);

	printDecimal(result);
}
