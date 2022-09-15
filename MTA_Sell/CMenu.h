#pragma once
class CMenu
{
public:
	static CMenu* getInstance();
	static void DestroyInstance();
	void running();
private:
	CMenu() {}
	~CMenu() {}
	static CMenu* instance;
};

