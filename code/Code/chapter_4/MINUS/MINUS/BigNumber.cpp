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
// The input 'A' and 'B' are always positive.
BIG_DECIMAL MINUS(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;

	if (IsBigger(A,B))
	{
		result = MinusAbsolute(A,B);
		result.sign = 0;
	}
	else
	{
		result = MinusAbsolute(B,A);
		result.sign = 1;
	}
	return result;
}

//--------------------------------------------------------------
// The input 'A' is always beigger than 'B'.
BIG_DECIMAL MinusAbsolute(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;

	result.digit = (unsigned char*)malloc(A->size);

	int i = 0;
	unsigned char temp = 0;

	for (;i<B->size;i++) 
	{
		if (A->digit[i] >= (B->digit[i] + temp))
		{
			result.digit[i] = A->digit[i] - B->digit[i] - temp;
			temp = 0;
		}
		else
		{
			result.digit[i] = A->digit[i] + 10 - B->digit[i] - temp;
			temp = 1;
		}
	}
	for (;i<A->size;i++)
	{
		if (A->digit[i] >= temp)
		{
			result.digit[i] = A->digit[i] - temp;
			temp = 0;
		}
		else
		{
			result.digit[i] = A->digit[i] + 10 - temp;
			temp = 1;
		}
	}

	result.size = A->size;

	while (!result.digit[i-1] && i>1)
	{
		result.size--;
		i--;
	}

	result.sign = 0;

	return result;
}

//--------------------------------------------------------------
BIG_DECIMAL MinusDigit(BIG_DECIMAL* A, unsigned char digit)
{
	BIG_DECIMAL result;

	result.digit = (unsigned char*)malloc(A->size);

	int i;
	unsigned char temp = 0x00;

	if (A->digit[0] >= digit)
		result.digit[0] = A->digit[0] - digit;
	else
	{
		result.digit[0] = A->digit[0] + 10 - digit;
		temp = 1;
	}

	for (i=1; i<A->size; i++)
	{
		if (A->digit[i] >= temp)
		{
			result.digit[i] = A->digit[i] - temp;
			temp = 0;
		}
		else
		{
			result.digit[i] = A->digit[i] + 10 - temp;
			temp = 1;
		}
	}

	result.size = A->size;

	while (!result.digit[i-1] && i>1)
	{
		result.size--;
		i--;
	}

	result.sign = false;

	return result;
}
