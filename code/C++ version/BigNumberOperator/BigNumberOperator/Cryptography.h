////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.08.21 (Version 1.0.0)
// Description    - RSA Crypto
//				    Big Number RSA Encryption/Decryption
////////////////////////////////////////////////////////////////////////////

#include "BigNumber.h"

class RSA {
public:
	static BIG_DECIMAL Encrypt(BIG_DECIMAL plain, BIG_DECIMAL e, BIG_DECIMAL publicKey);
	static BIG_DECIMAL Decrypt(BIG_DECIMAL cipher, BIG_DECIMAL secretKey, BIG_DECIMAL publicKey);
	static BIG_DECIMAL GetSecretKey(BIG_DECIMAL p, BIG_DECIMAL q, BIG_DECIMAL e);
	static BIG_DECIMAL GetPublicKey(BIG_DECIMAL p, BIG_DECIMAL q);
};
