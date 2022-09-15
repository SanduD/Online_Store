#pragma once
#include "IException.h"
#include <iostream>
class CException : public IException
{
	std::string message;
public:
	CException(std::string message) :message(message) {}
	std::string get_message() override { return message; }
	
};
