#include "calc.cpp"

int main()
{	
	while (Input())
	{
		try
		{
			Rational ans = Calc(0, str.length() - 1);
			Output(ans);
		}
		catch (Error error)
		{
			Output(error);
		}
	}
	return 0;
}