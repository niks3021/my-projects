#include <iostream>
#include <vector>
int bubblesort(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
void insertionSort(int arr[], int size)
{

    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size)
{
    int min = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        min = i;
        for (size_t j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
    }
}
void shellSort(int arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int j = gap; j < size; j++)
        {
            int temp = arr[j];
            int k = j;

            while (k >= gap && arr[k - gap] > temp)
            {
                arr[k] = arr[k - gap];
                k -= gap;
            }

            arr[k] = temp;
        }
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

void quicksort(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);
    quicksort(arr, low, pivotIndex - 1);
    quicksort(arr, pivotIndex + 1, high);
}

void heaping(int arr[], int size, int i)
{
    int largest = i;
    int left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heaping(arr, size, largest);
    }
}
void heapSort(int arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heaping(arr, size, i); // build max heap first
    }

    for (int i = size - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]); // extract root
        heaping(arr, i, 0); // rebuild and fix the heap
    }
}
void countingSort(int arr[], int size)
{
    if (size <= 0)
        return;
    int maxval = 0;
    for (int i = 0; i < size; i++)
    {
        if (maxval < arr[i])
            maxval = arr[i];
    }

    std::vector<int> count(maxval + 1);
    for (int i = 0; i < size; i++)
    {
        count[arr[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= maxval; i++)
    {
        while (count[i] > 0)
        {
            arr[index++] = i;
            count[i]--;
        }
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
int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24};
    int size = sizeof(arr) / sizeof(int);
    // bubblesort(arr,size);
    // mergeSort(arr,0,size-1);
    // insertionSort(arr,size);
    // selectionSort(arr,size);
    // shellSort(arr, size);
    // quicksort(arr, 0, size - 1);
    // heapSort(arr,size);
    // countingSort(arr,size);
    // radixSort(arr,size);
    for(int A : arr)
    {
        std::cout << A << " ";
    }
    return 0;
}