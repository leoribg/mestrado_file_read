#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LSIZ 128
#define RSIZ 10

int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *meas_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    float mean;
    uint32_t counter;
    char str[80];

    meas_file = fopen("../mestrado_file_plot/meas.txt", "w+");
    //meas_file = fopen("meas.txt", "w+");

    for (int i = 1; i < argc; i++)
    {
        counter = 0;
        mean = 0;

        printf("argv %d: %s\n", i, argv[i]);

        /* To calculate signal mean power from file */
        fp = fopen(argv[i], "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);

        while ((read = getline(&line, &len, fp)) != -1)
        {
            //printf("Retrieved line of length %zu:\n", read);
            //printf("%s", line);
            if (isdigit(line[1]))
            {
                float i = atof(line);
                //printf("%02f\n", i);
                counter++;
                mean += i;
                //printf("mean %02f\n", mean);
            }
        }
        mean /= counter;
        //printf("final mean %02f\n", mean);
        sprintf(str, "%02d,%f\n", (i - 1), mean);
        printf("%s", str);
        if(i < 100) {
            fwrite(str , 1 , 14 , meas_file );
        }
            
        memset(str, 0x00, 80);
        fclose(fp);
    }
    fclose(meas_file);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}