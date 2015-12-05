////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.10.31 (Version 1.0.0)
// Description    - Big Number Calculation
//				    This can be applied for Prime Number and RSA Crypto
////////////////////////////////////////////////////////////////////////////

/*
#include "BigNumber.h"

//-----------------------------------------------------------------------------
// Big Number Operator Test
int main()
{
	BIG_DECIMAL A = BIG_DECIMAL((unsigned char*)"12345678901234567890",20);
	BIG_DECIMAL B = BIG_DECIMAL((unsigned char*)"255",3);
	BIG_DECIMAL C = BIG_DECIMAL((unsigned char*)"134",3);

	
	A.printOnConsole();
	B.printOnConsole();
	C.printOnConsole();

	printf("\nPlus :\n");
	BIG_DECIMAL R1 = A + B;
	R1.printOnConsole();

	printf("\nMinus :\n");
	BIG_DECIMAL R2 = A - B;
	R2.printOnConsole();

	printf("\nMultiply :\n");
	BIG_DECIMAL R3 = A * B;	
	R3.printOnConsole();

	printf("\nDivide :\n");
	BIG_DECIMAL R4 = A / B;
	R4.printOnConsole();

	printf("\nModular :\n");
	BIG_DECIMAL R5 = A % B;
	R5.printOnConsole();

	printf("\MODULAR_EXPONENT :\n");
	BIG_DECIMAL R7 = MODULAR_EXPONENT(A,B,C);
	R7.printOnConsole();

	BIG_BINARY bin = BIG_BINARY(A);
	bin.printOnConsole();

	BIG_DECIMAL R100 = BIG_DECIMAL(bin);
	R100.printOnConsole();

	return 0;
}
*/

/*
#include "BigNumber.h"

//-----------------------------------------------------------------------------
// Big Number Operator Test
int main()
{
	FILE *fp;
	if ((fp=fopen("result.txt", "wt"))==NULL)
		printf("file open error. \n");

	BIG_BINARY bin;
	bin.byte = (unsigned char*)malloc(32);
	for(int i=0; i<32; i++)
		bin.byte[i] = 0xFF;
	bin.size = 32;

	BIG_DECIMAL dec = BIG_DECIMAL(bin);

	dec.printInFile(fp);

	bin = BIG_BINARY(dec);

	bin.printInFile(fp);

    fclose(fp);
}
*/

/*
#include "BigNumber.h"

//-----------------------------------------------------------------------------
// Prime Number
int main()
{
	BIG_DECIMAL p = BIG_DECIMAL((unsigned char*)"97",2);

	if (p.IsPrimeNumber())
	{
		p.printOnConsole();
		printf("is Prime Number. \n");
	}

	return 0;
}
*/

/*
#include "BigNumber.h"
#include <time.h>

//-----------------------------------------------------------------------------
// Mersenne Prime
int main()
{
	BIG_DECIMAL X = BIG_DECIMAL((unsigned char*)"2",1);
	BIG_DECIMAL E = BIG_DECIMAL((unsigned char*)"31",2);
	
	time_t now;
	time(&now);
	printf("%s \nMersenne Number Calculating...\n\n", ctime(&now));

	BIG_DECIMAL result = (X ^ E) - 1;

	time(&now);
	printf("%s\n", ctime(&now));

	result.printOnConsole();

	if (result.IsPrimeNumber())
	{
		printf("\nn = ");
		E.printOnConsole();
		printf("Is Mersenne Prime Exponent.\n\n");
	}
	else
	{
		printf("\nn = ");
		E.printOnConsole();
		printf("is Not Mersenne Prime Exponent.\n\n");
	}

	time(&now);
	printf("%s\n", ctime(&now));

	return 0;
}
*/

