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
bool IsEqual(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	if (A->size != B->size)
		return false;

	for (int i=0; i<A->size; i++)
		if (A->digit[i] != B->digit[i])
			return false;

	return true;
}

//--------------------------------------------------------------
bool IsBigger(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	int i;

	if (A->size > B->size)
		return true;
	else if (A->size < B->size)
		return false;
	else
	{
		for (i=A->size-1; i>=0; i--)
		{
			if (A->digit[i] > B->digit[i])
				return true;
			else if (A->digit[i] < B->digit[i])
				return false;
		}
	}

	return true;
}

//--------------------------------------------------------------
BIG_DECIMAL MULTIPLY(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result, temp, tempDigit;
	unsigned char * ptrTemp;

	result = CreateDecimal((unsigned char*)"0",1);

	temp.digit = (unsigned char*)malloc(A->size + B->size);

	int i, j;

	for (i=0; i<B->size; i++)
	{
		tempDigit = MultiplyDigit(A, B->digit[i]);
		
		for (j=0; j<i; j++)
			temp.digit[j] = 0x00;
		for (; j<tempDigit.size+i; j++)
			temp.digit[j] = tempDigit.digit[j-i];
		temp.size = tempDigit.size+i;

		free(tempDigit.digit);

		ptrTemp = result.digit;
		result = PLUS(&result, &temp);
		free(ptrTemp);
	}
	free(temp.digit);

	return result;
}

//--------------------------------------------------------------
BIG_DECIMAL MultiplyDigit(BIG_DECIMAL* A, unsigned char digit)
{
	BIG_DECIMAL result;

	unsigned int size = A->size + 1;
	result.digit = (unsigned char*)malloc(size);

	int i;
	unsigned char temp = 0;

	for (i=0;i<A->size;i++) 
	{
		result.digit[i] = (A->digit[i] * digit) + temp;

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

	result.sign = false;

	return result;
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
