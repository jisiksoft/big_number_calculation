//--------------------------------------------------------------
struct BIG_DECIMAL {
	unsigned char *digit;
	int size;
	bool sign;
};

//--------------------------------------------------------------
struct BIG_BINARY {
	unsigned char *byte;
	int size;
};

//--------------------------------------------------------------
BIG_DECIMAL CreateDecimal(unsigned char* str, int size);
BIG_BINARY CreateBinary(unsigned char* bytes, int length);	
void printDecimal(BIG_DECIMAL decimal);
void printBinary(BIG_BINARY binary);			
bool IsEqual(BIG_DECIMAL* A, BIG_DECIMAL* B);
bool IsBigger(BIG_DECIMAL* A, BIG_DECIMAL* B);

//--------------------------------------------------------------
BIG_DECIMAL PLUS(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '+'
BIG_DECIMAL MINUS(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '-'
BIG_DECIMAL MULTIPLY(BIG_DECIMAL* A, BIG_DECIMAL* B);			// '*'
BIG_DECIMAL DIVIDE(BIG_DECIMAL* A, BIG_DECIMAL* B);				// '/'
BIG_DECIMAL MODULAR(BIG_DECIMAL* A, BIG_DECIMAL* M);			// '%'
BIG_DECIMAL MULTIPLY_EXPONENT(BIG_DECIMAL* A, BIG_DECIMAL* E);

BIG_DECIMAL MinusAbsolute(BIG_DECIMAL* A, BIG_DECIMAL* B);
BIG_DECIMAL MultiplyDigit(BIG_DECIMAL* A, unsigned char digit);
void MinusForDivide(BIG_DECIMAL* A, BIG_DECIMAL* B);

//--------------------------------------------------------------
BIG_DECIMAL GetDecimal(BIG_BINARY* binary);
BIG_BINARY GetBinary(BIG_DECIMAL* decimal);