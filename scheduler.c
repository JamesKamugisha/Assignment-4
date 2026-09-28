#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"


float SJF(int* jobs, int size) {
   if (size <= 0) {
        return -1.0f;
    }

    int *sorted_jobs = malloc(size * sizeof(int));

    for(int i=0; i<size; i++) {
        sorted_jobs[i] = jobs[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_jobs[j] > sorted_jobs[j + 1]) {
                int temp = sorted_jobs[j];
                sorted_jobs[j] = sorted_jobs[j + 1];
                sorted_jobs[j + 1] = temp;
            }
        }
    }

    float elapsed_time = 0;
    float response_time = 0;

    for (int i = 0; i < size; i++) {
        float job_time = do_job(sorted_jobs[i],
                                sorted_jobs[i],
                                sorted_jobs[i],
                                0);

        elapsed_time += job_time;
        response_time += elapsed_time;
    }

    free(sorted_jobs);

    return response_time / size;
}

float FIFO(int* jobs, int size) {
    if(size <= 0) {
        return -1.0;
    }
    float elapsed_time = 0;
    float response_time = 0;

    for(int i=0; i<size; i++){
        float job_time = do_job(jobs[i], jobs[i], jobs[i], 0);
        elapsed_time += job_time;
        response_time += elapsed_time;
    }
    return response_time / size;

}
