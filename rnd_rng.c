#include <stdio.h>
#include "LCG.c"

int rnd_char()
{
	int lower = 97; /* ASCII character for a */
	int upper = 122; /* ASCII character for z */
	return (rand() % (upper - lower + 1)) + lower;
}
