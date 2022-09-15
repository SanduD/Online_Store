#pragma once
#include "CException.h"
class Error_Product : public CException
{
public:
	Error_Product(std::string message) :CException(message) {}
	std::string get_type() override { return "Product Error"; }
	void print() override { std::cout << get_type() << " " << get_message() << std::endl; }
};