#include "BigNum.h"

extern const int MAXN;
extern const int MAXM;
extern const int bit;

string strexczero(string &str) // wipe off zeros in front of the str
{
	string rslt;
	int flag = 0;
	int book = 0;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (i == 0 && str[i] == '-')
		{
			book = 1;
			continue;
		}
		if (str[i] != '0')
		{
			flag = i;
			break;
		}
	}
	rslt = str.substr(flag, str.length() - flag);
	if (book == 1)
		rslt = "-" + rslt;
	if (flag == 0 && str[0] == '0')
		rslt = "0";
	return rslt;
}

int my_pow(int n) // return 10^n
{
	int ans = 1;
	for (int i = 1; i <= n; i++)
		ans *= 10;
	return ans;
}

int string_to_int(string &str, int start, int end)
{
	int n = 0;
	for (int i = start; i <= end; i++)
		n += (str[i] - '0') * my_pow(end - i);
	return n;
}

vector<int> vector_reverse(vector<int> *vec)
{
	vector<int> ans;
	vector<int>::reverse_iterator ptr = vec->rbegin();
	while (ptr != vec->rend())
	{
		ans.push_back(*ptr);
		ptr++;
	}
	return ans;
}

BigNum::BigNum(BigNum const &src)
{
	//len = src.len;
	//inte_len = src.inte_len;
	s = src.s;
	integer = src.integer;
}

void BigNum::set(string &str)
{
	string tmp = strexczero(str);
	if (tmp[0] == '-')
	{
		s = -1;
		tmp = tmp.substr(1, tmp.length() - 1);
	}
	else if (tmp[0] == '0')
		s = 0;
	else
		s = 1;
	//len = tmp.length();
	//inte_len = 0;
	integer.clear();
	for (int i = tmp.length() - 1; i >= 0; i--)
	{
		if ((tmp.length() - i - 1) % bit == bit - 1)
			integer.push_back(string_to_int(tmp, i, i + bit - 1));
		else if (i == 0)
			integer.push_back(string_to_int(tmp, i, (tmp.length() - ((tmp.length() - i - 1) / bit) * bit - 1)));
	}
}

void BigNum::set(char *num)
{
	string str;
	str.assign(num);
	set(str);
}

void BigNum::set(int num)
{
	//len = 0;
	//inte_len = 0;
	int n = num;
	if (num == 0)
		integer.push_back(0);
	else if (num < 0)
		n = -n;
	while (n != 0)
	{
		integer.push_back(n % MAXM);
		n = n / MAXM;
	}
	if (num > 0)
		s = 1;
	else if (num == 0)
		s = 0;
	else
		s = -1;
}

BigNum BigNum::add(BigNum const &other) const
{
	BigNum rslt;
	rslt.integer.clear();
	//rslt.inte_len = 0;
	if (s >= 0 && other.s >= 0)
	{
		rslt.s = 1;
		for (int i = 0; i < integer.size() || i < other.integer.size(); i++)
		{
			int curr;
			if (i >= integer.size())
				curr = other.integer[i];
			else if (i >= other.integer.size())
				curr = integer[i];
			else
				curr = integer[i] + other.integer[i];
			curr += (!rslt.integer.empty()) ?  rslt.integer[rslt.integer.size() - 1] : 0;
			if (rslt.integer.empty())
				rslt.integer.push_back(curr % MAXM);
			else
				rslt.integer[rslt.integer.size() - 1] = curr % MAXM;
			rslt.integer.push_back(curr / MAXM);
		}
		if (rslt.integer[rslt.integer.size() - 1] == 0)
			rslt.integer.pop_back();
	}
	else if (s >= 0 && other.s < 0)
	{
		BigNum tmp;
		tmp = other;
		tmp.s = 1;
		rslt = sub(tmp);
	}
	else if (s < 0 && other.s >= 0)
	{
		rslt = other.add(*this);
	}
	else if (s < 0 && other.s < 0)
	{
		BigNum tmp1, tmp2;
		tmp1 = *this;
		tmp1.s = 1;
		tmp2 = other;
		tmp2.s = 1;
		rslt = tmp1.add(tmp2);
		rslt.s = -1;
	}
	return rslt;
}

