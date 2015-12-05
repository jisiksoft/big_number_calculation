#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------
struct BIG_BINARY {
	unsigned char *byte;
	int size;
};

//--------------------------------------------------------------
BIG_BINARY CreateBinary(unsigned char* bytes, int length)
{
	BIG_BINARY binary;

	binary.byte = (unsigned char*)malloc(length);
	for (int i=0; i<length; i++)
		binary.byte[i] = bytes[length-i-1];

	binary.size = length;

	return binary;
}

//--------------------------------------------------------------
void printBinary(BIG_BINARY binary)
{
	int i, j;
	unsigned char flag;

	for (i=binary.size-1; i>=0; i--)
	{
		flag = 0x80;

		for (j=0; j<8; j++)
		{
			if (binary.byte[i] & flag)
				printf("1");
			else
				printf("0");

			flag >>= 1;
		}
	}
	printf("\n");
}

//--------------------------------------------------------------
void fprintBinary(FILE *fp, BIG_BINARY binary)
{
	int i, j;
	unsigned char flag;

	for (i=binary.size-1; i>=0; i--)
	{
		flag = 0x80;

		for (j=0; j<8; j++)
		{
			if (binary.byte[i] & flag)
				fprintf(fp, "1");
			else
				fprintf(fp, "0");

			flag >>= 1;
		}
	}
	fprintf(fp, "\n");
}

//--------------------------------------------------------------
int main()
{
	BIG_BINARY binary;
	
	int bytes = -1;
	binary = CreateBinary((unsigned char *) &bytes, 4);
	printBinary(binary);

	char str[9] = { 0x10, 0x35, 0xb3, 0x7f, 0x94, 0xa9, 0x7e, 0x11, 0x93 };
	binary = CreateBinary((unsigned char *) str, 9);
	printBinary(binary);
}
