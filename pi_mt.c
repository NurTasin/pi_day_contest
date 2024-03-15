#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 4

struct thread_data {
    unsigned long long int start;
    unsigned long long int end;
    double partial_sum;
};

double pi_by_4(unsigned long long int start, unsigned long long int end) {
    double result = 0.0f;
    unsigned long long int i;

    for (i = start; i <= end; i++) {
        result += pow(-1, i + 1) * (1.0 / (double)(2 * i - 1));
    }

    return result;
}

void *compute_pi(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    my_data->partial_sum = pi_by_4(my_data->start, my_data->end);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    unsigned long long int steps = 0;
    int status = sscanf(argv[1], "%llu", &steps);
    if (status == -1) {
        steps = 1000;
    }

    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    unsigned long long int step_size = steps / NUM_THREADS;
    unsigned long long int i;

    clock_t start_time = clock();

    for (i = 0; i < NUM_THREADS; i++) {
        td[i].start = i * step_size + 1;
        td[i].end = (i + 1) * step_size;
        if (i == NUM_THREADS - 1) {
            td[i].end = steps;
        }
        pthread_create(&threads[i], NULL, compute_pi, (void *)&td[i]);
    }

    double pi = 0.0;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        pi += td[i].partial_sum;
    }

    pi *= 4;

    double time_taken = (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;

    printf("Steps Calculated: %llu\n", steps);
    printf("Calculated Value: %.20lf\n", pi);
    printf("Actual Value    : 3.14159265358979323846\n");
    printf("Time taken      : %.5lf s \n", time_taken);

    return 0;
}
