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
BIG_DECIMAL DIVIDE(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;
	int i, j, count;

	if (!IsBigger(A,B))
	{
		result = CreateDecimal((unsigned char*)"0",1);
		return result;
	}

	BIG_DECIMAL numerator;

	numerator.digit = (unsigned char*)malloc(A->size);
	numerator.size = A->size;

	for(i=0; i<numerator.size; i++)
		numerator.digit[i] = A->digit[i];

	i = A->size - B->size;
	result.digit = (unsigned char*)malloc(i+1);

	for(j=0; j<=i; j++)
		result.digit[j] = 0x00;

	unsigned char* ptrForOrigin = numerator.digit;
	numerator.digit += (numerator.size - B->size);
	numerator.size = B->size;

	for (; i>=0; i--)
	{
		count = 0;

		while (IsBigger(&numerator,B))
		{
			count++;
			MinusForDivide(&numerator,B);
		}
		result.digit[i] = (unsigned char)count;

		numerator.digit--;

		if (numerator.digit[numerator.size] != 0x00)
			numerator.size++;
	}

	free(ptrForOrigin);

	i = A->size - B->size;

	for (; i>0; i--)
		if (result.digit[i] != 0x00)
			break;

	result.size = i + 1;
	result.sign = 0;

	return result;
}

//--------------------------------------------------------------
void MinusForDivide(BIG_DECIMAL* A, BIG_DECIMAL* B)
{	
	int i;
	unsigned char temp = 0;

	for (i=0; i<B->size; i++) 
	{
		if (A->digit[i] >= (B->digit[i] + temp))
		{
			A->digit[i] = A->digit[i] - B->digit[i] - temp;
			temp = 0;
		}
		else
		{
			A->digit[i] = A->digit[i] + 0x0A - B->digit[i] - temp;
			temp = 0x01;
		}
	}
	for (;i<A->size;i++)
	{
		if (A->digit[i] >= temp)
		{
			A->digit[i] = A->digit[i] - temp;
			temp = 0;
		}
		else
		{
			A->digit[i] = A->digit[i] + 0x0A - temp;
			temp = 0x01;
		}
	}

	while (!A->digit[i-1] && i>1)
	{
		A->size--;
		i--;
	}
}
