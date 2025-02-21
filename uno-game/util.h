#pragma once

#include <random>
#include "config.h"
#include <time.h>

float rand0to1();
inline int rand0to14() {
	return rand() % RANDMAX;
}
inline char randcolor() {
	int c = rand() % 5;
	switch (c){
	case 1: return 'r';
	case 2: return 'g';
	case 3: return 'b';
	case 4: return 'y';
	}
}
