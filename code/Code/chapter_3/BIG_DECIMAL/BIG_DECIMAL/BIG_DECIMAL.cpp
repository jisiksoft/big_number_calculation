#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------
struct BIG_DECIMAL {
	unsigned char *digit;
	int size;
	bool sign;
};

//--------------------------------------------------------------
BIG_DECIMAL CreateDecimal(unsigned char* str, int size)
{
	BIG_DECIMAL decimal;

	decimal.digit = (unsigned char*)malloc(size);
	for (int i=0; i<size; i++)
		decimal.digit[i] = str[size-i-1] - 48;

	decimal.size = size;
	decimal.sign = false;

	return decimal;
}

//--------------------------------------------------------------
void printDecimal(BIG_DECIMAL decimal)
{
	int i;

	if (decimal.sign)
		printf("-");
	for (i=decimal.size-1; i>=0; i--)
		printf("%c", decimal.digit[i]+48);
	printf("\n");
}

//--------------------------------------------------------------
void fprintDecimal(FILE *fp, BIG_DECIMAL decimal)
{
	int i;

	if (decimal.sign)
		fprintf(fp, "-");
	for (i=decimal.size-1; i>=0; i--)
		fprintf(fp, "%c", decimal.digit[i]+48);
	fprintf(fp, "\n");
}

//--------------------------------------------------------------
int main()
{
	BIG_DECIMAL decimal;

	decimal = CreateDecimal((unsigned char*)"4298250647",10);
	printDecimal(decimal);

	decimal = CreateDecimal((unsigned char*)"123456789012345678901234567890",30);
	printDecimal(decimal);

	decimal = CreateDecimal((unsigned char*)"0",1);
	printDecimal(decimal);

	FILE *fp;
	if ((fp=fopen("result.txt", "wt")) == NULL)
		printf("file open error. \n");

	fprintDecimal(fp, decimal);
	fclose(fp);
}
