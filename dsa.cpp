#include <iostream>

int findElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i; 
    }
    return -1; 
}

int findMultiple(int arr[], int size, int target, int indices[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            indices[count++] = i;
        }
    }
    return count; 
}

void findDuplicatesSorted(int arr[], int size) {
    std::cout << "Duplicates (Sorted): ";
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            int j = i + 1;
            while (j < size && arr[j] == arr[i]) j++;
            std::cout << arr[i] << " (Count: " << (j - i) << ")  ";
            i = j - 1; 
        }
    }
    std::cout << "\n";
}

void findDuplicatesUnsorted(int arr[], int size) {
    std::cout << "Duplicates (Unsorted): ";
    for (int i = 0; i < size; i++) {
        int count = 1;
        if (arr[i] != -1) { 
            for (int j = i + 1; j < size; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                    arr[j] = -1; 
                }
            }
            if (count > 1) {
                std::cout << arr[i] << " (Count: " << count << ")  ";
            }
        }
    }
    std::cout << "\n";
}

void findPairSumUnsorted(int arr[], int size, int K) {
    std::cout << "Pairs with sum " << K << " (Unsorted): ";
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == K) {
                std::cout << "(" << arr[i] << ", " << arr[j] << ") ";
            }
        }
    }
    std::cout << "\n";
}

void findPairSumSorted(int arr[], int size, int K) {
    std::cout << "Pairs with sum " << K << " (Sorted): ";
    int low = 0;
    int high = size - 1;

    while (low < high) {
        int sum = arr[low] + arr[high];
        if (sum == K) {
            std::cout << "(" << arr[low] << ", " << arr[high] << ") ";
            low++;
            high--;
        } else if (sum < K) {
            low++;
        } else {
            high--;
        }
    }
    std::cout << "\n";
}

void findMaxMin(int arr[], int size, int &maxVal, int &minVal) {
    if (size <= 0) return;
    
    maxVal = arr[0];
    minVal = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        } else if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
}

int main() {
    int searchArr[] = {10, 20, 30, 20, 40, 20, 50};
    int sizeSearch = 7;
    int index = findElement(searchArr, sizeSearch, 30);
    std::cout <<"Single element 30 found at index: " << index;
    int foundIndices[7];
    int occurrences = findMultiple(searchArr, sizeSearch, 20, foundIndices);
    std::cout << "Element 20 found " << occurrences << " times at indices: ";
    for (int i = 0; i < occurrences; i++) std::cout << foundIndices[i] << " ";
    std::cout << "\n\n";
    int sortedArr[] = {1, 2, 2, 2, 3, 4, 4, 5, 8, 8};
    findDuplicatesSorted(sortedArr, 10);
    int unsortedArr[] = {8, 3, 1, 3, 8, 3, 9, 1};
    findDuplicatesUnsorted(unsortedArr, 8);
    std::cout << "\n";
    int pairUnsorted[] = {6, 3, 8, 4, 2, 7, 1};
    findPairSumUnsorted(pairUnsorted, 7, 10);
    int pairSorted[] = {1, 2, 3, 4, 6, 7, 8};
    findPairSumSorted(pairSorted, 7, 10);
    std::cout << "\n";
    int mixArr[] = {25, 12, 99, 4, 67, -3, 45};
    int maxVal, minVal;
    findMaxMin(mixArr, 7, maxVal, minVal);
    std::cout <<"Max value: " << maxVal << " | Min value: " << minVal;
    return 0;
}