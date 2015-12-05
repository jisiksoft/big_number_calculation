#include <stdio.h>
#include <stdlib.h>

#include "BigNumber.h"

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
BIG_DECIMAL PLUS(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;

	unsigned int min, max;

	BIG_DECIMAL* biggerNum = A->size > B->size ? A : B;	
	min = A->size > B->size ? B->size : A->size;
	max = A->size > B->size ? A->size : B->size;

	unsigned int size = max + 1;
	result.digit = (unsigned char*)malloc(size);

	unsigned int i = 0;
	unsigned char temp = 0;

	for (;i<min;i++) 
	{
		result.digit[i] = A->digit[i] + B->digit[i] + temp;
		if (result.digit[i] > 0x09)
			temp = 0x01;
		else
			temp = 0x00;
		result.digit[i] %= 0x0A;
	}
	for (;i<max;i++)
	{
		result.digit[i] = biggerNum->digit[i] + temp;
		if (result.digit[i] > 0x09)
			temp = 0x01;
		else
			temp = 0x00;
		result.digit[i] %= 0x0A;
	}

	if (temp)
	{
		result.digit[i] = temp;
		result.size = size;
	}
	else
		result.size = size - 1;

	result.sign = 0;

	return result; 
}

//--------------------------------------------------------------
BIG_DECIMAL PlusDigit(BIG_DECIMAL* A, unsigned char digit)
{
	BIG_DECIMAL result;

	unsigned int size = A->size + 1;
	result.digit = (unsigned char*)malloc(size);

	int i;
	unsigned char temp;

	result.digit[0] = A->digit[0] + digit;
	temp = result.digit[0] / 0x0A;
	result.digit[0] %= 0x0A;
	
	for (i=1;i<A->size;i++) 
	{
		result.digit[i] = A->digit[i] + temp;			
		temp = result.digit[i] / 0x0A;
		result.digit[i] %= 0x0A;
	}

	if (temp)
	{
		result.digit[i] = temp;
		result.size = size;
	}
	else
		result.size = A->size;

	result.sign = A->sign;

	return result;
}
