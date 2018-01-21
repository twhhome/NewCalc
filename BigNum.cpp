#include "BigNum.h"

extern const int MAXN;
extern const int MAXM;
extern const int bit;

string strexczero(const string &str) // wipe off zeros in front of the str
{
	string rslt;
	int flag = 0;
	int book = 0;
	for (int i = 0; i < str.length(); i++)
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
	s = src.s;
	integer = src.integer;
}

void BigNum::set(const string &str)
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
	integer.clear();
	for (int i = tmp.length() - 1; i >= 0; i--)
	{
		if ((tmp.length() - i - 1) % bit == bit - 1)
			integer.push_back(string_to_int(tmp, i, i + bit - 1));
		else if (i == 0)
			integer.push_back(string_to_int(tmp, i, (tmp.length() - ((tmp.length() - i - 1) / bit) * bit - 1)));
	}
}

void BigNum::set(const char *num)
{
	string str;
	str.assign(num);
	set(str);
}

void BigNum::set(const int num)
{
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
	if (*this == 0 || other == 0)
		return (*this == 0) ? other : *this;
	BigNum rslt;
	rslt.integer.clear();
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
	rslt.integer.clear();
	if (s >= 0 && other.s >= 0)
	{
		if (*this >= other)
		{
			rslt.s = 1;
			rslt.integer.push_back(0);
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
	if (*this == 0 || other == 0)
		return 0;
	BigNum rslt, rslt_tmp;
	rslt.integer.clear();
	rslt_tmp.integer.clear();
	BigNum this_tmp, other_tmp;
	this_tmp.integer.clear();
	other_tmp.integer.clear();
	for (int i = 0; i < this->integer.size(); i++)
	{
		int tmp_num;
		tmp_num = this->integer[i];
		while (tmp_num != 0)
		{
			this_tmp.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	for (int i = 0; i < other.integer.size(); i++)
	{
		int tmp_num;
		tmp_num = other.integer[i];
		while (tmp_num != 0)
		{
			other_tmp.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	for (int i = 0; i < other_tmp.integer.size(); i++)
	{
		for (int j = 0; j < this_tmp.integer.size(); j++)
		{
			int curr;
			curr = other_tmp.integer[i] * this_tmp.integer[j];
			if (i + j > rslt_tmp.integer.size() - 1 || rslt_tmp.integer.empty())
			{
				rslt_tmp.integer.push_back(0);
			}
			rslt_tmp.integer[i + j] += curr;
		}
	}
	int len = rslt_tmp.integer.size();
	for (int i = 0; i <= len - 1; i++)
	{
		int curr = rslt_tmp.integer[i];
		rslt_tmp.integer[i] = curr % 10;
		if (i == rslt_tmp.integer.size() - 1)
			rslt_tmp.integer.push_back(0);
		rslt_tmp.integer[i + 1] += curr / 10;
	}
	if (rslt_tmp.integer[rslt_tmp.integer.size() - 1] == 0)
		rslt_tmp.integer.pop_back();
	int tmp_num = 0;
	for (int i = 0; i < rslt_tmp.integer.size(); i++)
	{
		tmp_num += rslt_tmp.integer[i] * my_pow(i % bit);
		if ((i + 1) % bit == 0)
		{
			rslt.integer.push_back(tmp_num);
			tmp_num = 0;
		}
	}
	if (tmp_num != 0)
		rslt.integer.push_back(tmp_num);
	rslt.s = s * other.s;
	return rslt;
}

BigNum BigNum::div(BigNum const &other) const
{
	BigNum rslt, rslt_tmp, tmp_this, tmp_other, tmp2;
	rslt.integer.clear();
	rslt_tmp.integer.clear();
	tmp_this.integer.clear();
	tmp_other.integer.clear();
	tmp2.integer.clear();
	bool book = false; // whether other is smaller than 0
	bool not_zero = false; // whether the first number is zero
	rslt.s = s * other.s;
	if (other.s < 0)
	{
		const_cast<BigNum&>(other).s = -other.s;
		book = true;
	}
	for (int i = 0; i < this->integer.size(); i++)
	{
		int tmp_num;
		tmp_num = this->integer[i];
		while (tmp_num != 0)
		{
			tmp_this.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	for (int i = 0; i < other.integer.size(); i++)
	{
		int tmp_num;
		tmp_num = other.integer[i];
		while (tmp_num != 0)
		{
			tmp_other.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	for (int i = 1; i <= tmp_this.integer.size() - tmp_other.integer.size() + 1; i++)
		rslt_tmp.integer.push_back(0);
	tmp_this.s = 1;
	for (int i = rslt_tmp.integer.size() - 1; i >= 0; i--)
	{
		for (int j = 1; j <= 10; j++)
		{
			BigNum tmp3, tmp4;
			tmp3 = other * j;
			tmp4.integer.clear();
			tmp4.s = 1;
			for (int k = 0; k < tmp3.integer.size(); k++)
			{
				int tmp_num;
				tmp_num = tmp3.integer[k];
				while (tmp_num != 0)
				{
					tmp4.integer.push_back(tmp_num % 10);
					tmp_num /= 10;
				}
			}
			if (tmp4 > tmp_this.subnum(i, tmp_this.integer.size() - 1))
			{
				if (j == 1 && not_zero == false)
					rslt_tmp.integer.pop_back();
				else
				{
					not_zero = true;
					rslt_tmp.integer[i] = j - 1;
					tmp3 = other * (j - 1);
					tmp4.integer.clear();
					for (int k = 0; k < tmp3.integer.size(); k++)
					{
						int tmp_num;
						tmp_num = tmp3.integer[k];
						while (tmp_num != 0)
						{
							tmp4.integer.push_back(tmp_num % 10);
							tmp_num /= 10;
						}
					}
					bool flag = false;
					for (int k = 0; k < tmp4.integer.size(); k++)
					{
						int tmp_num;
						tmp_num = tmp_this.integer[k + i] - tmp4.integer[k];
						if (flag == true)
						{
							tmp_num -= 1;
							flag = false;
						}
						if (tmp_num < 0)
						{
							tmp_num = 10 + tmp_num;
							flag = true;
						}
						tmp_this.integer[k + i] = tmp_num;
					}
					for (int k = tmp_this.integer.size() - 1; k >= 0; k--)
					{
						if (tmp_this.integer[k] != 0)
							break;
						tmp_this.integer.pop_back();
					}
				}
				break;
			}
		}
	}
	for (int i = rslt_tmp.integer.size() - 1; i >= 0; i--)
	{
		if (rslt_tmp.integer[i] != 0)
			break;
		rslt_tmp.integer.pop_back();
	}
	if (rslt_tmp.integer.empty())
		rslt = 0;
	else
	{
		int tmp_num = 0;
		for (int i = 0; i < rslt_tmp.integer.size(); i++)
		{
			tmp_num += rslt_tmp.integer[i] * my_pow(i % bit);
			if ((i + 1) % bit == 0)
			{
				rslt.integer.push_back(tmp_num);
				tmp_num = 0;
			}
		}
		if (tmp_num != 0)
			rslt.integer.push_back(tmp_num);
	}
	if (integer.size() < other.integer.size())
		rslt = 0;
	if (book) // if other is smaller than 0, then recover it
		const_cast<BigNum&>(other).s = -other.s;
	return rslt;
}

BigNum BigNum::mod(BigNum const &other) const
{
	BigNum rslt, tmp_this, tmp_other, tmp2;
	rslt.integer.clear();
	tmp_this.integer.clear();
	tmp_other.integer.clear();
	tmp2.integer.clear();
	bool book = false; // whether other is smaller than 0
	bool not_zero = false; // whether the first number is zero
	if (other.s < 0)
	{
		const_cast<BigNum&>(other).s = -other.s;
		book = true;
	}
	for (int i = 0; i < this->integer.size(); i++)
	{
		int tmp_num;
		tmp_num = this->integer[i];
		while (tmp_num != 0)
		{
			tmp_this.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	for (int i = 0; i < other.integer.size(); i++)
	{
		int tmp_num;
		tmp_num = other.integer[i];
		while (tmp_num != 0)
		{
			tmp_other.integer.push_back(tmp_num % 10);
			tmp_num /= 10;
		}
	}
	tmp_this.s = 1;
	for (int i = tmp_this.integer.size() - tmp_other.integer.size(); i >= 0; i--)
	{
		for (int j = 1; j <= 10; j++)
		{
			BigNum tmp3, tmp4;
			tmp3 = other * j;
			tmp4.integer.clear();
			tmp4.s = 1;
			for (int k = 0; k < tmp3.integer.size(); k++)
			{
				int tmp_num;
				tmp_num = tmp3.integer[k];
				while (tmp_num != 0)
				{
					tmp4.integer.push_back(tmp_num % 10);
					tmp_num /= 10;
				}
			}
			if (tmp4 > tmp_this.subnum(i, tmp_this.integer.size() - 1))
			{
				if (j == 1 && not_zero == false)
					break;
				else
				{
					not_zero = true;
					tmp3 = other * (j - 1);
					tmp4.integer.clear();
					for (int k = 0; k < tmp3.integer.size(); k++)
					{
						int tmp_num;
						tmp_num = tmp3.integer[k];
						while (tmp_num != 0)
						{
							tmp4.integer.push_back(tmp_num % 10);
							tmp_num /= 10;
						}
					}
					bool flag = false;
					for (int k = 0; k < tmp4.integer.size(); k++)
					{
						int tmp_num;
						tmp_num = tmp_this.integer[k + i] - tmp4.integer[k];
						if (flag == true)
						{
							tmp_num -= 1;
							flag = false;
						}
						if (tmp_num < 0)
						{
							tmp_num = 10 + tmp_num;
							flag = true;
						}
						tmp_this.integer[k + i] = tmp_num;
					}
					for (int k = tmp_this.integer.size() - 1; k >= 0; k--)
					{
						if (tmp_this.integer[k] != 0)
							break;
						tmp_this.integer.pop_back();
					}
				}
				break;
			}
		}
	}
	if (tmp_this.integer.empty())
		rslt = 0;
	else
	{
		int tmp_num = 0;
		for (int i = 0; i < tmp_this.integer.size(); i++)
		{
			tmp_num += tmp_this.integer[i] * my_pow(i % bit);
			if ((i + 1) % bit == 0)
			{
				rslt.integer.push_back(tmp_num);
				tmp_num = 0;
			}
		}
		if (tmp_num != 0)
			rslt.integer.push_back(tmp_num);
		rslt.s = 1;
	}
	if (book) // if other is smaller than 0, then recover it
		const_cast<BigNum&>(other).s = -other.s;
	return rslt;
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
	else if (s == 0 && other.s == 0)
		return true;
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
	else if (s == 0 && other.s == 0)
		return false;
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

BigNum BigNum::subnum(int start, int end) const
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
