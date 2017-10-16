#include "BigNum.h"
#include "calc.cpp"

int main()
{
	while (Input())
	{
		BigNum ans = Calc(0, str.length() - 1);
		Output(ans);
	}
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