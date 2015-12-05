//--------------------------------------------------------------
struct BIG_DECIMAL {
	unsigned char *digit;
	int size;
	bool sign;
};

//--------------------------------------------------------------
BIG_DECIMAL CreateDecimal(unsigned char* str, int size);
void printDecimal(BIG_DECIMAL decimal);

//--------------------------------------------------------------
BIG_DECIMAL PLUS(BIG_DECIMAL* A, BIG_DECIMAL* B);
BIG_DECIMAL PlusDigit(BIG_DECIMAL* A, unsigned char digit);
