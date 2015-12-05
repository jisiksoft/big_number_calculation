#include "BigNumber.h"

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL A;
	BIG_BINARY B;

	A = CreateDecimal((unsigned char*)"12345678901234567890",20);
	B = GetBinary(&A);
	printBinary(B);
	
	unsigned char data[9] = { 0x10, 0x35, 0xb3, 0x7f, 0x94, 0xa9, 0x7e, 0x11, 0x93 };

	B = CreateBinary(data,sizeof(data));
	A = GetDecimal(&B);
	printDecimal(A);
}
