#ifndef ERROR_H
#define ERROR_H

#pragma once
#include<iostream>
using namespace std;

enum ErrorType {DIVIDED_BY_ZERO, UNMATCHED_BRACKETS, UNDEFINED};

class Error
{
private:
	ErrorType error_type;
public:
	Error();
	Error(const Error& other);
	~Error();
	void display() const;
	Error& operator=(const Error& other);
	friend ostream& operator<<(ostream& os, const Error& error);
};

#endif