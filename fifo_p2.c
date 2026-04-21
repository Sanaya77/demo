#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

int main()
{
    int fd1, fd2;
    char input[SIZE], result[SIZE];
    int chars = 0, words = 0, lines = 0;

    fd1 = open("fifo1", O_RDWR);
    fd2 = open("fifo2", O_RDWR);

    if (fd1 < 0 || fd2 < 0)
    {
        printf("Error opening FIFO\n");
        return 1;
    }

    read(fd1, input, SIZE);

    for (int i = 0; input[i] != '\0'; i++)
    {
        chars++;

        if (input[i] == ' ')
            words++;

        if (input[i] == '\n')
            lines++;
    }

    if (chars > 0)
        words++;

    sprintf(result,
            "Characters: %d\nWords: %d\nLines: %d",
            chars, words, lines);

    write(fd2, result, strlen(result) + 1);

    close(fd1);
    close(fd2);

    return 0;
}