/*
#include "BigNumber.h"

//-----------------------------------------------------------------------------
// Print Prime Number in File

int main()
{
	BIG_DECIMAL A = BIG_DECIMAL((unsigned char*)"1572509",7);

	int i;
	unsigned char *ptrForFree;

	FILE *fp;

	if ((fp=fopen("prime.txt", "wt"))==NULL)
		printf("file open error. \n");

	for (i=0; i<1;)
	{
		if (A.IsPrimeNumber())
		{
			A.printInFile(fp);

			putc('\n', fp);
			i++;
		}

		ptrForFree = A.digit;
		A = A + 0x01;
		free(ptrForFree);
	}

    fclose(fp);

	return 0;
}
*/

/*
#include "BigNumber.h"

//-----------------------------------------------------------------------------
// the maximum number in 1024 bits
int main()
{
	BIG_DECIMAL dec = BIG_DECIMAL((unsigned char*)"2",1);

	for (int i=0; i<10; i++)
		dec = dec * dec;

	dec = dec - 1;

	dec.printOnConsole();

	BIG_BINARY bin = BIG_BINARY(dec);
	bin.printOnConsole();

	FILE *fp;

	if ((fp=fopen("1024bit.txt", "wt"))==NULL)
		printf("file open error. \n");

	dec.printInFile(fp);

	fclose(fp);

	return 0;
}
*/

/*
#include "BigNumber.h"
#include <time.h>

//-----------------------------------------------------------------------------
// "X ^ Y mod M" Test
int main()
{
	BIG_DECIMAL p = BIG_DECIMAL((unsigned char*)"4298250647",10);
	BIG_DECIMAL q = BIG_DECIMAL((unsigned char*)"62982591643",11);

	printf("M : \n");
	BIG_DECIMAL M = p * q;
	M.printOnConsole();

	BIG_DECIMAL Y = BIG_DECIMAL((unsigned char*)"623982591637",12);
	BIG_DECIMAL X = BIG_DECIMAL((unsigned char*)"12345678901234567890",20);

	time_t now;
	time(&now);
	printf("\n%s", ctime(&now));

	printf("\nX ^ Y mod M : \n");
	BIG_DECIMAL result = MODULAR_EXPONENT(X, Y, M);
	result.printOnConsole();

	time(&now);
	printf("\n%s", ctime(&now));

	return 0;
}
*/


#include "BigNumber.h"

//-----------------------------------------------------------------------------
// Factorization Test
int main()
{
	BIG_DECIMAL A, result, one;
	BIG_DECIMAL *ptrForFree;

	A = BIG_DECIMAL((unsigned char*)"1234567890",10);
	one = BIG_DECIMAL((unsigned char*)"1",1);
	
	while(!(A == one))
	{
		result = A.Factorize();

		result.printOnConsole();

		A = A / result;
	}
}


/*
#include "Cryptography.h"

//-----------------------------------------------------------------------------
// RSA Test
int main()
{
	BIG_DECIMAL p = BIG_DECIMAL((unsigned char*)"2269",4);
	BIG_DECIMAL q = BIG_DECIMAL((unsigned char*)"2347",4);
	BIG_DECIMAL e = BIG_DECIMAL((unsigned char*)"2833",4);

	BIG_DECIMAL plain = BIG_DECIMAL((unsigned char*)"1234567",7);
	
	printf("plain      : ");
	plain.printOnConsole();

	printf("public key : ");
	BIG_DECIMAL publicKey = RSA::GetPublicKey(p, q);					//get public key
	publicKey.printOnConsole();
	
	printf("encrypted  : ");
	BIG_DECIMAL cipher = RSA::Encrypt(plain, e, publicKey);			//Encrypt in RSA
	cipher.printOnConsole();
	
	printf("secret key : ");
	BIG_DECIMAL secretKey = RSA::GetSecretKey(p, q, e);				//solve secret key
	secretKey.printOnConsole();

	printf("decrypted  : ");
	BIG_DECIMAL result = RSA::Decrypt(cipher, secretKey, publicKey);	//Decrypt in RSA
	result.printOnConsole();

	return 0;
}
*/
