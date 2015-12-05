////////////////////////////////////////////////////////////////////////////
// Developer Name	- SEHOON KIM
// Draft Date		- 2011.10.31 (Version 1.0.0)
// Description		- 'Big Number Operator' Header File
//					  This can be applied for Prime Number and RSA Crypto.
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

class BIG_BINARY;

//--------------------------------------------------------------------------
class BIG_DECIMAL {
public:
	unsigned char *digit;		//digit[0] is small position and digit[>0] is higher position.
	int size;					//the number of decimal digits. i.e. the size of 'digit[]' array.
	bool sign;					//if decimal is positive, then sign is 0. otherwise, sign is 1.

public:
	BIG_DECIMAL();
	BIG_DECIMAL(unsigned char* str, int length);	//create big decimal with decimal string
	BIG_DECIMAL(BIG_BINARY binary);					//change decimal to binary.

	bool IsPrimeNumber();							//return true if 'A' is prime number.
	BIG_DECIMAL Factorize();						//return the smallest number to factorize the input 'A'.

	void printOnConsole();							//print the input decimal on console.
	void printInFile(FILE *fp);						//print BIG_DECIMAL in a file
};

//--------------------------------------------------------------------------
class BIG_BINARY {
public:
	unsigned char *byte;		//the order format of 'byte' is same as java integer format.
	int size;					//the size of 'byte[]' array

public:
	BIG_BINARY();
	BIG_BINARY(unsigned char* bytes, int length);	//create big binary with byte
	BIG_BINARY(BIG_DECIMAL decimal);				//change binary to decimal.

	void printOnConsole();							//print the input decimal on console.
	void printInFile(FILE *fp);						//print BIG_BINARY in a file
};

//--------------------------------------------------------------------------
const BIG_DECIMAL operator +(BIG_DECIMAL A, BIG_DECIMAL B);			// '+'
const BIG_DECIMAL operator +(BIG_DECIMAL A, unsigned char digit);	//plus big number with a digit '0~9'.
const BIG_DECIMAL operator -(BIG_DECIMAL A, BIG_DECIMAL B);			// '-'
const BIG_DECIMAL operator -(BIG_DECIMAL A, unsigned char digit);	//minus big number with a digit '0~9'.
const BIG_DECIMAL operator *(BIG_DECIMAL A, BIG_DECIMAL B);			// '*'
const BIG_DECIMAL operator *(BIG_DECIMAL A, unsigned char digit);	//multiplay big number by a digit '0~9'.
const BIG_DECIMAL operator /(BIG_DECIMAL A, BIG_DECIMAL B);			// '/'
const BIG_DECIMAL operator %(BIG_DECIMAL A, BIG_DECIMAL M);			// '%'
const BIG_DECIMAL operator ^(BIG_DECIMAL A, BIG_DECIMAL E);			// '^' Exponent Operator
const bool operator ==(BIG_DECIMAL A, BIG_DECIMAL B);				//return true if 'A' == 'B'.
const bool operator >=(BIG_DECIMAL A, BIG_DECIMAL B);				//return true if 'A' >= 'B'.

//--------------------------------------------------------------------------
const BIG_DECIMAL MODULAR_EXPONENT(BIG_DECIMAL A, BIG_DECIMAL E, BIG_DECIMAL M);	// "A^X mod M"
const BIG_DECIMAL MinusAbsolute(BIG_DECIMAL A, BIG_DECIMAL B);		//returned value is always positive (i.e. A > B)
const void MinusForDivide(BIG_DECIMAL* A, BIG_DECIMAL* B);			//minus function to use only for divide
