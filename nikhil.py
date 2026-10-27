def insertion(arr1):
    n = len(arr1)

    for i in range(1,n):
        key = arr1[i]
        j = i -1
        while j>=0 and key < arr1[j]:
            arr1[j +1] = arr1[j]
            j-=1
        arr1[j+1] = key
arr1 = [93,75,27,53,37]
insertion(arr1)
print('sorted array is   ', arr1)
def selection(arr1):
    n = len(arr1)
    for i in range(1,n-1):
        mini = i
        for j in range(i+1,n):
            if arr1[j] < arr1[mini]:
                mini = j 
                arr1[i], arr1[mini] = arr1[mini], arr1[i]
arr2 = [12,45,65,23,34,98]
selection(arr2)
print("sorted array is" , arr2)
def bubble(arr1):
    n = len(arr1)
    for i in range(n):
        swapped = False
        for j in range(0,n-i-1):
            if arr1[j]> arr1[j+1]:
                arr1[j], arr1[j+1] = arr1[j+1], arr1[j]
                swapped = True
        if not swapped:
            break
arr3 = [2,3,44,6,75,77,86,89]
bubble(arr3)
print('sorted array is', arr3)