#include "calc.cpp"

int main()
{
	
	while (Input())
	{
		BigNum ans = Calc(0, str.length() - 1);
		Output(ans);
	}
	return 0;
}