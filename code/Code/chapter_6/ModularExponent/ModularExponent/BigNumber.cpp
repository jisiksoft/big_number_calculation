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

//--------------------------------------------------------------------------
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
void printDecimal(BIG_DECIMAL decimal)
{
	int i;

	if (decimal.sign)
		printf("-");
	for (i=decimal.size-1; i>=0; i--)
		printf("%c", decimal.digit[i]+48);
	printf("\n");
}

//--------------------------------------------------------------------------
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
//--------------------------------------------------------------------------
// plus the two input positive numbers 'A' and 'B'
// return "A + B"
BIG_DECIMAL PLUS(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;

	unsigned int min, max;

	BIG_DECIMAL* biggerNum = A->size > B->size ? A : B;	
	min = A->size > B->size ? B->size : A->size;
	max = A->size > B->size ? A->size : B->size;

	unsigned int size = max + 1;
	result.digit = (unsigned char*)malloc(size);				//create memory space to store result

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
		result.digit[size-1] = temp;
		result.size = size;
	}
	else
		result.size = size - 1;

	result.sign = 0;

	return result;
}

//--------------------------------------------------------------------------
// The input 'A' and 'B' are always positive.
// return "A - B"
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

//--------------------------------------------------------------------------
// return "A * B"
BIG_DECIMAL MULTIPLY(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result, temp, tempDigit;
	unsigned char * ptrTemp;

	result = CreateDecimal((unsigned char*)"0",1);		//initialize result as '0'

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

		free(tempDigit.digit);							//remove garbage memory space

		ptrTemp = result.digit;							//pointer to remove garbage memory space later
		result = PLUS(&result, &temp);
		free(ptrTemp);									//remove garbage memory space
	}
	free(temp.digit);

	return result;
}

//--------------------------------------------------------------------------
BIG_DECIMAL MODULAR_EXPONENT(BIG_DECIMAL* A, BIG_DECIMAL* E, BIG_DECIMAL* M)
{
	int i, j, position;
	unsigned char flag, *ptrForFree;
	BIG_DECIMAL result, temp;

	BIG_BINARY binaryE = GetBinary(E);

	result = CreateDecimal((unsigned char*)"1",1);
	temp = MultiplyDigit(A, 1);

	position = 8 * (binaryE.size - 1);

	j = 8;
	flag = 0x80;

	for (i=0; i<8; i++)
	{
		if (binaryE.byte[binaryE.size - 1] & flag)
		{
			position += j;
			break;
		}

		j--;
		flag >>= 1;
	}

	for (i=0; i<binaryE.size; i++)
	{
		flag = 0x01;

		for (j=0; j<8; j++)
		{
			if (binaryE.byte[i] & flag)
			{
				ptrForFree = result.digit;
				result = MULTIPLY(&result,&temp);
				free(ptrForFree);

				ptrForFree = result.digit;
				result = MODULAR(&result,M);
				free(ptrForFree);
			}

			position--;
			if (position == 0)
				break;

			ptrForFree = temp.digit;
			temp = MULTIPLY(&temp, &temp);
			free(ptrForFree);

			ptrForFree = temp.digit;
			temp = MODULAR(&temp,M);
			free(ptrForFree);

			flag <<= 1;
		}
	}

	return result;
}

//--------------------------------------------------------------------------
// return "A / B"
BIG_DECIMAL DIVIDE(BIG_DECIMAL* A, BIG_DECIMAL* B)
{
	BIG_DECIMAL result;
	int i, j, count;

	result.sign = 0;

	if (!IsBigger(A,B))							//if numerator is smaller than denominator, return '0'.
	{
		result = CreateDecimal((unsigned char*)"0",1);	//initialize result as '0'
		return result;
	}

	BIG_DECIMAL numerator;

	numerator.digit = (unsigned char*)malloc(A->size);
	numerator.size = A->size;

	for(i=0; i<numerator.size; i++)					//initialize numerator that is same as the input 'A'
		numerator.digit[i] = A->digit[i];

	i = A->size - B->size;							//the index 'i' for position of digit to write
	result.digit = (unsigned char*)malloc(i+1);

	for(j=0; j<=i; j++)								//initialize numerator that is same as the input 'A'
		result.digit[j] = 0x00;

	unsigned char* ptrForDigit = numerator.digit;
	numerator.digit += (numerator.size - B->size);
	numerator.size = B->size;

	while (i>=0)
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

		i--;
	}

	free(ptrForDigit);								//remove garbage memory space.

	i = A->size - B->size;							//the following is to get the exact size of result.
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
			result.digit[i] = A->digit[i] + 0x0A - B->digit[i] - temp;
			temp = 0x01;
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
			result.digit[i] = A->digit[i] + 0x0A - temp;
			temp = 0x01;
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
BIG_DECIMAL MultiplyDigit(BIG_DECIMAL* A, unsigned char digit)
{
	BIG_DECIMAL result;

	unsigned int size = A->size + 1;
	result.digit = (unsigned char*)malloc(size);

	int i = 0;
	unsigned char temp = 0;

	for (;i<A->size;i++) 
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

//--------------------------------------------------------------
BIG_DECIMAL GetDecimal(BIG_BINARY* binary)
{
	int i, j;
	unsigned char flag, *ptrForFree;

	BIG_DECIMAL decimal, temp;

	decimal = CreateDecimal((unsigned char*)"0",1);
	temp    = CreateDecimal((unsigned char*)"1",1);	

	for (i=0; i<binary->size; i++)
	{
		flag = 0x01;

		for (j=0; j<8; j++)
		{
			if (binary->byte[i] & flag)
			{
				ptrForFree = decimal.digit;
				decimal = PLUS(&decimal,&temp);
				free(ptrForFree);
			}
			flag <<= 1;

			ptrForFree = temp.digit;
			temp = MultiplyDigit(&temp, 0x02);
			free(ptrForFree);
		}
	}

	return decimal;
}

//--------------------------------------------------------------
BIG_BINARY GetBinary(BIG_DECIMAL* decimal)
{
	int i, j, position;
	BIG_BINARY binary;
	BIG_DECIMAL numerator, denominator, remainder, zero;

	binary.byte = (unsigned char*)malloc((int)(decimal->size / 2) + 1);
						
	numerator.digit = (unsigned char *)malloc(decimal->size);
	numerator.size = decimal->size;
	for(i=0; i<numerator.size; i++)
		numerator.digit[i] = decimal->digit[i];
					
	zero = CreateDecimal((unsigned char *)"0", 1);

    denominator = CreateDecimal((unsigned char *)"256", 3);

	for (position=0; ; position++)
	{
		remainder = MODULAR(&numerator, &denominator);

		void *ptrDigit = (void *)numerator.digit;
		numerator = DIVIDE(&numerator,&denominator);
		free(ptrDigit);

		binary.byte[position] = 0x00;

		for (i=0; i<remainder.size; i++)
		{
			unsigned char tempMultiply = 1;

			for (j=0; j<i; j++)
				tempMultiply *= 10;

			binary.byte[position] += remainder.digit[i] * tempMultiply;
		}

		if (IsEqual(&numerator, &zero))
			break;
	}

	binary.size = position + 1;

	free(numerator.digit);
	free(denominator.digit);
	free(remainder.digit);
	free(zero.digit);

	return binary;
}
