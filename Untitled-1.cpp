#include <iostream>

bool SearchElement(int Array[],int ArraySize, int Target, int &IndexFound);

int main()
{
    int FoundAt;
    int TargetArray[] = {1,2,3,4,5,6,7,8,9,10};
if(SearchElement(TargetArray,10,1,FoundAt))
{
    std::cout << "Target Found at " << FoundAt+1;
}
else
{
    std::cout << "Target Not found";
}
 
}
bool SearchElement(int Array[],int ArraySize,int Target , int &IndexFound)
{
    bool _Found = false;
    for (int  i = 0; i < ArraySize; i++)
    {
        if(Array[i] == Target)
        {
            _Found = true;
            IndexFound = i;
            break;
        }
    }
    return _Found;
    
}