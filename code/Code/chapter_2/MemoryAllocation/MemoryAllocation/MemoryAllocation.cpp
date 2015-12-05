#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	char str[10] = "kimsehoon";
	char *ptrStr;

	printf("ptrStr Addr (before malloc) : %p\n", ptrStr);

	ptrStr = (char *)malloc(10);

	printf("ptrStr Addr (after malloc)  : %p\n", ptrStr);

	printf("ptrStr (before init) = %s \n", ptrStr);
	
	for (i=0; i<10; i++)
		ptrStr[i] = str[i];

	printf("ptrStr (after init)  = %s \n", ptrStr);
	
	free(ptrStr);

	printf("ptrStr (after free)  = %s \n", ptrStr);	
	printf("ptrStr Addr (after free)    : %p\n\n\n", &ptrStr);
}
