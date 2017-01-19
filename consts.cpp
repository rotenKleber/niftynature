#include "consts.hpp"
#include <time.h>

int irandom(const int &a, const int &b) {
	return rand() % (b-a+1) + a;
}
