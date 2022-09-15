#include "CMenu.h"
#include "IException.h"
#include<iostream>
using namespace std;

void main()
{
	try {
		CMenu* meniu = CMenu::getInstance();
		meniu->running();

	}
	catch (IException* exception)
	{
		exception->print();
	}
}