#include <stdio.h>
#include <iostream>

static int var;


char * header_retMem()
{
	return (char*)malloc(10);
}


//extern char*  retMem();

void callretMem()
{
	header_retMem();
}

class myClass
{
	public:
		~myClass()
		{
			std::cout << "DELETING" << std::endl;
			//delete this;
		}
};
