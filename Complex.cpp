#include "Complex.h"

void Complex::set(int rl)
{
	real = rl;
	imaginary = 0;
}

void Complex::set(int rl, int img)
{
	real = rl;
	imaginary = img;
}

void Complex::set(const Int &rl)
{
	real = rl;
	imaginary = 0;
}

void Complex::set(const Int &rl, const Int &img)
{
	real = rl;
	imaginary = img;
}

void Complex::set(const Rational &rl)
{
	real = rl;
	imaginary = 0;
}

void Complex::set(const Rational &rl, const Rational &img)
{
	real = rl;
	imaginary = img;
}

void Complex::set(const char *str)
{
	string temp;
	temp.assign(str);
	set(temp);
}

void Complex::set(const string &str)
{
	real = 0;
	imaginary = 0;
	int pos = str.find('+');
	int pos2 = str.find('i');
	if (pos < pos2)
	{
		real = str.substr(0, pos);
		imaginary = str.substr(pos2 + 1, str.length() - pos - 2);
	}
	else if (pos > pos2)
	{
		imaginary = str.substr(0, pos2);
		real = str.substr(pos + 1, str.length() - pos - 1);
	}
}

Complex Complex::add(const Complex &other) const
{
	Complex rslt;
	rslt.real = real + other.real;
	rslt.imaginary = imaginary + other.imaginary;
	return rslt;
}

Complex Complex::sub(const Complex &other) const
{
	Complex rslt;
	rslt.real = real - other.real;
	rslt.real = imaginary - other.imaginary;
	return rslt;
}

Complex Complex::multi(const Complex &other) const
{
	Complex rslt;
	rslt.real = real * other.real - imaginary * other.imaginary;
	rslt.imaginary = real * other.imaginary + imaginary * other.real;
	return rslt;
}

Complex Complex::div(const Complex &other) const
{
	Complex rslt;
	rslt.real = (real * other.real + imaginary * other.imaginary) / (imaginary * imaginary + other.imaginary * other.imaginary);
	rslt.imaginary = (imaginary * other.real - real * other.imaginary) / (imaginary * imaginary + other.imaginary * other.imaginary);
	return rslt;
}

bool Complex::operator==(const Complex &other) const
{
	return real == other.real && imaginary == other.imaginary;
}

bool Complex::operator!=(const Complex &other) const
{
	return !(*this == other);
}

bool Complex::operator>(const Complex &other) const
{
	if (imaginary != 0 || other.imaginary != 0)
		throw Error(COMPARE_IMAGINARY);
	return real > other.real;
}

bool Complex::operator<(const Complex &other) const
{
	if (imaginary != 0 || other.imaginary != 0)
		throw Error(COMPARE_IMAGINARY);
	return real < other.real;
}

bool Complex::operator>=(const Complex &other) const
{
	return !(*this < other);
}

bool Complex::operator<=(const Complex &other) const
{
	return !(*this > other);
}

ostream &operator<<(ostream &os, const Complex &complex)
{
	os << complex.real << "+" << complex.imaginary << "i";
	return os;
}

istream &operator>>(istream &in, Complex &complex)
{
	string str;
	in >> str;
	complex.set(str);
	return in;
}