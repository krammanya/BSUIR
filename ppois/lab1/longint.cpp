#include"longint.h"

using namespace std;

LongInt::LongInt() {
	negative = false;
	digits.push_back('0');  
}

LongInt :: LongInt(const string& integer) {
	negative = false;
	if (integer.empty()) throw invalid_argument("Надо ввести число");
	int startIndex = 0;
	if (integer[0] == '-') {
		negative = true;
		startIndex = 1;  
	}
	for (int i = startIndex; i < integer.size(); i++) {
		if (i==0 && integer[0] == '-') {
			negative = true;
		}
		else if (isdigit(integer[i])) digits.push_back(integer[i]);
		else {
			throw invalid_argument("Неверно ввели целое число");
		}
	}
	remove0s();
	if (digits.empty()) {
		digits.push_back('0');
		negative = false;
	}
}

LongInt::LongInt(const LongInt& other) {
	negative = other.negative;
	digits = other.digits;
}

LongInt ::~LongInt() {
	digits.clear();
}

bool LongInt::isZero() const {
	return (digits.size() == 1 && digits[0] == '0');
}

void LongInt:: remove0s() {
	while (digits.size() > 1 && digits.front() == '0') { 
		digits.pop_front();
	}
	if (digits.size() == 1 && digits.front() == '0') {
		negative = false; // -0 становится +0
	}
}

istream& operator >>(istream& in, LongInt& num) {
	string integer;
	in >> integer;
	num.digits.clear();
	num.negative = false;

	int startIndex = 0;
	if (integer[0] == '-') {
		num.negative = true;
		startIndex = 1;
	}
	for (int i = startIndex; i < integer.length(); i++) {
		if (isdigit(integer[i])) {
			num.digits.push_back(integer[i]);
		}
		else {
			throw invalid_argument("Неверно ввели целое число");
		}
	}
	num.remove0s();
	if (num.digits.empty()) {
		num.digits.push_back('0');
		num.negative = false;
	}
	return in;
}

ostream& operator <<(ostream& out, const LongInt& num) {
	LongInt output = num;
	output.remove0s();
	if (output.negative) {
		out << "-";
	}
	for (char digit : output.digits) {
		out << digit;
	}
	return out;
}

bool LongInt :: operator<(const LongInt& other)const {
	if (negative != other.negative) {
		return negative;
	}
	if (digits.size() != other.digits.size()) {
		if (negative) return digits.size() > other.digits.size();
		else return digits.size() < other.digits.size();
	}
	for (int i = 0; i < digits.size(); i++) {
		if (digits[i] != other.digits[i]) {
			if (negative) {
				return digits[i] > other.digits[i]; 
			}
			else return digits[i] < other.digits[i];
		}
	}
	return false;
}

bool LongInt::operator>(const LongInt& other) const {
	return other < *this;  // a > b если b < a
}

bool LongInt::operator<=(const LongInt& other) const {
	return !(other < *this);  // a <= b если НЕ (b < a)
}

bool LongInt::operator>=(const LongInt& other) const {
	return !(*this < other);  // a >= b если НЕ (a < b)
}

bool LongInt::operator==(const LongInt& other) const {
	return !(*this < other) && !(other < *this);  // a == b если НЕ (a < b) и НЕ (b < a)
}

bool LongInt::operator!=(const LongInt& other) const {
	return !(*this == other);  // a != b если НЕ (a == b)
}

LongInt LongInt :: operator+(const LongInt& other)const {
	if (negative != other.negative) {
		LongInt temp = other;
		temp.negative = !temp.negative;
		return *this - temp;
	}
	LongInt result;
	result.digits.clear();
	result.negative = negative;
	int i = digits.size() - 1;
	int j = other.digits.size() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0 || carry > 0) {
		int sum = carry;
		if (i >= 0) sum += digits[i--] - '0';
		if (j >= 0) sum += other.digits[j--] - '0';
		result.digits.push_front('0' + (sum % 10));
		carry = sum / 10;
	}
	result.remove0s();  
	return result;
}

LongInt& LongInt::operator+=(const LongInt& other) {
	*this = *this + other;
	return *this;
}

LongInt& LongInt::operator=(const LongInt& other) {
	if (this != &other) {
		digits = other.digits;
		negative = other.negative;
	}
	return *this;
}

