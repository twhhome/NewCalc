#include "calc.cpp"

int main()
{
	
	while (Input())
	{
		Rational ans = Calc(0, str.length() - 1);
		Output(ans);
	}
	/*
	Int a, b;
	cin >> a >> b;
	Int c;
	c = a % b;
	cout << c << endl;
	*/
	return 0;
}