BigNum BigNum::sub(BigNum const &other) const
{
	BigNum rslt;
	//rslt.inte_len = 0;
	rslt.integer.clear();
	if (s >= 0 && other.s >= 0)
	{
		if (*this >= other)
		{
			rslt.s = 1;
			rslt.integer.push_back(0);
			//rslt.integer[rslt.inte_len] = 0;
			for (int i = 0; i < integer.size() || i < other.integer.size(); i++)
			{
				int curr;
				if (i >= integer.size())
					curr = other.integer[i];
				else if (i >= other.integer.size())
					curr = integer[i];
				else
					curr = integer[i] - other.integer[i];
				curr += rslt.integer[rslt.integer.size() - 1];
				rslt.integer[rslt.integer.size() - 1] = (curr < 0) ? MAXM + curr : curr;
				rslt.integer.push_back((curr < 0) ? -1 : 0);
			}
			for (int i = rslt.integer.size() - 1; i >= 0; i--)
			{
				if (rslt.integer[i] != 0)
					break;
				if (rslt.integer[i] == 0)
					rslt.integer.pop_back();
			}
			if (rslt.integer.empty())
			{
				rslt.s = 0;
				rslt.integer.push_back(0);
			}
		}
		else if (*this < other)
		{
			rslt = other.sub(*this);
			rslt.s = -1;
		}
	}
	else if (s >= 0 && other.s < 0)
	{
		BigNum tmp;
		tmp = other;
		tmp.s = 1;
		rslt = add(tmp);
	}
	else if (s < 0 && other.s >= 0)
	{
		rslt = other.sub(*this);
		rslt.s = -rslt.s;
	}
	else if (s < 0 && other.s < 0)
	{
		BigNum tmp1, tmp2;
		tmp1 = *this;
		tmp1.s = 1;
		tmp2 = other;
		tmp2.s = 1;
		rslt = tmp1.sub(tmp2);
		rslt.s = -rslt.s;
	}
	return rslt;
}

BigNum BigNum::multi(BigNum const &other) const
{
	BigNum rslt;
	//rslt.inte_len = 0;
	rslt.integer.clear();
	//int maxipj = -1; //the maximum of i plus j
	for (int i = 0; i < other.integer.size(); i++)
	{
		for (int j = 0; j < integer.size(); j++)
		{
			int curr;
			curr = other.integer[i] * integer[j];
			if (i + j > rslt.integer.size() - 1 || rslt.integer.empty())
			{
				//maxipj = i + j;
				rslt.integer.push_back(0);
				//rslt.integer[i + j] = 0;
			}
			rslt.integer[i + j] += curr;
		}
	}
	int len = rslt.integer.size();
	for (int i = 0; i <= len - 1; i++)
	{
		int curr = rslt.integer[i];
		rslt.integer[i] = curr % MAXM;
		if (i == rslt.integer.size() - 1)
			rslt.integer.push_back(0);
			//rslt.integer[i + 1] = 0;
		rslt.integer[i + 1] += curr / MAXM;
	}
	if (rslt.integer[rslt.integer.size() - 1] == 0)
		rslt.integer.pop_back();
	rslt.s = s * other.s;
	return rslt;
}

