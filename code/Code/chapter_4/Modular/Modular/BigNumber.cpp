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
BIG_DECIMAL MODULAR(BIG_DECIMAL* A, BIG_DECIMAL* M)
{
	BIG_DECIMAL result;
	int i;

	result.digit = (unsigned char*)malloc(A->size);
	for (i=0; i<A->size; i++)
		result.digit[i] = A->digit[i];
	result.size = A->size;
	result.sign = 0;

	if (!IsBigger(A,M))
		return result;

	unsigned char* ptrForOrigin = result.digit;

	result.digit += (result.size - M->size);
	result.size = M->size;

	for (i=(A->size - M->size); i>=0; i--)
	{
		while (IsBigger(&result,M))
			MinusForDivide(&result,M);
		
		result.digit--;

		if (result.digit[result.size] != 0)
			result.size++;
	}
	
	result.digit = ptrForOrigin;

	i = A->size - 1;

	while (i>0)
	{
		if (result.digit[i] != 0x00)
			break;
		i--;
	}
	result.size = i+1;

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
