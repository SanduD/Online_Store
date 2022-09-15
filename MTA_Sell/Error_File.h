#include "CException.h"

class Error_File : public CException
{
public:
	Error_File(std::string message) :CException(message) {}
	std::string get_type() override { return "Error_File"; }
	void print() override { std::cout << get_type() << " " << get_message() << std::endl; }
};