#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }
        char *jobs_string = argv[2];

    int count = 1;
    for (int i = 0; jobs_string[i] != '\0'; i++) {
        if (jobs_string[i] == ',') {
            count++;
        }
    }

    int *jobs = malloc(count * sizeof(int));

    char *token = strtok(jobs_string, ",");
    int i = 0;

    while (token != NULL) {
        jobs[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
    }

    struct timespec t0, t1;
    timespec_get(&t0, TIME_UTC);

    float average_response;

    if (strcmp(argv[1], "FIFO") == 0) {
        average_response = FIFO(jobs, count);
    }
    else if (strcmp(argv[1], "SJF") == 0) {
        average_response = SJF(jobs, count);
    }
    else {
        printf("Scheduling policy must be FIFO or SJF.\n");
        free(jobs);
        return 1;
    }

    timespec_get(&t1, TIME_UTC);

    float dns = (float)(t1.tv_nsec - t0.tv_nsec) / 1000000000;
    float ds = (float)(t1.tv_sec - t0.tv_sec);
    float total_time = ds + dns;

    float throughput = count / total_time;

    printf("Average response time: %.6f seconds\n", average_response);
    printf("Throughput: %.6f jobs/second\n", throughput);

    free(jobs);

    return 0;
}