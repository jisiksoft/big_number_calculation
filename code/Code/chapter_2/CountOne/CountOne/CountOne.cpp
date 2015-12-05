///////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.10.27
// Description    - Count '1' bits in "unsigned int"
//				    How to use bit operators
///////////////////////////////////////////////////////

#include "stdio.h"

//-----------------------------------------------
//return the total number of '1' bits in the input
int countOne(unsigned int input)
{
	unsigned int i, count, flag;

	count = 0;
	flag  = 0x00000001;

	for (i=0; i<32; i++)
	{
		if (input & flag)		//if there is 1 bit on the specific position,
			count++;			//then increase count

		flag <<= 1;				//move the only '1' bit to the left one bit
	}
	
	return count;
}

//-----------------------------------------------
int main()
{
	printf("%8d : %2d\n", 8, countOne(8));
	printf("%8d : %2d\n", 1234, countOne(1234));
	printf("%8d : %2d\n", 12345678, countOne(12345678));
}
