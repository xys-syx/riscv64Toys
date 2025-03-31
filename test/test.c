// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>



int open(char *pathname, int flags);
// int open(const char *pathname, int flags, mode_t mode);

int close(int fd);

// ssize_t read(int fd, void *buf, size_t count);
int read(int fd, void *buf, int count);

// ssize_t write(int fd, const void *buf, int count);
int write(int fd, void *buf, int count);


int pubVar;
static int privVar;
// extern int externVar;
//
int test()
{
	write(1, 2, 3);
}
//
//
//int printf(const char* __fmt, ...);

int main(int argc, char** argv)
{
	// test();

	pubVar = 123;
	privVar = 456;
	//externVar = 789;
	int stdinfd = 0;
	int stdoutfd = 1;
	int stderrfd = 2;
	
	char* str = "Hello!\n";

	write(stdoutfd, str, 7);

	int x = 3 + 5;

	/*
	if (argc > 3)
	{
		write(stdoutfd, str, 7);
		//printf("%f", t);
	}
	*/

	return x * 2;
}

//#include <stdio.h>
/*
int printf(const char* __fmt, ...);

void test()
{
	printf("%d\n", sizeof(short int));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(signed long int));
	printf("%d\n", sizeof(long long int));
	printf("%d\n", sizeof(char));
	printf("%d\n", sizeof(void*));
	printf("%d\n", sizeof(float));
	printf("%d\n", sizeof(double));
	printf("%d\n", sizeof(long double));
	printf("%d\n", sizeof(_Bool));
	printf("%d\n", sizeof(float _Complex));
	printf("%d\n", sizeof(double _Complex));
	printf("%d\n", sizeof(long double _Complex));
	printf("%d\n", sizeof(void));
}

*/