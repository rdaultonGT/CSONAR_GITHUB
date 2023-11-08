#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HEADERS/demo.h"
#include <time.h>

int robShared = 31;

extern void memoryLeak();

void NTAD()
{
	char *p, *p1;
	p = (char*)malloc(10);
	

	p1 = &p[3];
	if (p)
		p1 = &p[0];
}


char * retMem()
{
	return ( char*)malloc(10);
}


class Base
{
	public:
	
		
		virtual int getValue ()
			{ return 1; }
		virtual void  setField(int index)
		{
			char *buffer = (char*)"Daulton";
			
			buffer[index] = 'a';
		}
};

class Derived : public Base
{
	virtual int getValue ()
			{ return -1; }
		virtual void  setField(int index)
		{
			char *buffer = (char*)"Daulton";
			
			buffer[index] = 'a';
		}
};

 class _Y
{
	public:
		char *field;
		
};

class _X
{
	public:
	
		char * ptr;

		
		char * Method1()
		{
			ptr = new char[10];
			
			return ptr;
		}
		
		void Method2(char * ptr)
		{
			delete ptr;
		}
};

 class _Z
{
	public:
	
		_Y y;
		
		void Method3(_Y &instY)
		{
			// uninit variable
			y = instY;
			char *e = getenv("LIMIT");

			if (e!=NULL)
					Method4(atoi(e));
			
		}
		
		void Method4(int length)
		{
			int l;
			
			y.field = new char[5];
			
			for (l = 0; l <=length; l++)
			// buffer overrun y.field has 5 elements, for loop can loop though it upto index 5.
				y.field[l]  = 'q';
				
			if (length == 4)
				y.field = (char*)"HELLO";
				
			Method5(length);			
		}
		
		void Method5(int length)
		{
			if (length == 4)
			// null pointer dereference - y.field is NULL when length is 4
				strcpy(y.field, "x");
			
			delete[] y.field;
		}
};

typedef struct {
	char* start_adr;
	int num_bytes;
	void * theres_more;
} prom_phys_avail_t;

typedef struct {
	char* phys_addr;
	int reg_size;
} prom_reg_memlist_t;

void cut_past_error() // based on linux-2.6.6\arch\sparc64\prom\memory.c
{
	int iter;
	int num_regs = 63;
	prom_phys_avail_t prom_prom_taken[64];
	prom_phys_avail_t prom_phys_total[64];
	prom_reg_memlist_t prom_reg_memlist[64];
	
	for(iter=0; iter<num_regs; iter++) {
		prom_phys_total[iter].start_adr =
			prom_reg_memlist[iter].phys_addr;
		prom_phys_total[iter].num_bytes =
			prom_reg_memlist[iter].reg_size;
		prom_phys_total[iter].theres_more =
			&prom_phys_total[iter+1];
	}

	prom_prom_taken[iter-1].theres_more = 0x0;

	for(iter=0; iter<num_regs; iter++) {
		prom_prom_taken[iter].start_adr =
			prom_reg_memlist[iter].phys_addr;
		prom_prom_taken[iter].num_bytes =
			prom_reg_memlist[iter].reg_size;
		prom_prom_taken[iter].theres_more =
			&prom_phys_total[iter+1];
	}
}


int  MyThreadFunction( void * lpParam ) 
{ 
 int *shared = (int*)lpParam;
 int result = *shared + 10;
 int result1 = robShared + 20;
 
 return result;
 
}

void bigbuf()
{

	char buf[1201329834];
}


void anotherLeak()
{
	_X * instX = new _X;
	char *mem;
	
	// leak - Method1 allocates, nothing deletes it
	// unused value
	mem = instX->Method1();
	
	delete instX;
}

