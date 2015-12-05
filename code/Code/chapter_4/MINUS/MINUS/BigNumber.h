//--------------------------------------------------------------
struct BIG_DECIMAL {
	unsigned char *digit;
	int size;
	bool sign;
};

//--------------------------------------------------------------
BIG_DECIMAL CreateDecimal(unsigned char* str, int size);
void printDecimal(BIG_DECIMAL decimal);
bool IsEqual(BIG_DECIMAL* A, BIG_DECIMAL* B);
bool IsBigger(BIG_DECIMAL* A, BIG_DECIMAL* B);

//--------------------------------------------------------------
BIG_DECIMAL MINUS(BIG_DECIMAL* A, BIG_DECIMAL* B);
BIG_DECIMAL MinusAbsolute(BIG_DECIMAL* A, BIG_DECIMAL* B);
BIG_DECIMAL MinusDigit(BIG_DECIMAL* A, unsigned char digit);
