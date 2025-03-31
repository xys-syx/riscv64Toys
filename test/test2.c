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
        write(1, "Hello ", 6);
}

int main(int argc, char** argv)
{
        test();

        pubVar = 123;
        privVar = 456;
        //externVar = 789;
        int stdinfd = 0;
        int stdoutfd = 1;
        int stderrfd = 2;

        char* str = "world! ";

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

