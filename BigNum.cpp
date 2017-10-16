#include "BigNum.h"

string strexczero(string str) // wipe off zeros in front of the str
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

BigNum::BigNum(BigNum const &src)
{
	//len = src.len;
	inte_len = src.inte_len;
	s = src.s;
	for (int i = 0; i < inte_len; i++)
		integer[i] = src.integer[i];
}

void BigNum::set(string str)
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
	inte_len = 0;
	for (int i = tmp.length() - 1; i >= 0; i--)
	{
		if ((tmp.length() - i - 1) % bit == bit - 1)
			integer[inte_len++] = string_to_int(tmp, i, i + bit - 1);
		else if (i == 0)
			integer[inte_len++] = string_to_int(tmp, i, (tmp.length() - ((tmp.length() - i - 1) / bit) * bit - 1));
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
	inte_len = 0;
	int n = num;
	if (num == 0)
		integer[inte_len++] = 0;
	else if (num < 0)
		n = -n;
	while (n != 0)
	{
		integer[inte_len++] = n % MAXM;
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
	rslt.inte_len = 0;
	if (s >= 0 && other.s >= 0)
	{
		rslt.s = 1;
		for (int i = 0; i < inte_len || i < other.inte_len; i++)
		{
			int curr;
			if (i >= inte_len)
				curr = other.integer[i];
			else if (i >= other.inte_len)
				curr = integer[i];
			else
				curr = integer[i] + other.integer[i];
			curr += rslt.integer[rslt.inte_len];
			rslt.integer[rslt.inte_len++] = curr % MAXM;
			rslt.integer[rslt.inte_len] = 0;
			rslt.integer[rslt.inte_len] = curr / MAXM;
		}
		if (rslt.integer[rslt.inte_len] != 0)
			rslt.inte_len++;
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
	rslt.inte_len = 0;
	if (s >= 0 && other.s >= 0)
	{
		if (*this >= other)
		{
			rslt.s = 1;
			rslt.integer[rslt.inte_len] = 0;
			for (int i = 0; i < inte_len || i < other.inte_len; i++)
			{
				int curr;
				if (i >= inte_len)
					curr = other.integer[i];
				else if (i >= other.inte_len)
					curr = integer[i];
				else
					curr = integer[i] - other.integer[i];
				curr += rslt.integer[rslt.inte_len];
				rslt.integer[rslt.inte_len++] = (curr < 0) ? MAXM + curr : curr;
				rslt.integer[rslt.inte_len] = 0;
				rslt.integer[rslt.inte_len] = (curr < 0) ? -1 : 0;
			}
			for (int i = rslt.inte_len - 1; i >= 0; i--)
			{
				if (rslt.integer[i] != 0)
				{
					rslt.inte_len = i + 1;
					break;
				}
			}
			if (rslt.integer[rslt.inte_len - 1] == 0)
			{
				rslt.s = 0;
				rslt.inte_len = 1;
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
	rslt.inte_len = 0;
	int maxipj = -1; //the maximum of i plus j
	for (int i = 0; i < other.inte_len; i++)
	{
		for (int j = 0; j < inte_len; j++)
		{
			int curr;
			curr = other.integer[i] * integer[j];
			if (i + j > maxipj)
			{
				maxipj = i + j;
				rslt.integer[i + j] = 0;
			}
			rslt.integer[i + j] += curr;
		}
	}
	for (int i = 0; i <= maxipj; i++)
	{
		int curr = rslt.integer[i];
		rslt.integer[i] = curr % MAXM;
		if (i == maxipj)
			rslt.integer[i + 1] = 0;
		rslt.integer[i + 1] += curr / MAXM;
		rslt.inte_len++;
	}
	if (rslt.integer[rslt.inte_len] != 0)
		rslt.inte_len++;
	rslt.s = s * other.s;
	return rslt;
}

BigNum BigNum::div(BigNum &other) const
{
	BigNum rslt, tmp, tmp2;
	bool book = false; // whether other is smaller than 0
	bool not_zero = false; // whether the first number is zero
	rslt.s = s * other.s;
	if (other.s < 0)
	{
		other.s = -other.s;
		book = true;
	}
	rslt.inte_len = inte_len - other.inte_len + 1;
	tmp = *this;
	tmp.s = 1;
	for (int i = inte_len - other.inte_len; i >= 0; i--)
	{
		for (int j = 1; j <= MAXM; j++)
		{
			if (other * j > tmp.subnum(i, tmp.inte_len - 1))
			{
				if (j == 1 && not_zero == false)
					rslt.inte_len--;
				else
				{
					not_zero = true;
					rslt.integer[i] = j - 1;
					tmp2 = other * (j - 1);
					tmp2.inte_len += i;
					for (int k = tmp2.inte_len - 1; k >= 0; k--)
						tmp2.integer[k] = ((k - i) >= 0) ? tmp2.integer[k - i] : 0;
					tmp -= tmp2;
				}
				break;
			}
		}
	}
	if (inte_len < other.inte_len)
		rslt = 0;
	else if (rslt.inte_len == 0)
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
		if (inte_len == other.inte_len)
		{
			for (int i = 0; i < inte_len; i++)
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
		if (inte_len != other.inte_len)
			return (inte_len < other.inte_len) ? true : false;
		else
		{
			for (int i = inte_len - 1; i >= 0; i--)
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
	rslt.inte_len = end - start + 1;
	for (int i = start; i <= end; i++)
		rslt.integer[i - start] = integer[i];
	return rslt;
}

ostream &operator<<(ostream &os, BigNum const &bn)
{
	if (bn.s == (-1))
		os << "-";
	for (int i = bn.inte_len - 1; i >= 0; i--)
	{
		if (i != bn.inte_len - 1)
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
