#include "calc.cpp"

int main()
{
	
	while (Input())
	{
		Rational ans = Calc(0, str.length() - 1);
		Output(ans);
	}
	return 0;
}