#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include<deque>
#include<string>

using namespace std;
class LongInt {
	friend istream& operator >>(istream& in, LongInt& num);
	friend ostream& operator <<(ostream& out,const LongInt& num);

	public:
		LongInt();
		LongInt(const string& str);
		LongInt(const LongInt& other);

		void remove0s();

		~LongInt();

		LongInt operator+(const LongInt& other)const;
		LongInt& operator+=(const LongInt& other);

		LongInt operator-(const LongInt& other)const;
		LongInt& operator-=(const LongInt& other);

		LongInt operator*(const LongInt& other)const;
		LongInt& operator*=(const LongInt& other);
		bool isZero()const;

		LongInt operator/(const LongInt& other)const;
		LongInt& operator/=(const LongInt& other);

		bool operator< (const LongInt& num) const;
		bool operator<= (const LongInt& num) const;
		bool operator> (const LongInt& num) const;
		bool operator>= (const LongInt& num) const;
		bool operator== (const LongInt& num) const;
		bool operator!= (const LongInt& num) const;

		LongInt& operator=(const LongInt& other);


		operator int() const;

		LongInt& operator++();
		LongInt operator++(int);
		LongInt& operator--();
		LongInt operator--(int);

		void compareWith(const LongInt& other) const;
		void compareWith(int other) const;

	private:
		deque <char> digits;
		bool negative;
		

};

#endif // !LONGINT

