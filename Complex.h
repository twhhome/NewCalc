#ifndef COMPLEX_H
#define COMPLEX_H

#include "Fraction.h"
#include "Error.h"
#pragma once
class Complex
{
private:
	Rational real;//Êµ²¿
	Rational imaginary;//Ðé²¿
public:
	Complex() { set(0); }
	Complex(int rl) { set(rl); }
	Complex(int rl, int img) { set(rl, img); }
	Complex(const Int &rl) { set(rl); }
	Complex(const Int &rl, const Int &img) { set(rl, img); }
	Complex(const Rational &rl) { set(rl); }
	Complex(const Rational &rl, const Rational &img) { set(rl, img); }
	Complex(const char *str) { set(str); }
	Complex(const string &str) { set(str); }
	Complex(const Complex &other) { real = other.real; imaginary = other.imaginary; }

	void set(int rl);
	void set(int rl, int img);
	void set(const Int &rl);
	void set(const Int &rl, const Int &img);
	void set(const Rational &rl);
	void set(const Rational &rl, const Rational &img);
	void set(const char *str);
	void set(const string &str);

	Rational get_real() const { return real; }
	Rational get_imaginary() const { return imaginary; }

	Complex add(const Complex &other) const;
	Complex sub(const Complex &other) const;
	Complex multi(const Complex &other) const;
	Complex div(const Complex &other) const;

	Complex operator+(Complex const &other) const { return add(other); }
	Complex operator+(int const &n) const { Complex temp = n; return *this + temp; }
	Complex operator-(Complex const &other) const { return sub(other); }
	Complex operator-(int const &n) const { Complex temp = n; return *this - temp; }
	Complex operator*(Complex const &other) const { return multi(other); }
	Complex operator*(int const &n) const { Complex temp = n; return *this * temp; }
	Complex operator/(Complex const &other) const { return div(other); }
	Complex operator/(int const &n) const { Complex temp = n; return *this / temp; }

	void operator+=(Complex const &other) { *this = *this + other; }
	void operator+=(int const &n) { *this = *this + n; }
	void operator-=(Complex const &other) { *this = *this - other; }
	void operator-=(int const &n) { *this = *this - n; }
	void operator*=(Complex const &other) { *this = *this * other; }
	void operator*=(int const &n) { *this = *this * n; }
	void operator/=(Complex const &other) { *this = *this / other; }
	void operator/=(int const &n) { *this = *this / n; }

	Complex operator=(const int rl) { set(rl); return *this; }
	Complex operator=(const Int &rl) { set(rl); return *this; }
	Complex operator=(const Rational &rl) { set(rl); return *this; }
	Complex operator=(const char *str) { set(str); return *this; }
	Complex operator=(const string str) { set(str); return *this; }
	Complex operator=(const Complex &other) { real = other.real; imaginary = other.imaginary; return *this; }

	bool operator==(const Complex &other) const;
	bool operator!=(const Complex &other) const;
	bool operator>(const Complex &other) const;
	bool operator>=(const Complex &other) const;
	bool operator<(const Complex &other) const;
	bool operator<=(const Complex &other) const;

	friend ostream &operator<<(ostream &os, const Complex &complex);
	friend istream &operator>>(istream &in, Complex &complex);
};

#endif