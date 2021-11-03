#include "Apex.h"

Apex::Apex() {

}
void Apex::SetApex(int apex) {
	APEX = (apex >= 0? apex: 0);
}

Apex::~Apex() {

}

int Apex::GetApex() {
	return APEX;
}