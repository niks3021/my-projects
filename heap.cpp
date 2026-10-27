#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstdlib>
void heapify(int arr[],int size,int i)
{
    int largest = i;
    int left = 2*i+1, right = 2*i+2;
    if(left<size && arr[left]>arr[largest])
    {
        largest = left;
    } 
    if(right<size && arr[right]>arr[largest])
    {
        largest = right;
    } 
    if(largest != i)
    {
        std::swap(arr[i],arr[largest]);
        heapify(arr,size,largest);
    }
}
void heapSort(int arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void countSortForDigit(int arr[], int size, int exp) {
    std::vector<int> output(size);
    int count[10] = {0}; 
    for (int i = 0; i < size; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}
void radixSort(int arr[], int size) {
    if (size <= 0) return;

    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortForDigit(arr, size, exp);
    }
}
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

void quickSort(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}
int main()
{


    return 0;
}