////////////////////////////////////////////////////////////////////////////
// Developer Name - SEHOON KIM
// Draft Date	  - 2011.08.21 (Version 1.0.0)
// Description    - RSA Crypto
//				    Big Number RSA Encryption/Decryption
////////////////////////////////////////////////////////////////////////////

#include "BigNumber.h"

BIG_DECIMAL RSAEncrypt(BIG_DECIMAL *plain, BIG_DECIMAL *e, BIG_DECIMAL *publicKey);
BIG_DECIMAL RSADecrypt(BIG_DECIMAL *cipher, BIG_DECIMAL *secretKey, BIG_DECIMAL *publicKey);
BIG_DECIMAL RSAGetSecretKey(BIG_DECIMAL *p, BIG_DECIMAL *q, BIG_DECIMAL *e);
BIG_DECIMAL RSAGetPublicKey(BIG_DECIMAL *p, BIG_DECIMAL *q);
