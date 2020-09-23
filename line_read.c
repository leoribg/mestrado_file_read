#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    float mean;
    uint32_t counter;

    fp = fopen("leo.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        if(isdigit(line[1])) {
            float i = atof(line);
            printf("%02f\n", i);
            counter++;
            mean += i;
            printf("mean %02f\n", mean);
        }
    }

    mean /= counter; 
    printf("final mean %02f\n", mean);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}