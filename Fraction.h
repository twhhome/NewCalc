#ifndef FRACTION_H
#define FRACTION_H

#include "BigNum.h"

#pragma once
class Fraction
{
private:
	Int num, den;
	void normalize();
	Int gcd(Int a, Int b);
	Int lcm(Int a, Int b);

public:
	Fraction() { num = 0; den = 1; }
	Fraction(const int n) { num = n; den = 1; }
	Fraction(const int n, const int d) { set(n, d); }
	Fraction(const Int &n) { num = n; den = 1; }
	Fraction(const Int &n, const Int &d) { set(n, d); }
	Fraction(const char *str) { set(str); }
	Fraction(const string &str) { set(str); }
	Fraction(const Fraction &src) { num = src.num; den = src.den; }

	void set(const int n, const int d);
	void set(const Int &n, const Int &d);
	void set(const char *str);
	void set(const string &str);

	Int get_num() const { return num; }
	Int get_den() const { return den; }

	Fraction add(Fraction const &other) const;
	Fraction sub(Fraction const &other) const;
	Fraction multi(Fraction const &other) const;
	Fraction div(Fraction const &other) const;

	Fraction operator+(Fraction const &other) const { return add(other); }
	Fraction operator+(int const &n) const;
	Fraction operator-(Fraction const &other) const { return sub(other); }
	Fraction operator-(int const &n) const;
	Fraction operator*(Fraction const &other) const { return multi(other); }
	Fraction operator*(int const &n) const;
	Fraction operator/(Fraction const &other) const { return div(other); }
	Fraction operator/(int const &n) const;

	void operator+=(Fraction const &other) { *this = *this + other; }
	void operator+=(int const &n) { *this = *this + n; }
	void operator-=(Fraction const &other) { *this = *this - other; }
	void operator-=(int const &n) { *this = *this - n; }
	void operator*=(Fraction const &other) { *this = *this * other; }
	void operator*=(int const &n) { *this = *this * n; }
	void operator/=(Fraction const &other) { *this = *this / other; }
	void operator/=(int const &n) { *this = *this / n; }

	Fraction operator=(const int &n) { num = n; den = 1; return *this; }
	Fraction operator=(const Int &n) { num = n; den = 1; return *this; }
	Fraction operator=(const char *str) { set(str); return *this; }
	Fraction operator=(const string &str) { set(str); return *this; }
	Fraction operator=(const Fraction &fr) { num = fr.num; den = fr.den; return *this; }

	Fraction& operator++()
	{
		*this = *this + 1;
		return *this;
	}
	const Fraction operator++(int)
	{
		Fraction tmp = *this;
		++(*this);
		return tmp;
	}
	Fraction& operator--()
	{
		*this = *this - 1;
		return *this;
	}
	const Fraction operator--(int)
	{
		Fraction tmp = *this;
		--(*this);
		return tmp;
	}

	bool operator==(Fraction const &other) const;
	bool operator!=(Fraction const &other) const;
	bool operator<(Fraction const &other) const;
	bool operator<=(Fraction const &other) const;
	bool operator>(Fraction const &other) const;
	bool operator>=(Fraction const &other) const;

	friend ostream &operator<<(ostream &os, Fraction const &fc);
	friend istream &operator>>(istream &in, Fraction &fc);
};

typedef Fraction Rational;

#endif