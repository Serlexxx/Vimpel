#pragma once
#include <iostream>
#include <math.h>

class Point 
{
	public: 
		Point* point;
	Point();
	~Point(); // äåñòðóêòîð

	void SetPoint(char point, double coord);
	double GetPoint(char point);
private:
	double x, y;
};