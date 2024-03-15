/*
    Getting the first digits after decimal point of the constant PI
    Using Gregory-Leibniz pi approximation formula to get (PI/4)
    This is the first revision of the code, second revision uses multithreading
    to perform the task accross multiple cores of the host computer

    Author: Nur Mahmud Ul Alam Tasin (aka BigT)
    This code was written for the HSC Cracker's PI day contest
    #HSC_Crackers_Pi_Day_Contest
*/


#include <stdio.h>
#include <math.h>
#include <time.h>

double pi_by_4(unsigned long long int n){
    unsigned long long int i=0;
    double result=0.0f;
    for(i=1;i<=n;i++){
        result+=pow(-1,i+1)*(1.0/(double)(2*i-1));
    }
    return result;
}

int main(int argc, char **argv){
    unsigned long long int steps=0;
    int status = sscanf (argv[1], "%llu", &steps);
    if(status==-1){
        steps = 1000;
    }
    clock_t start_time = clock();
    double pi=(double)4*pi_by_4(steps);
    double time_taken = (double)(clock()-start_time)/(double)CLOCKS_PER_SEC;
    printf("Steps Calculated: %llu\n", steps);
    printf("Calculated Value: %.20lf\n",pi);
    printf("Actual Value    : 3.14159265358979323846\n");
    printf("Time taken      : %.5lf s \n",time_taken);
    return 0;
}