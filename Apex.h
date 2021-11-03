#pragma once
#include <iostream>

class Apex {
public:
    Apex();
	void SetApex(int apex);
	~Apex();

	int GetApex();
private:
	int APEX = 0;
};