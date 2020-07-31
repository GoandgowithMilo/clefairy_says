#include <stdio.h>
#include <math.h>

int rseed = 0;

void seed(int x)
{
	rseed = x;
}


/* use of & for bitwise AND instead of modulo here. Not certain on why but it produces similar effects for powers of 2? worth looking into when I have tiworth looking into when I have time*/
int rand()
{
	return rseed = (rseed * 16087 + 1) & 2147483647;
}
