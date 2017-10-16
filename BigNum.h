/*
the way to store number in the integer array is like:(if MAXM = 10000)
n=1234567890
then integer[0] = 7890, integer[1] = 3456, integer[2] = 12
*/

#include<string>
#include<iostream>
#include<algorithm>
#include<stack>
#include<iomanip>
using namespace std;

#pragma once
const int MAXN = 10; // the max number of the elements of the array
const int MAXM = 10000; // the max number of the elements in the array
/*if the max num which BigNum can store is 100000, 
then MAXN = 10, and each element in the array is 
no bigger than 10000*/

class BigNum
{
private:
	int integer[MAXN];
	//int len;
	int inte_len; // the length of the integer array
	int s; //positive:1 zero:0 negative:-1

public:
	BigNum() { set(0); }
	BigNum(string str) { set(str); }
	BigNum(char *num) { set(num); }
	BigNum(int num) { set(num); }
	BigNum(BigNum const &src);

	//int get_len() const { return len; }
	void set(int num);
	void set(string str);
	void set(char *num);

	BigNum add(BigNum const &other) const;
	BigNum sub(BigNum const &other) const;
	BigNum multi(BigNum const &other) const;
	BigNum div(BigNum &other) const;
	BigNum mod(BigNum &other) const;

	BigNum operator+(BigNum const &other) const { return add(other); }
	BigNum operator+(int const &n) const;
	BigNum operator-(BigNum const &other) const { return sub(other); }
	BigNum operator-(int const &n) const;
	BigNum operator*(BigNum const &other) const { return multi(other); }
	BigNum operator*(int const &n) const;
	BigNum operator/(BigNum &other) const { return div(other); }
	BigNum operator/(int const &n) const;
	BigNum operator%(BigNum &other) const { return mod(other); }
	BigNum operator%(int const &n) const;

	void operator+=(BigNum const &other) { *this = *this + other; }
	void operator+=(int const &n) { *this = *this + n; }
	void operator-=(BigNum const &other) { *this = *this - other; }
	void operator-=(int const &n) { *this = *this - n; }
	void operator*=(BigNum const &other) { *this = *this * other; }
	void operator*=(int const &n) { *this = *this * n; }
	void operator/=(BigNum &other) { *this = *this / other; }
	void operator/=(int const &n) { *this = *this / n; }

	BigNum& operator++() {
		*this = *this + 1;
		return *this;
	}
	const BigNum operator++(int) {
		BigNum tmp = *this;
		++(*this);
		return tmp;
	}
	BigNum& operator--() {
		*this = *this - 1;
		return *this;
	}
	const BigNum operator--(int) {
		BigNum tmp = *this;
		--(*this);
		return tmp;
	}

	bool operator==(BigNum const &other) const;
	bool operator!=(BigNum const &other) const;
	bool operator<(BigNum const &other) const;
	bool operator<=(BigNum const &other) const;
	bool operator>(BigNum const &other) const;
	bool operator>=(BigNum const &other) const;

	
	BigNum &operator=(BigNum const &other) {
		//len = other.len;
		inte_len = other.inte_len;
		s = other.s;
		for (int i = 0; i < inte_len; i++)
			integer[i] = other.integer[i];
		return *this;
	}
	
	BigNum subnum(int start, int end);

	friend ostream &operator<<(ostream &os, BigNum const &bn);
	friend istream &operator>>(istream &in, BigNum &bn);
};

