//#include "calc.cpp"
#include "Fraction.h"

int main()
{
	/*
	while (Input())
	{
		BigNum ans = Calc(0, str.length() - 1);
		Output(ans);
	}
	*/
	Fraction a, b;
	while (1)
	{
		cin >> a >> b;
		cout << a.add(b) << endl;
	}
	return 0;
}