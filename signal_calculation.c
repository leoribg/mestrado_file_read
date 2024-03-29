#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LSIZ 128
#define RSIZ 10

#define NOISE_FLOOR (-150)
#define BUSY_LEVEL (-85)

int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *meas_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    float mean = 0;
    uint32_t counter = 0;
    char str[80];
    /*occupancy*/
    uint32_t occ_counter = 0;
    uint8_t occupancy = 0;

    meas_file = fopen("../mestrado_file_plot/meas.txt", "w+"); // file to save channel average power and occupancy
    //meas_file = fopen("meas.txt", "w+");

    if(argc == 1) {
        printf("No channel measures files were specified");
    }

    for (int i = 1; i < argc; i++)
    {
        counter = 0;
        mean = 0;
        occ_counter = 0;

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
                float j = atof(line);
                //printf("%02f\n", i);
                if(j > NOISE_FLOOR) {
                    counter++;
                    mean += j;
                }
                if(j > BUSY_LEVEL) {
                    occ_counter++;
                }
                //printf("mean %02f\n", mean);
            }
        }
        mean /= counter;
        occupancy = (occ_counter * 100) / counter;
        //printf("occupancy: %02d \n", occupancy);
        //printf("final mean %02f\n", mean);
        sprintf(str, "%02d,%f,%03d\n", (i - 1), mean, occupancy);
        printf("%s", str);
        if(i < 100) { //SANITY CHECK FOR MAXIMUM CHANNELS
            fwrite(str , 1 , strlen(str) , meas_file );
        }
            
        memset(str, 0x00, 80);
        fclose(fp);
    }
    fclose(meas_file);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}