#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int *ptr; // address of first num
	int size; // array size

	
	printf("Enter size of array:");
	scanf("%d",&size);

	// dynamic allocate mem to ptr
	ptr = (int*)malloc(size*sizeof(int));

	if (ptr==NULL)
	{
		printf("Malloc Failed");
		exit(0);
	}

	printf("Enter elements:\n");
	int elem;
	for (int i = 0; i < size; ++i)
	{
		scanf("%d",&elem);
		ptr[i]= elem;
	}

	char op;

	printf("Enter operation:");
	scanf(" %c",&op);


	double res=ptr[0];


	for (int i = 1; i < size; ++i)
	{
		if (op=='+'){res = res+ptr[i];continue;}
		if (op=='-'){res = res-ptr[i];continue;}
		if (op=='*'){res = res*ptr[i];continue;}
		if (op=='/'){res = res/ptr[i];continue;}

	}

	
	printf("%s %f\n","Result = ",res);
	return 0;
}