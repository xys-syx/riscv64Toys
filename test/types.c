// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>

typedef int ssize_t ;
typedef int size_t ;

int i, *pi, **ppi, ai[3], aai[5][6];

int close(int fd);

int open(const char *pathname, int flags);

ssize_t write(int fd, const void *buf, size_t count);

ssize_t read(int fd, void *buf, size_t count);

int f(), *f(), (*f)();
//  a function returning an integer, a function returning a pointer to an integer, a pointer to a function returning an integer; 

int *api[10], (*pai)[10];
// an array of pointers to integers,
// and a pointer to an array of integers. 
// In all these cases the declaration of a variable resembles its usage in an expression whose type is the one named at the head of the declaration. 

int *(*pfp)();
// a pointer to a function returning a pointer to an integer.

int x();
int (x)(int a, int b);
typedef int (t)(int a, int b);

int (asd)(double a), (zxc)(float b);

void (*func_ptrs[3])() = { fun1, fun2, fun3 };

int (*func_ptrs[3])(int (*a[5])(), int b[4]);
int (*getFunc(void))(int, int);
int (*(*getFunc2(void))(int))(int, int);
int (*(*(*getFuncArr[4])(void))(int))(int, int);

int (*idputs(int (*puts)(const char *)))(const char *) {
    return puts;
}

int *x, y[10], z[2][1+1+1];
char **ptr;

void printf(char* s);

int main(int argc, char** argv)
{
	int z;

	printf("1");

	int arr[10][20], foo;
	int *ptr;
	
	int x = argc;
	arr[x + 3][2] = 5;
	int a = 3;

	return 0;
}

