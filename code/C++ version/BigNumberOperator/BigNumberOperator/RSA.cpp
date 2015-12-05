////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.08.21 (Version 1.0.0)
// Description    - RSA Crypto
//				    Big Number RSA Encryption/Decryption
////////////////////////////////////////////////////////////////////////////

#include "Cryptography.h"

//--------------------------------------------------------------------------------------------------
// "t ^ e mod pq"
BIG_DECIMAL RSA::Encrypt(BIG_DECIMAL plain, BIG_DECIMAL e, BIG_DECIMAL publicKey)
{
	return MODULAR_EXPONENT(plain, e, publicKey);
}

//--------------------------------------------------------------------------------------------------
// "c ^ s mod pq"
BIG_DECIMAL RSA::Decrypt(BIG_DECIMAL cipher, BIG_DECIMAL secretKey, BIG_DECIMAL publicKey)
{
	return MODULAR_EXPONENT(cipher, secretKey, publicKey);
}

//--------------------------------------------------------------------------------------------------
// return Secret Key in RSA : "e * X = 1 (mod n)"
BIG_DECIMAL RSA::GetSecretKey(BIG_DECIMAL p, BIG_DECIMAL q, BIG_DECIMAL e)
{
	BIG_DECIMAL secretKey, temp, n, one;
	unsigned char *ptrForFree;
		
	secretKey = BIG_DECIMAL((unsigned char*)"1", 1);		//initialize secret key as '1'
	one = BIG_DECIMAL((unsigned char*)"1", 1);

	n = (p - 1) * (q - 1);

	for (;;)
	{
		temp = e * secretKey;		//multiply relatively prime by secret key

		ptrForFree = temp.digit;
		temp = temp % n;						//"(e * x) mod n"
		free(ptrForFree);

		if (temp == one)							//break if "e * x = 1 (mod n)"
			break;

		ptrForFree = secretKey.digit;
		secretKey = secretKey + 1;			//increase secret key
		free(ptrForFree);
		free(temp.digit);
	}

	return secretKey;
}

//--------------------------------------------------------------------------------------------------
//return public key : "p * q"
BIG_DECIMAL RSA::GetPublicKey(BIG_DECIMAL p, BIG_DECIMAL q)
{
	return p * q;					//p * q
}
