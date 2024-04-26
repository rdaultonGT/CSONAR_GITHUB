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
	
	// buffer overrun - ptr not large enough for string copy
	strcpy(ptr, "Scirs Ltd");
	
	goAndUse(ptr, ptr, 10);	
}
		
#define BUF_SIZE 10

int aBuggyRoutine(int x, int y)
{
	char buf[BUF_SIZE];
	
	if (x > 1)
	{	
		if (y > 2)
		{
			strcpy(buf, "This string is too long");
		}
	}	
}