LongInt LongInt::operator-(const LongInt& other)const {
	if (negative != other.negative) {
		LongInt temp = other;
		temp.negative = !temp.negative;
		return *this + temp;
	}
	if (*this == other) {
		return LongInt("0");
	}

	bool needSwap = (*this < other);
	const LongInt* larger;
	const LongInt* smaller;

	if (needSwap) {
		larger = &other;
		smaller = this;
	}
	else {
		larger = this;
		smaller = &other;
	}

	LongInt result;
	result.digits.clear();
	result.negative = needSwap;

	int borrow = 0;
	int i = larger->digits.size() - 1;
	int j = smaller->digits.size() - 1;
	while (i >= 0) {
		int top = larger->digits[i--] - '0';
		int bottom = (j >= 0) ? smaller->digits[j--] - '0' : 0;
		
		int diff = top - bottom - borrow;

		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		else borrow = 0;
		result.digits.push_front('0' + diff);
	}
	result.remove0s();
	if (result.digits.size() == 1 && result.digits[0] == '0') {
		result.negative = false;
	}
	return result;
}

LongInt& LongInt::operator-=(const LongInt& other) {
	*this = *this - other;
	return *this;
}

LongInt LongInt::operator*(const LongInt& other) const {
	bool isNegative = (negative != other.negative);
	if (isZero() || other.isZero()) return LongInt("0");
	LongInt product("0");
	for (int i = other.digits.size() - 1; i >= 0; i--) {
		int digit_other = other.digits[i] - '0';
		LongInt temp;
		temp.digits.clear();
		int carry = 0;

		for (int j = digits.size() - 1; j >= 0; j--) {
			int product_digit = (digits[j] - '0') * digit_other + carry;
			temp.digits.push_front('0' + (product_digit % 10));
			carry = product_digit / 10;
		}
		if (carry > 0) {
			temp.digits.push_front('0' + carry);
		}
		int shift = other.digits.size() - 1 - i;
		for (int s = 0; s < shift; s++) {
			temp.digits.push_back('0');
		}
		product = product + temp;
	}
	product.negative = isNegative;
	product.remove0s();
	return product;
}

LongInt& LongInt::operator*=(const LongInt& other) {
	*this = *this * other;
	return *this;
}
LongInt LongInt::operator/(const LongInt& other)const {
	if (other.isZero()) throw invalid_argument("Деление на 0");

	bool isNegative = (negative != other.negative);
	LongInt dividend = *this;    
	LongInt divisor = other;     
	dividend.negative = false;
	divisor.negative = false;

	if (dividend < divisor) {
		return LongInt("0");
	}
	if (dividend == divisor) {
		LongInt result("1");
		result.negative = isNegative;
		return result;
	}

	LongInt quotient("0");
	LongInt current("0");

	for (int i = 0; i < dividend.digits.size(); i++) {
		current = current * LongInt("10") + LongInt(string(1, dividend.digits[i]));

		int digit = 0;
		while (current >= divisor) {
			current = current - divisor;
			digit++;
		}

		if (digit > 0 || !quotient.digits.empty()) {
			quotient.digits.push_back('0' + digit);
		}
	}

	if (quotient.digits.empty()) {
		quotient.digits.push_back('0');
	}

	quotient.negative = isNegative;
	quotient.remove0s();
	return quotient;
}

LongInt& LongInt::operator /=(const LongInt& other) {
	*this = *this / other;
	return *this;
}

LongInt::operator int() const {
	const LongInt INT_MAX_VALUE("2147483647");  
	const LongInt INT_MIN_VALUE("-2147483648"); 

	if (*this > INT_MAX_VALUE) {
		return INT_MAX;
	}

	if (*this < INT_MIN_VALUE) {
		return INT_MIN;
	}

	int result = 0;
	for (int i = 0; i < digits.size(); ++i) {
		result = result * 10 + (digits[i] - '0');
	}
	if (negative) return -result;
	else return result;
}

//++a
LongInt& LongInt::operator++() {
	*this = *this + LongInt("1");
	return *this;
}

//a++
LongInt LongInt::operator++(int) {
	LongInt temp = *this;
	*this = *this + LongInt("1");
	return temp;
}

LongInt& LongInt::operator--() {
	*this = *this - LongInt("1");
	return *this;
}

LongInt LongInt::operator--(int) {
	LongInt temp = *this;
	*this = *this - LongInt("1");
	return temp;
}

void LongInt::compareWith(const LongInt& other) const {
	cout << "\nРезультаты сравнения:" << endl;
	cout << *this << " == " << other << ": " << (*this == other ? "true" : "false") << endl;
	cout << *this << " != " << other << ": " << (*this != other ? "true" : "false") << endl;
	cout << *this << " >  " << other << ": " << (*this > other ? "true" : "false") << endl;
	cout << *this << " <  " << other << ": " << (*this < other ? "true" : "false") << endl;
	cout << *this << " >= " << other << ": " << (*this >= other ? "true" : "false") << endl;
	cout << *this << " <= " << other << ": " << (*this <= other ? "true" : "false") << endl;
}

void LongInt::compareWith(int other) const {
	LongInt temp(to_string(other));
	compareWith(temp); 
}
