#include "Error.h"


Error::Error()
{
	this->error_type = UNDEFINED;
	this->error_pos = -1;
}

Error::Error(ErrorType errorType, int errorPos)
{
	this->error_type = errorType;
	this->error_pos = errorPos;
}

Error::Error(const Error& other)
{
	this->error_type = other.error_type;
	this->error_pos = other.error_pos;
}

Error::~Error()
{
	this->error_type = UNDEFINED;
	this->error_pos = -1;
}

int Error::get_pos() const
{
	return this->error_pos;
}

Error& Error::operator=(const Error& other)
{
	this->error_type = other.error_type;
	this->error_pos = other.error_pos;
	return *this;
}

ostream& operator<<(ostream& os, const Error& other)
{
	os << "Error: " << ErrorTypeString[other.error_type];
	return os;
}
