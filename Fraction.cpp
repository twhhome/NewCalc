#include "Fraction.h"

void Fraction::set(const int n, const int d)
{
	num = n;
	den = d;
	normalize();
}

void Fraction::set(Int const &n, Int const &d)
{
	num = n;
	den = d;
	normalize();
}

void Fraction::set(const char *str)
{
	string temp;
	temp.assign(str);
	set(temp);
}

void Fraction::set(const string &str)
{
	num = 0;
	den = 1;
	int pos = str.find('/', 0);
	if (pos == string::npos)
		num = str;
	else
	{
		num = str.substr(0, pos);
		den = str.substr(pos + 1, str.length() - 1);
		normalize();
	}
}

void Fraction::normalize()
{
	if (den == 0 || num == 0)
	{
		num = 0;
		den = 1;
	}
	if (den == 1)
		return;
	Int n = gcd(num, den);
	num /= n;
	den /= n; 
	if (den < 0)
	{
		num *= -1;
		den *= -1;
	}
}

Int Fraction::gcd(Int a, Int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

Int Fraction::lcm(Int a, Int b)
{
	return a * b / gcd(a, b);
}

Fraction Fraction::add(Fraction const &other) const
{
	Fraction rslt;
	rslt.num = num * other.den + den * other.num;
	rslt.den = den * other.den;
	rslt.normalize();
	return rslt;
}

Fraction Fraction::sub(Fraction const &other) const
{
	Fraction rslt;
	rslt.num = num * other.den - den * other.num;
	rslt.den = den * other.den;
	rslt.normalize();
	return rslt;
}

Fraction Fraction::multi(Fraction const &other) const
{
	Fraction rslt;
	rslt.num = num * other.num;
	rslt.den = den * other.den;
	rslt.normalize();
	return rslt;
}

Fraction Fraction::div(Fraction const &other) const
{
	Fraction rslt;
	rslt.num = num * other.den;
	rslt.den = den * other.num;
	rslt.normalize();
	return rslt;
}

Fraction Fraction::operator+(int const &n) const
{
	Fraction tmp = n;
	return *this + tmp;
}

Fraction Fraction::operator-(int const &n) const
{
	Fraction tmp = n;
	return *this - tmp;
}

Fraction Fraction::operator*(int const &n) const
{
	Fraction tmp = n;
	return *this * tmp;
}

Fraction Fraction::operator/(int const &n) const
{
	Fraction tmp = n;
	return *this / tmp;
}

bool Fraction::operator==(Fraction const &other) const
{
	if (num == other.num && den == other.den)
		return true;
	else
		return false;
}

bool Fraction::operator!=(Fraction const &other) const
{
	return !(*this == other);
}

bool Fraction::operator<(Fraction const &other) const
{
	return num * other.den < den * other.num;
}

bool Fraction::operator<=(Fraction const &other) const
{
	return num * other.den <= den * other.num;
}

bool Fraction::operator>(Fraction const &other) const
{
	return num * other.den > den * other.num;
}

bool Fraction::operator>=(Fraction const &other) const
{
	return num * other.den >= den * other.num;
}

ostream &operator<<(ostream &os, Fraction const &fc)
{
	if (fc.den == 1)
		os << fc.num;
	else
		os << fc.num << "/" << fc.den;
	return os;
}

istream &operator>>(istream &in, Fraction &fc)
{
	string str;
	in >> str;
	fc.set(str);
	return in;
}
