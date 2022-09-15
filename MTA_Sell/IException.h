#pragma once
#include <string>
class IException
{
public:
	virtual void print() = 0;
	virtual std::string get_message() = 0;
	virtual std::string get_type() = 0;
};