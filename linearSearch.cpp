#include <iostream>
#include <vector>
#include <algorithm>
template <typename U>

int LinearSearch(std::vector<U> Input, U Target)
{
    for (int i = 0; i < Input.size(); i++)
    {
        if (Input[i] == Target)
        {
            return i;
        }
    }
    return -1;
}
template <typename U>
int BinarySearch(std::vector<U> Input , U Target)
{
    std::sort(Input.begin(),Input.end());
    int start = 0,end = Input.size()-1;
     while (start <= end) {
        int mid = start + (end - start) / 2; 

        if (Input[mid] == Target) {
            return mid;             
        }
        if (Input[mid] < Target) {
            start = mid + 1;     
        } else {
            end = mid - 1;  
        }
    }
    return -1;     
}


int main()
{
    std::vector<int> arr(5);
    int target;
     std::cout << "Enter 5 numbers:\n";
    for(int &i : arr) { 
        std::cin >> i; 
    } 
    std::cout << "Enter target: ";
    std::cin >> target;
    int result = BinarySearch(arr,target);
    (result == -1)?( std::cout << "Not Found \n"):( std::cout << "Found at: " << result <<"\n");
    return 0;
}