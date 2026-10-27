#include <iostream>
#include <cstdlib>
#include<time.h>


int partition(int arr[], int low, int high) // for quick sort
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);
    quicksort(arr, low, pivotIndex - 1);
    quicksort(arr, pivotIndex + 1, high);
}

int main()
{
    srand(time(0));
    const int SIZE = 100000;
    int * array = new int[SIZE];
    for(int i = 0 ;i < SIZE;i++)
    {
        array[i] = rand()%(100) + 1;
    }
    std::cout << "Starting QuickSort\n";
    quicksort(array,0,SIZE-1);
    std::cout << "Quick Sort Done\n " << array[0] << " is First " << array[SIZE-1] << " Is Last\n";
    for(int i = 0 ;i < SIZE;i++)
    {
        array[i] = rand()%(100000) + 1;
    }
        std::cout << "Starting QuickSort\n";
    quicksort(array,0,SIZE-1);
    std::cout << "Quick Sort Done\n " << array[0] << " is First " << array[SIZE-1] << " Is Last\n";
    delete[] array;
    
}