////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.08.21 (Version 1.0.0)
// Description    - RSA Crypto
//				    Big Number RSA Encryption/Decryption
////////////////////////////////////////////////////////////////////////////

#include "Cryptography.h"

//--------------------------------------------------------------------------------------------------
// "plain ^ e % publicKey"
BIG_DECIMAL RSAEncrypt(BIG_DECIMAL *plain, BIG_DECIMAL *e, BIG_DECIMAL *publicKey)
{
	return MODULAR_EXPONENT(plain, e, publicKey);
}

//--------------------------------------------------------------------------------------------------
// "cipher ^ secretKey % publicKey"
BIG_DECIMAL RSADecrypt(BIG_DECIMAL *cipher, BIG_DECIMAL *secretKey, BIG_DECIMAL *publicKey)
{
	return MODULAR_EXPONENT(cipher, secretKey, publicKey);
}

//--------------------------------------------------------------------------------------------------
// return Secret Key in RSA : "(e * S) % n = 1"
BIG_DECIMAL RSAGetSecretKey(BIG_DECIMAL *p, BIG_DECIMAL *q, BIG_DECIMAL *e)
{
	BIG_DECIMAL secretKey, temp, n, one;
	unsigned char *ptrForFree;
		
	one = CreateDecimal((unsigned char*)"1", 1);

	n = MULTIPLY(&MinusDigit(p,1),&MinusDigit(q,1));

	secretKey = DIVIDE(&n,e);

	temp = MULTIPLY(e,&secretKey); 

	for (;;)
	{
		ptrForFree = temp.digit;
		temp = MODULAR(&temp, &n);
		free(ptrForFree);

		if (IsEqual(&temp,&one))
			break;

		ptrForFree = secretKey.digit;
		secretKey = PlusDigit(&secretKey, 1);
		free(ptrForFree);

		ptrForFree = temp.digit;
		temp = PLUS(&temp, e);
		free(ptrForFree);

		//printDecimal(secretKey);
	}

	return secretKey;
}

//--------------------------------------------------------------------------------------------------
//return public key : "p * q"
BIG_DECIMAL RSAGetPublicKey(BIG_DECIMAL *prime1, BIG_DECIMAL *prime2)
{
	return MULTIPLY(prime1, prime2);					//p * q
}
