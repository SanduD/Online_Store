#pragma once
#include<vector>
#include <string>
using namespace std;
class CCustom
{
	std::string option;
	bool isOn=false;
	std::string details;
public:

	CCustom(std::string option) :option(option){}
	
	std::string get_option() { return option; }
	std::string get_details() { return details; }
	bool get_isOn() { return isOn; }
	
	bool& set_IsOn() { return this->isOn; }
	string& set_details() { return this->details; }
	~CCustom(){}
};

