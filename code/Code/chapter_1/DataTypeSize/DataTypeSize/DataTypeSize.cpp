#include <stdio.h>

int main()
{
	int *pointer;

	printf("Data Type Size\n");

	printf("char      : %d \n", sizeof(char));
	printf("int       : %d \n", sizeof(int));
	printf("long      : %d \n", sizeof(long));
	printf("long long : %d \n", sizeof(long long));
	printf("float     : %d \n", sizeof(float));
	printf("double    : %d \n", sizeof(double));
	printf("pointer   : %d \n", sizeof(pointer));
}
