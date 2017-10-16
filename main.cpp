#include "BigNum.h"
#include "calc.cpp"

int main()
{
	while (Input())
		cout << Calc(0, str.length() - 1) << endl;
	/*
	BigNum a, b;
	while (1)
	{
		cin >> a >> b;
		cout << a.mod(b) << endl;
	}
	*/
	return 0;
}