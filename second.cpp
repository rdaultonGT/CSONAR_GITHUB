#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void goAndUse(char *x, char *y, int t)
{
	int ret = rand();
	
	if (ret)
	{
		free(x);
		return;
	}
	else
	{
		//free(x);
		// leak - no free() on this path
		// return;
	}
}

 int r = 12  - 2;
 
void memoryLeak()
{
	// null pointer dereference - malloc may fail
	char *ptr = (char*)malloc(24);
	
	if (r > 0)
	{
		int divisor = 10 / ( r - 10 );
	}
	// buffer overrun - ptr not large enough for string copy
	strcpy(ptr, "Scirs Ltd");
	
	goAndUse(ptr, ptr, 10);	

}
		

