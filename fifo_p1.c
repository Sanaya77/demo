#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define SIZE 1024

int main()
{
    int fd1, fd2;
    char input[SIZE], output[SIZE];

   
    unlink("fifo1");
    unlink("fifo2");

    
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

  
    fd1 = open("fifo1", O_RDWR);
    fd2 = open("fifo2", O_RDWR);

    if (fd1 < 0 || fd2 < 0)
    {
        printf("Error opening FIFO\n");
        return 1;
    }

    printf("Enter sentence: ");
    fgets(input, SIZE, stdin);

    
    write(fd1, input, strlen(input) + 1);

    
    read(fd2, output, SIZE);

    printf("\nResult from Process 2:\n%s\n", output);

    close(fd1);
    close(fd2);

    return 0;
}
