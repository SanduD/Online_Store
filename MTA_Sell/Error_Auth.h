#pragma once
#include "CException.h"
class Error_Auth:public CException
{
public:
	Error_Auth(std::string message) :CException(message) {}
	std::string get_type() override { return "Authentification Error"; }
	void print() override { std::cout << get_type() << " " << get_message() << std::endl; }
};