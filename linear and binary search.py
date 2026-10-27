def linear(array,target):
    for i in range(len(array)):
        if array[i] == target:
            return i
    return -1
array = [10,20,30,40,60]
print(linear(array,60))
print(linear(array,50))
def binary(array,target):
    left, right = 0, len(array)-1
    while left<=right:
        mid = (left + right)//2
        if array[mid] == target:
            return mid
        elif array[mid]<target:
            left = mid+1
        else :
            left = mid-1 

array = [10,20,30,40,50]
binary(array,40)
   
