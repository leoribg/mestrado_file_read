#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LSIZ 128 
#define RSIZ 10 

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    float mean;
    uint32_t counter;

    char channel_files[128][32];
    uint8_t channel_index = 0;
    
    for(int i = 0; i < channel_index; i++)
        memset(channel_files[i], 0x00, 32);
    
    /* To read a list in a file */
    fp = fopen("channel_list.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        memcpy(channel_files[channel_index], line, read);
        channel_index++;
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    for(int i = 0; i < channel_index; i++)
        printf("%s", channel_files[i]);

    /* To calculate signal mean power from file */
    fp = fopen("leo.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        if(isdigit(line[1])) {
            float i = atof(line);
            //printf("%02f\n", i);
            counter++;
            mean += i;
            //printf("mean %02f\n", mean);
        }
    }
    mean /= counter; 
    printf("final mean %02f\n", mean);
    fclose(fp);

    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}