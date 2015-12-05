////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.08.22 (Version 1.0.0)
// Description    - Big Number Calculation
//				    This can be applied for Prime Number and RSA Crypto
////////////////////////////////////////////////////////////////////////////

/*
#include "Cryptography.h"
#include <time.h>

//-----------------------------------------------------------------------------
// the maximum number in 64 bits
int main()
{
	BIG_DECIMAL byte = CreateDecimal((unsigned char*)"256",3);

	printf("byte : \n");
	BIG_DECIMAL *temp = &byte;
	
	for (int i=0; i<3; i++)
		*temp = MULTIPLY(temp,temp);

	printDecimal(*temp);

	return 0;
}
*/

/*
//-----------------------------------------------------------------------------
// "X ^ Y mod M" Test
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"4298250647",10);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"62982591643",11);

	printf("M : \n");
	BIG_DECIMAL M = MULTIPLY(&p,&q);
	printDecimal(M);

	//BIG_DECIMAL Y = CreateDecimal((unsigned char*)"623982591637",12);
	//BIG_DECIMAL X = CreateDecimal((unsigned char*)"12345678901234567890",20);
	BIG_DECIMAL Y = CreateDecimal((unsigned char*)"6239825916371234567890",22);
	BIG_DECIMAL X = CreateDecimal((unsigned char*)"1234567890123456789012",22);

	time_t now;
	time(&now);
	printf("\n%s", ctime(&now));

	printf("\nX ^ Y mod M : \n");
	printDecimal(MODULAR_EXPONENT(&X, &Y, &M));

	time(&now);
	printf("\n%s", ctime(&now));

	return 0;
}
*/

/*
#include "Cryptography.h"

//-----------------------------------------------------------------------------
// Factorization Test
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"4223",4);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"422819",6);

	BIG_DECIMAL temp = Factorize(&MULTIPLY(&p,&q));

	if (temp.size == 0)
		printf("No Output in Factorization\n");
	else
		printDecimal(temp);
	
	return 0;
}
*/

/*
#include "Cryptography.h"

//-----------------------------------------------------------------------------
// RSA Test
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"2269",4);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"2347",4);
	BIG_DECIMAL e = CreateDecimal((unsigned char*)"2833",4);

	BIG_DECIMAL plain = CreateDecimal((unsigned char*)"1234567",7);
	
	printf("plain : ");
	printDecimal(plain);

	printf("\npublic key : ");
	BIG_DECIMAL publicKey = RSAGetPublicKey(&p,&q);					//get public key
	printDecimal(publicKey);
	
	printf("\nencrypted : ");
	BIG_DECIMAL cipher = RSAEncrypt(&plain, &e, &publicKey);			//Encrypt in RSA
	printDecimal(cipher);
	
	printf("\nsecret key : ");
	BIG_DECIMAL secretKey = RSAGetSecretKey(&p, &q, &e);				//solve secret key
	printDecimal(secretKey);

	printf("\ndecrypted : ");
	BIG_DECIMAL result = RSADecrypt(&cipher, &secretKey, &publicKey);	//Decrypt in RSA
	printDecimal(result);
	printf("\n");
	
	return 0;
}
*/


#include "BigNumberOperator.h"

//-----------------------------------------------------------------------------
// Big Prime Number Test
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"4382591627",10);

	int i, j;
	unsigned char *ptrForFree;

	FILE *fp;

	if ((fp=fopen("prime.txt", "wt"))==NULL)
		printf("file open error. \n");

	for (i=0; i<10;)
	{
		if (IsPrimeNumber(&A))
		{
			for (j=A.size-1; j>=0; j--)
			{
				fprintf(fp, "%c", A.digit[j] + 48);
			}

			putc('\n', fp);
			i++;
		}

		ptrForFree = A.digit;
		A = PlusDigit(&A,0x01);
		free(ptrForFree);
	}

	fclose(fp);

	return 0;
}


/*
#include "BigNumberOperator.h"

//-----------------------------------------------------------------------------
// Big Number Operator Test
int main()
{
	BIG_DECIMAL A = CreateDecimal((unsigned char*)"12345678901234567890",20);
	BIG_DECIMAL B = CreateDecimal((unsigned char*)"255",3);
	BIG_DECIMAL C = CreateDecimal((unsigned char*)"134",3);

	printDecimal(A);
	printDecimal(B);
	printDecimal(C);

	printf("\nPlus :\n");
	BIG_DECIMAL R1 = PLUS(&A, &B);
	printDecimal(R1);

	printf("\nMinus :\n");
	BIG_DECIMAL R2 = MINUS(&A, &B);
	printDecimal(R2);

	printf("\nMultiply :\n");
	BIG_DECIMAL R3 = MULTIPLY(&A, &B);	
	printDecimal(R3);

	printf("\nDivide :\n");
	BIG_DECIMAL R4 = DIVIDE(&A, &B);
	printDecimal(R4);

	printf("\nModular :\n");
	BIG_DECIMAL R5 = MODULAR(&A, &B);
	printDecimal(R5);

	printf("\MODULAR_EXPONENT :\n");
	BIG_DECIMAL R7 = MODULAR_EXPONENT(&A,&B,&C);
	printDecimal(R7);

	BIG_BINARY bin = GetBinary(&A);
	printBinary(bin);

	BIG_DECIMAL R100 = GetDecimal(&bin);
	printDecimal(R100);

	return 0;
}
*/

/*
#include "BigNumberOperator.h"

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

	BIG_DECIMAL dec;
	dec = GetDecimal(&bin);

	fprintDecimal(fp, dec);
	fprintBinary(fp, GetBinary(&dec));

    fclose(fp);
}
*/

