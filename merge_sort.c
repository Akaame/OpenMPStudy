#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void print_array(int* data, int n)
{
    int i = 0;
    for(i; i<n; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void swap_int(int* data, int i, int j)
{
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

void merge(int* data, int n, int midpoint)
{
    int* temp_arr = (int*)malloc(sizeof(int)*n);
    int i=0;
    int j=midpoint;
    int counter = 0;
    while(counter<n)
    {
        if(i==midpoint)
        {
            temp_arr[counter] = data[j];
            j++;
        }
        else if(j==n)
        {
            temp_arr[counter] = data[i];
            i++;
        }
        else if(data[i] < data[j])
        {
            temp_arr[counter] = data[i];
            i++;
        }
        else
        {
            temp_arr[counter] = data[j];
            j++;
        }
        counter++;
    }
    i = 0;
    for(i;i<n;i++)
    {
        data[i] = temp_arr[i];
    }
    return;
}

void merge_sort(int* data, int n)
{
    if(n==2){
        if(data[0]>data[1]){
            swap_int(data,0,1);
        }
        return;
    }
    else if(n==1 || n==0){
        return;
    }
    else{
        int midpoint = n/2;
        /*
        printf("First part of data\n");
        print_array(data,midpoint);
        printf("Second part of data\n");
        print_array(&data[midpoint],n-midpoint);
        */
        merge_sort(data, midpoint);
        merge_sort(&data[midpoint], n-midpoint);
        // swap data
        merge(data, n, midpoint);
    }
}

int main(int argc, char** argv)
{
    int num_threads = 8;
    omp_set_num_threads(num_threads); // sets number of threads.
    // if not set threads as many as cpu cores
    int count = 34;
    int arr[count];
    int i = 0;
    for(i;i<count;i++)
    {
        arr[i] = count - i;
    }
    int data_count = count;
    if(data_count%num_threads != 0){
        data_count += num_threads - data_count%num_threads;
    }
    int surplus = data_count -count;
    int* data = calloc(sizeof(int),data_count);
    i = 0;
    for(i;i<count;i++)
    {
        data[i] = arr[i];
    }
    print_array(data, data_count);
    // data test
    // print_array(data, data_count);
    
    // swap test
    // swap_int(data, 3, 10);
    // print_array(data, data_count);

    int part_len = data_count / num_threads;
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        int a = ID * part_len;
        int b = (ID+1) * part_len;
        // printf("I am in thread %d\n", ID);
        // print_array(&data[a], b-a);
        merge_sort(&data[a], part_len);
    }
    // swap data TODO
    print_array(data, data_count);
    for(part_len; part_len<data_count;part_len*=2)
    {
        i = 0;
        for(i;i<num_threads-1;i+=2)
        {
            int a = i*part_len;
            int b = (i+2)*part_len;
            merge(&data[a], b-a, part_len);
        }
        print_array(data, data_count);
        num_threads/=2;
    }
    print_array(&data[surplus], data_count-surplus);
    return 0;
}

