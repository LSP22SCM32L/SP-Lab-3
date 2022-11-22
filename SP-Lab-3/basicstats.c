/* C program that reads data from text files, and calculates mean, median, 
    and standard deviation from the set of values and shows the results */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//swap function for quicksort
void swap(float* a, float* b){
    float temp = *a;
    *a = *b;
    *b = temp;
};

//partition function for quicksort
int partition(float data[], int l, int h){
    float x = data[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++){
        if (data[j] <= x){
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap (&data[i + 1], &data[h]);
    return (i + 1);
};

//recursive quicksort function to sort the values
void quickSort(float data[], int l, int h){
    if (l < h){
        int p = partition(data, l, h);
        quickSort(data, l, p - 1);
        quickSort(data, p + 1, h);
    }
};

//function to compute the mean of values
double mean(float data[], int capacity){
    double average; 
    float sum = 0;

    for (int i = 0; i < capacity; i++){
        sum = sum + data[i];
    }

    average = (double)sum / capacity;
    return average;
};

//function to compute the median of values
float median(float data[], int capacity){
    float median;

    if (capacity % 2 == 0){
        median = (data[(capacity - 1) / 2] + data[capacity/2]) / 2;
    }
    else{
        median = data[capacity / 2];
    }
    return median;
};

//function to square a number
float square(float num){
    return (num*num);
};

//function to compute the standard deviation of values
double standard_deviation(float data[], int capacity){
    double mean1;
    double standard_deviation;
    float sum;

    mean1 = mean(data, capacity);

    for (int i = 0; i < capacity; i++){
        sum = sum + square(data[i] - mean1);
    }

    standard_deviation = (double)sqrt(sum / capacity);
    
    return standard_deviation;
};

//function to create the database using dynamic memory allocation
float * new_database(char* text_file, int* num_values, int* capacity){
    int values = 20;
    int i = 0;
    int num_data = 0;

    float* data = (float*)malloc(values * sizeof(float));

    if (data == NULL){
        exit(0);
    }

    FILE * file;
    file = fopen(text_file, "r");
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), file)){
        num_data = strtof(buffer, NULL);
        data[i] = num_data;
        i++;

        if (i == values){
            values = values * 2;

            float* new_data = (float*)malloc(values * sizeof(float));

            if (new_data == NULL){
                exit(0);
            }

            memcpy(new_data, data, values * sizeof(float));
            free(data);
            data = (float*)malloc(values * sizeof(float));
            memcpy(data, new_data, values * sizeof(float));
            free(new_data);
        }
    }

    if (feof(file)){
        fclose(file);
    }

    *capacity = values;
    *num_values = i;
    
    return data;
};

//function to print the results of math functions
void printResults(float data[], int num_values, int capacity){
    printf("\nResults:");
    printf("\n--------");
    printf("\nNum values:\t%d", num_values);
    printf("\nmean:\t%lf", mean(data, num_values));
    printf("\nmedian:\t%f", median(data, num_values));
    printf("\nstandard deviation: \t%lf", standard_deviation(data, num_values));
    printf("\nUnused array capacity:\t%d\n", (capacity - num_values));
};

//main function for storing values and displaying end result
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Wrong argument");
    }
    else{
        int num_values = 0;
        int capacity = 20;
        float* data;

        data = new_database(argv[1], &num_values, &capacity);
        quickSort(data, 0, num_values);
        printResults(data, num_values, capacity);
    }
};
