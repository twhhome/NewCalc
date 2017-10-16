#include "BigNum.h"

string str;

int Input() // input of the expression
{
	cin >> str;
	if (str == "exit")
		return 0; // return 0 to break the circulation
	return 1;
}

BigNum Calc(int s, int e)
{
	BigNum ans = 0;
	BigNum rslt_md; // result of multi and div
	int start = -1, end = -1; // the start and end of substr 
	char last1 = '+'; // the last symbol of +, -
	char last2 = NULL; // the last symbol of *, /
	stack<int> brackets;
	bool if_bracket = false; // whether have brackets
	BigNum bracket;
	for (int i = s; i <= e; i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			if (str[i] == '(')
			{
				brackets.push(i);
				if_bracket = true;
			}
			else if (str[i] == ')')
			{
				if (brackets.size() == 1)
					bracket = Calc(brackets.top() + 1, i - 1);
				brackets.pop();
				if (i != e)
					continue;
			}
		}
		if (!brackets.empty())
			continue;
		if (i != e && (str[i] >= '0' && str[i] <= '9'))
		{
			if (start == -1)
				start = i;
		}
		else if (i != e && (str[i] < '0' || str[i] > '9')) // not a number && i is not the end of the string
		{
			BigNum num;
			if (if_bracket)
			{
				num = bracket;
				if_bracket = false;
			}
			else
			{
				end = i - 1;
				string sub_str = str.substr(start, end - start + 1);
				num = sub_str; // the current number
			}
			// judge the symbol
			if (str[i] == '+' || str[i] == '-')
			{
				switch (last2)
				{
				case '*':
					rslt_md *= num;
					break;
				case '/':
					rslt_md /= num;
					break;
				}
				switch (last1)
				{
				case '+':
					ans += (last2 == '*' || last2 == '/') ? rslt_md : num;
					break;
				case '-':
					ans -= (last2 == '*' || last2 == '/') ? rslt_md : num;
					break;
				}
				last1 = str[i];
				last2 = NULL;
			}
			else if (str[i] == '*' || str[i] == '/')
			{
				switch (last2)
				{
				case '*':
					rslt_md *= num;
					break;
				case '/':
					rslt_md /= num;
					break;
				case NULL:
					rslt_md = num;
					break;
				}
				last2 = str[i];
			}
			end = -1;
			start = -1;
		}
		else if (i == e) // end of the string
		{
			BigNum num;
			if (str[i] == ')')
			{
				num = bracket;
				if_bracket = false;
			}
			else
			{
				if (start == -1)
					start = i;
				end = i;
				string sub_str = str.substr(start, end - start + 1);
				num = sub_str;
			}
			switch (last2)
			{
			case '*':
				rslt_md *= num;
				break;
			case '/':
				rslt_md /= num;
				break;
			}
			switch (last1)
			{
			case '+':
				ans += (last2 == '*' || last2 == '/') ? rslt_md : num;
				break;
			case '-':
				ans -= (last2 == '*' || last2 == '/') ? rslt_md : num;
				break;
			}
		}
	}
	return ans;
}