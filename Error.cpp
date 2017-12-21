#include "Error.h"


Error::Error()
{
	this->error_type = UNDEFINED;
}

Error::Error(const Error& other)
{
	this->error_type = other.error_type;
}

Error::~Error()
{
	this->error_type = UNDEFINED;
}

Error& Error::operator=(const Error& other)
{
	this->error_type = other.error_type;
	return *this;
}

ostream& operator<<(ostream& os, const Error& other)
{
	os << "Error";
	return os;
}