void ReturnCheckExample()
{
	if (puts("STRING") == EOF)
		printf("Error\n");
	if (puts("STRING 1") == EOF)
		printf("Error\n");
	if (puts("STRING 2") == EOF)
		printf("Error\n");
	if (puts("STRING 3") == EOF)
		printf("Error\n");
	if (puts("STRING 4") == EOF)
		printf("Error\n");
	if (puts("STRING 5") == EOF)
		printf("Error\n");
	if (puts("STRING") == EOF)
		printf("Error\n");
	if (puts("STRING 1") == EOF)
		printf("Error\n");
	if (puts("STRING 2") == EOF)
		printf("Error\n");
	if (puts("STRING 3") == EOF)
		printf("Error\n");
	if (puts("STRING 4") == EOF)
		printf("Error\n");
	if (puts("STRING 5") == EOF)
		printf("Error\n");
	if (puts("STRING") == EOF)
		printf("Error\n");
	if (puts("STRING 1") == EOF)
		printf("Error\n");
	if (puts("STRING 2") == EOF)
		printf("Error\n");
	if (puts("STRING 3") == EOF)
		printf("Error\n");
	if (puts("STRING 4") == EOF)
		printf("Error\n");
	if (puts("STRING 5") == EOF)
		printf("Error\n");
	if (puts("STRING") == EOF)
		printf("Error\n");
	if (puts("STRING 1") == EOF)
		printf("Error\n");
	if (puts("STRING 2") == EOF)
		printf("Error\n");
	if (puts("STRING 3") == EOF)
		printf("Error\n");
	if (puts("STRING 4") == EOF)
		printf("Error\n");
	if (puts("STRING 5") == EOF)
		printf("Error\n");

	puts("WARNING");
}

int callback()
{
	return -1;
}

void useDangerous(char * s)
{
	int z = 0;
	system(s);
}

void cast()
{
	//HANDLE MyHandle = GetStdHandle(STD_OUTPUT_HANDLE) ;

	printf("%u\n", (int)-11);
	printf("%u\n", -11);
	printf("%u\n", 11);
}
	
void divbyzero()
{

	float cFramePeriod_s = 0.1;
	
	
	const int TickStep = int( double( CLOCKS_PER_SEC ) * cFramePeriod_s ) ;
	printf("TickStep : %d\n", TickStep);
	

	int Clock = clock();
	printf("Clock : %d\n", Clock);
	printf("result : %u\n", Clock % TickStep);
	
	int Delay = TickStep - ( Clock % TickStep ) ;

}


void newError()
{

	unsigned int testUint;
	
	for (int loop =1; loop <=5; loop++)
	{
		puts("HELLO");
	}
	
	malloc(10);
}

int main(int argc, char **argv)
{
	int (*cb_func_ptr)(), index;
	
	_X * instX1 = new _X;
	_Z * instZ = new _Z;
	char *n=NULL, *o=NULL;
	char *mem1;
	myClass *mc = new myClass;
	char *buffer= (char*)"Robert";
	Base base;
	Derived derived;
	char *dangerous;
	static int shared=1;
	int unused;

	//unused += 2;

	_Y instY;
	instZ->Method3(instY);
	
	std::cout << "hello" << std::endl;

	memoryLeak();

	newError();	

	//CreateThread(NULL, 0, MyThreadFunction, (LPVOID)&shared, 0, NULL);
	
	shared++; robShared++;
	
	dangerous = getenv("TAINTED");
	
	useDangerous(dangerous);
	
	
	Base * basePtr, * basePtr1;
	
	basePtr = & base;
	basePtr1 = & derived;
	
	basePtr->setField(basePtr->getValue());
	basePtr1->setField(basePtr1->getValue());
	
	memoryLeak();
	
	retMem();
	
	cb_func_ptr = &callback;
	
	index = (*cb_func_ptr)();
	
	buffer[index] = 'a';
	
	strcpy(n, "OOps!");
	strcpy(o, "OOps!");
	// mismatched new[] / delete
	mem1 = instX1->Method1();
	instX1->Method2(mem1);
	
	
	//_Y instY;
	//instZ->Method3(instY);
	 
	// unreachable beacuse of prior null pointer dereference
	delete instX1;
	delete instZ;

	bigbuf();

	//n = mktemp("rob");

	if (n == NULL)
		return -1;
		
	return 0;
}
