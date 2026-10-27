#include <stdio.h>
int main()
{
    int i,j,mid;
    int n;
    printf("enter array size");
    scanf("%d",&n);
    int arr[n];
    printf("enter array elements ");
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for ( i = 0; i < n-1; i++)
    {
        for ( j = 0; j < n-1-i; j++)
        {
            if (arr[j]>arr[j+1])
            {
                int temp =0;
                temp =arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;    
            }
            
        }
        
    }
    printf("enter target to search");
    int target;
    scanf("%d",&target);
     int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {printf("\n%d",mid);break;} 
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

   
}