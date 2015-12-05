////////////////////////////////////////////////////////////////////////////
// Developer Name	- SEHOON KIM
// Draft Date		- 2011.07.24 (Version 1.0.0)
// Description		- 'Big Number Operator' Header File
//					  This can be applied for Prime Number and RSA Crypto
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------
struct BIG_DECIMAL {
	unsigned char *digit;		//digit[0] is small position and digit[>0] is higher position.
	int size;					//the number of decimal digits. i.e. the size of 'digit[]' array.
	bool sign;					//if decimal is positive, then sign is 0. otherwise, sign is 1.
};

//--------------------------------------------------------------------------
struct BIG_BINARY {
	unsigned char *byte;		//the order format of 'byte' is same as java integer format.
	int size;					//the size of 'byte[]' array
};

//--------------------------------------------------------------------------
BIG_DECIMAL PLUS(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '+'
BIG_DECIMAL MINUS(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '-'
BIG_DECIMAL MULTIPLY(BIG_DECIMAL* A, BIG_DECIMAL* B);			// '*'
BIG_DECIMAL DIVIDE(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '/'
BIG_DECIMAL MODULAR(BIG_DECIMAL* A, BIG_DECIMAL* M);			// '%'
BIG_DECIMAL MULTIPLY_EXPONENT(BIG_DECIMAL* A, BIG_DECIMAL* E);	// '^'
BIG_DECIMAL MODULAR_EXPONENT(BIG_DECIMAL* A, BIG_DECIMAL* E, BIG_DECIMAL* M);	// "A^E mod M"

//--------------------------------------------------------------------------
bool IsEqual(BIG_DECIMAL* A, BIG_DECIMAL* B);					//return true if 'A' == 'B'.
bool IsBigger(BIG_DECIMAL* A, BIG_DECIMAL* B);					//return true if 'A' >= 'B'.
bool IsPrimeNumber(BIG_DECIMAL* A);								//return true if 'A' is prime number.
BIG_DECIMAL Factorize(BIG_DECIMAL* A);							//return the smallest number to factorize the input 'A'.
BIG_DECIMAL MinusAbsolute(BIG_DECIMAL* A, BIG_DECIMAL* B);		//returned value is always positive (i.e. A > B)
BIG_DECIMAL PlusDigit(BIG_DECIMAL* A, unsigned char digit);		//plus big number with a digit '0~9'.
BIG_DECIMAL MinusDigit(BIG_DECIMAL* A, unsigned char digit);	//minus big number with a digit '0~9'.
BIG_DECIMAL MultiplyDigit(BIG_DECIMAL* A, unsigned char digit); //multiplay big number by a digit '0~9'.
void MinusForDivide(BIG_DECIMAL* A, BIG_DECIMAL* B);            //minus function to use only for divide

//--------------------------------------------------------------------------
BIG_DECIMAL CreateDecimal(unsigned char* str, int size);		//create big decimal with decimal string
BIG_BINARY CreateBinary(unsigned char* bytes, int length);		//create big binary with byte

//--------------------------------------------------------------------------
BIG_BINARY GetBinary(BIG_DECIMAL* decimal);						//change decimal to binary.
BIG_DECIMAL GetDecimal(BIG_BINARY* binary);						//change binary to decimal.

//--------------------------------------------------------------------------
void printDecimal(BIG_DECIMAL decimal);							//print the input decimal on console.
void printBinary(BIG_BINARY binary);							//print the input decimal on console.
void fprintDecimal(FILE *fp, BIG_DECIMAL decimal);				//print BIG_DECIMAL in a file
void fprintBinary(FILE *fp, BIG_BINARY binary);					//print BIG_BINARY in a file
