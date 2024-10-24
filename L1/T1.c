#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc<4)
	{
		printf("%s\n","Usage: int operator int");
		return 1;	
	}

	char op = *argv[2];

	float res=0;

	if (op=='+')
	{
	res =  atoi(argv[1])+atoi(argv[3]);
	}
		
	if (op=='-')
	{
	res =  atoi(argv[1])-atoi(argv[3]);
	}
		
	if (op=='*')
	{
	res =  atoi(argv[1])*atoi(argv[3]);
	}
		
	if (op=='/')
	{
	res =  atoi(argv[1])/atoi(argv[3]);
	}

	printf("%d %c %d %s %f\n",atoi(argv[1]),op,atoi(argv[3]),"=",res);

	return 0;
}