BigNum BigNum::div(BigNum &other) const
{
	BigNum rslt, tmp, tmp2;
	rslt.integer.clear();
	tmp.integer.clear();
	tmp2.integer.clear();
	bool book = false; // whether other is smaller than 0
	bool not_zero = false; // whether the first number is zero
	rslt.s = s * other.s;
	if (other.s < 0)
	{
		other.s = -other.s;
		book = true;
	}
	//rslt.inte_len = inte_len - other.inte_len + 1;
	for (int i = 1; i <= integer.size() - other.integer.size() + 1; i++)
		rslt.integer.push_back(0);
	tmp = *this;
	tmp.s = 1;
	for (int i = rslt.integer.size() - 1; i >= 0; i--)
	{
		for (int j = 1; j <= MAXM; j++)
		{
			if (other * j > tmp.subnum(i, tmp.integer.size() - 1))
			{
				if (j == 1 && not_zero == false)
					rslt.integer.pop_back();
				else
				{
					not_zero = true;
					rslt.integer[i] = j - 1;
					tmp2 = other * (j - 1);
					/*
					tmp2.inte_len += i;
					for (int k = tmp2.inte_len - 1; k >= 0; k--)
						tmp2.integer[k] = ((k - i) >= 0) ? tmp2.integer[k - i] : 0;
					*/
					int len = tmp2.integer.size();
					for (int k = 0; k < i; k++)
					{
						for (int l = len - 1; l >= 0; l--)
						{
							if (l == len - 1)
							{
								tmp2.integer.push_back(tmp2.integer[tmp2.integer.size() - 1]);
								tmp2.integer[tmp2.integer.size() - 2] = 0;
							}
							else
							{
								tmp2.integer[l + k + 1] = tmp2.integer[l + k];
								tmp2.integer[l + k] = 0;
							}
						}
					}
					tmp -= tmp2;
				}
				break;
			}
		}
	}
	if (integer.size() < other.integer.size())
		rslt = 0;
	else if (rslt.integer.size() == 0)
		rslt = 0;
	if (book) // if other is smaller than 0, then recover it
		other.s = -other.s;
	return rslt;
}

BigNum BigNum::mod(BigNum &other) const
{
	return *this - *this / other * other;
}

BigNum BigNum::operator+(int const &n) const
{
	BigNum bn;
	bn = n;
	return *this + bn;
}

BigNum BigNum::operator-(int const &n) const
{
	BigNum bn;
	bn = n;
	return *this - bn;
}

BigNum BigNum::operator*(int const &n) const
{
	BigNum bn;
	bn = n;
	return *this * bn;
}

BigNum BigNum::operator/(int const &n) const
{
	BigNum bn;
	bn = n;
	return *this / bn;
}

BigNum BigNum::operator%(int const &n) const
{
	BigNum bn;
	bn = n;
	return *this % bn;
}

bool BigNum::operator==(BigNum const &other) const
{
	if (s != other.s)
		return false;
	else
	{
		if (integer.size() == other.integer.size())
		{
			for (int i = 0; i < integer.size(); i++)
			{
				if (integer[i] != other.integer[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}
}

bool BigNum::operator!=(BigNum const &other) const
{
	return !(*this == other);
}

bool BigNum::operator<(BigNum const &other) const
{
	if (s != other.s)
		return (s < other.s) ? true : false;
	else
	{
		if (integer.size() != other.integer.size())
			return (integer.size() < other.integer.size()) ? true : false;
		else
		{
			for (int i = integer.size() - 1; i >= 0; i--)
			{
				if (integer[i] != other.integer[i])
					return (integer[i] < other.integer[i]) ? true : false;
			}
			return false;
		}
	}
}

bool BigNum::operator<=(BigNum const &other) const
{
	if (*this < other || *this == other)
		return true;
	else
		return false;
}

bool BigNum::operator>(BigNum const &other) const
{
	return !(*this <= other);
}

bool BigNum::operator>=(BigNum const &other) const
{
	return !(*this < other);
}

BigNum BigNum::subnum(int start, int end)
{
	BigNum rslt;
	rslt.s = s;
	rslt.integer.clear();
	for (int i = start; i <= end; i++)
		rslt.integer.push_back(integer[i]);
	return rslt;
}

ostream &operator<<(ostream &os, BigNum const &bn)
{
	if (bn.s == (-1))
		os << "-";
	for (int i = bn.integer.size() - 1; i >= 0; i--)
	{
		if (i != bn.integer.size() - 1)
			os << setw(bit) << setfill('0') << bn.integer[i];
		else
			os << bn.integer[i];
	}
	return os;
}

istream &operator>>(istream &in, BigNum &bn)
{
	string str;
	in >> str;
	bn.set(str);
	return in;
}
