#ifndef BIGNUM_H
#define BIGNUM_H

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
#include<vector>
#include "Error.h"
using namespace std;

#pragma once
extern const int MAXN = 250; // the max number of the elements of the array
extern const int MAXM = 1000000000; // the max number of the elements in the array
extern const int bit = 9;
/*if the max num which BigNum can store is 1000, 
then MAXN = 250, and each element in the array is 
no bigger than 10000*/

class BigNum
{
private:
	vector<int> integer;
	int s; //positive:1 zero:0 negative:-1

public:
	BigNum() { set(0); }
	BigNum(const string &str) { set(str); }
	BigNum(const char *num) { set(num); }
	BigNum(const int num) { set(num); }
	BigNum(const BigNum &bn) { set(bn); }

	void set(const int num);
	void set(const string &str);
	void set(const char *num);
	void set(const BigNum &bn);

	BigNum add(BigNum const &other) const;
	BigNum sub(BigNum const &other) const;
	BigNum multi(BigNum const &other) const;
	BigNum div(BigNum const &other) const;
	BigNum mod(BigNum const &other) const;

	BigNum operator+(BigNum const &other) const { return add(other); }
	BigNum operator+(int const &n) const;
	BigNum operator-(BigNum const &other) const { return sub(other); }
	BigNum operator-(int const &n) const;
	BigNum operator*(BigNum const &other) const { return multi(other); }
	BigNum operator*(int const &n) const;
	BigNum operator/(BigNum const &other) const { return div(other); }
	BigNum operator/(int const &n) const;
	BigNum operator%(BigNum const &other) const { return mod(other); }
	BigNum operator%(int const &n) const;

	void operator+=(BigNum const &other) { *this = *this + other; }
	void operator+=(int const &n) { *this = *this + n; }
	void operator-=(BigNum const &other) { *this = *this - other; }
	void operator-=(int const &n) { *this = *this - n; }
	void operator*=(BigNum const &other) { *this = *this * other; }
	void operator*=(int const &n) { *this = *this * n; }
	void operator/=(BigNum const &other) { *this = *this / other; }
	void operator/=(int const &n) { *this = *this / n; }

	BigNum operator=(const int &n) { set(n); return *this; }
	BigNum operator=(const char *num) { set(num); return *this; }
	BigNum operator=(const string &str) { set(str); return *this; }
	BigNum operator=(const BigNum &bn) { set(bn); return *this; }
	
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

	BigNum subnum(int start, int end) const;

	friend ostream &operator<<(ostream &os, BigNum const &bn);
	friend istream &operator>>(istream &in, BigNum &bn);
};

typedef BigNum Int;

#endif