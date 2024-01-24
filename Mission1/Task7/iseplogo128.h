#include <stdio.h>

unsigned char motif[128 * 8];
int main()
{
	// Method 1: Using a loop
	for (int i = 0; i < sizeof(motif); i++)
	{
		motif[i] = 0x00;
	}
	return 0;
}