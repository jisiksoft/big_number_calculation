#include "Cryptography.h"


//-----------------------------------------------------------------------------
// RSA Test 3
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"1572509", 7);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"94837289", 8);
	BIG_DECIMAL e = CreateDecimal((unsigned char*)"94837274098213", 14);

	BIG_DECIMAL plain = CreateDecimal((unsigned char*)"123456789012345",15);
	
	printf("plain          : ");
	printDecimal(plain);

	printf("prime number 1 : ");
	printDecimal(p);
	printf("prime number 2 : ");
	printDecimal(q);

	printf("public key     : ");
	BIG_DECIMAL publicKey = RSAGetPublicKey(&p,&q);
	printDecimal(publicKey);
	
	printf("encrypted      : ");
	BIG_DECIMAL cipher = RSAEncrypt(&plain, &e, &publicKey);
	printDecimal(cipher);
	
	printf("secret key     : ");
	BIG_DECIMAL secretKey = RSAGetSecretKey(&p, &q, &e);
	printDecimal(secretKey);

	printf("decrypted      : ");
	BIG_DECIMAL result = RSADecrypt(&cipher, &secretKey, &publicKey);
	printDecimal(result);
	
	return 0;
}


/*
//-----------------------------------------------------------------------------
// RSA Test 2
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"2269",4);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"2347",4);
	BIG_DECIMAL e = CreateDecimal((unsigned char*)"2833",4);

	BIG_DECIMAL plain = CreateDecimal((unsigned char*)"1234567",7);
	
	printf("plain          : ");
	printDecimal(plain);

	printf("prime number 1 : ");
	printDecimal(p);
	printf("prime number 2 : ");
	printDecimal(q);

	printf("public key     : ");
	BIG_DECIMAL publicKey = RSAGetPublicKey(&p,&q);
	printDecimal(publicKey);
	
	printf("encrypted      : ");
	BIG_DECIMAL cipher = RSAEncrypt(&plain, &e, &publicKey);
	printDecimal(cipher);
	
	printf("secret key     : ");
	BIG_DECIMAL secretKey = RSAGetSecretKey(&p, &q, &e);
	printDecimal(secretKey);

	printf("decrypted      : ");
	BIG_DECIMAL result = RSADecrypt(&cipher, &secretKey, &publicKey);
	printDecimal(result);
	
	return 0;
}
*/

/*
//-----------------------------------------------------------------------------
// RSA Test 1
int main()
{
	BIG_DECIMAL p = CreateDecimal((unsigned char*)"29",2);
	BIG_DECIMAL q = CreateDecimal((unsigned char*)"11",2);
	BIG_DECIMAL e = CreateDecimal((unsigned char*)"17",2);

	BIG_DECIMAL plain = CreateDecimal((unsigned char*)"131",3);
	
	printf("plain          : ");
	printDecimal(plain);

	printf("prime number 1 : ");
	printDecimal(p);
	printf("prime number 2 : ");
	printDecimal(q);

	printf("public key     : ");
	BIG_DECIMAL publicKey = RSAGetPublicKey(&p,&q);
	printDecimal(publicKey);
	
	printf("encrypted      : ");
	BIG_DECIMAL cipher = RSAEncrypt(&plain, &e, &publicKey);
	printDecimal(cipher);
	
	printf("secret key     : ");
	BIG_DECIMAL secretKey = RSAGetSecretKey(&p, &q, &e);
	printDecimal(secretKey);

	printf("decrypted      : ");
	BIG_DECIMAL result = RSADecrypt(&cipher, &secretKey, &publicKey);
	printDecimal(result);
	
	return 0;
}
*/