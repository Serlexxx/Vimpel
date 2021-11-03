#include "Point.h"


Point::Point() {
	
}


Point::~Point() {

}



void Point::SetPoint(char point, double coord) {
	switch (point)
	{
	case 'x':
		x = coord;
		break;
	case 'y':
		y = coord;
		break;
	}
}

double Point::GetPoint(char point) {
	switch (point)
	{
	case 'x':
		return x;
		break;
	case 'y':
		return y;
		break;
	}
}