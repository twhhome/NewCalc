#ifndef ERROR_H
#define ERROR_H

#pragma once
#include<iostream>
#include<string>
using namespace std;

enum ErrorType {DIVIDED_BY_ZERO, UNMATCHED_BRACKETS, COMPARE_IMAGINARY, UNDEFINED};
string ErrorTypeString[] = {"DIVIDED BY ZERO", "UNMATCHED BRACKETS", "TRYING TO COMPARE IMAGINARY NUMBERS"};

class Error
{
private:
	ErrorType error_type;
	int error_pos;
public:
	Error();
	Error(ErrorType errorType);
	Error(ErrorType errorType, int errorPos);
	Error(const Error& other);
	~Error();
	int get_pos() const;
	Error& operator=(const Error& other);
	friend ostream& operator<<(ostream& os, const Error& error);
};

#endif