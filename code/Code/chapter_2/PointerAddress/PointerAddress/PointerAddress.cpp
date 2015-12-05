///////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.10.27
// Description    - Check Pointer Address
//				    What is one pointer & double pointer?
///////////////////////////////////////////////////////

#include <stdio.h>

int main()
{
	char **ptrDouble, *ptrOne, ch = 'A';

	ptrOne = &ch;
	ptrDouble = &ptrOne;

	printf("ptrDouble address : 0x%p \n\n", &ptrDouble);

	printf("ptrDouble value : 0x%p \n",   ptrDouble);
	printf("ptrOne  address : 0x%p \n\n", &ptrOne);

	printf("ptrOne    value : 0x%p \n",   ptrOne);
	printf("ch      address : 0x%p \n\n", &ch);

	printf("**ptrDouble value: %c \n",   **ptrDouble);
	printf(" *ptrOne    value: %c \n",   *ptrOne);
	printf("  ch        value: %c \n\n", ch);
}
