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

	char *ptr = (char*)malloc(24);
	// null pointer dereference - malloc may fail

	strcpy(ptr, "Scirs Ltd");
	
	goAndUse(ptr, ptr, 10);	
}

int newFunc(int x)
{
	int uninit;

	if (x > 1)
		uninit = 10;

	printf("%d\n",uninit);
}
		

