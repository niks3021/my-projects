#include <iostream>
int const MaxSize = 100;
int array[MaxSize] = {};
int Currentsize = 0;

int display()
{
    std::cout << "\n Array is: ";
    for (int i = 0; i < Currentsize; i++)
    {
        std::cout << array[i] << "\t";
    }
}

int append(int x)
{
    if (Currentsize == MaxSize)
    {
        return -1;
    }
    Currentsize++;
    array[Currentsize - 1] = x;
    return 0;
}

int insert(int index, int x)
{
    if (Currentsize == MaxSize)
    {
        return -1;
    }
    if (index < 0 || index > Currentsize)
        return -1;
    Currentsize++;
    for (int j = Currentsize; j > index; j--)
    {
        array[j] = array[j - 1];
    }
    array[index] = x;
}

int remove(int x)
{
    if (Currentsize == 0)
        return -1;
    for (int i = 0; i < Currentsize; i++)
    {
        if (array[i] == x)
        {
            for (int j = i; j < Currentsize - 1; j++)
            {
                array[j] = array[j + 1];
            }
            Currentsize--;
            return 0;
        }
    }
    std::cout << "target not found\n";
    return -1;
}

int Linearsearch(int x)
{
    for (int i = 0; i < Currentsize; i++)
    {
        if (array[i] == x)
        {
            return i;
        }
    }
    std::cout << "Not Found\n";
    return -1;
}

int Binarysearch(int x)
{
    for (int i = 0; i < Currentsize - 1; i++)
    {
        for (int j = 0; j < Currentsize - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    std::cout << "\nSorted array is:";
    for(int i = 0;i<Currentsize;i++) {std::cout << array[i] <<"\t";}
    int low = 0;
    int high = Currentsize - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (array[mid] == x)
        {
            return mid;
        }
        else if (array[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    std::cout << "Not Found\n";
    return -1;
}

int Get(int index)
{
    if (index < 0 || index >= Currentsize)
    {
        std::cout << "Out of bounds\n";
        return -1;
    }
    return array[index];
}

void Set(int index, int x)
{
    if (index < 0 || index >= Currentsize)
    {
        std::cout << "Out of bounds\n";
        return;
    }
    array[index] = x;
}

int max()
{
    int Maximum = array[0];
    for (int i = 0; i < Currentsize; i++)
    {
        if (Maximum < array[i])
            Maximum = array[i];
    }
    return Maximum;
}

int min()
{
    int Minimum = array[0];
    for (int i = 0; i < Currentsize; i++)
    {
        if (Minimum > array[i])
            Minimum = array[i];
    }
    return Minimum;
}

int reverse()
{
    for (int i = 0; i < Currentsize / 2; i++)
    {
        int temp = array[i];
        array[i] = array[Currentsize - 1];
        array[Currentsize - 1] = temp;
    }
}

int shift() // right
{
    int last = array[Currentsize - 1];
    for (int i = Currentsize - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = last;
}

void rotate() //to right
{
    if (Currentsize <= 1) return;
    int lastElement = array[Currentsize - 1]; 
    for (int i = Currentsize - 1; i > 0; i--) {
        array[i] = array[i - 1];
    }
    array[0] = lastElement; 
}

int main()
{
    append(5);
    append(6);
    append(9);
    append(-2);
    display();
    insert(0, 1);
    append(-5);
    display();
    remove(5);
    display();
    std::cout << "\nSearching -2 found at: " << Linearsearch(-2);
    std::cout << "\nvalue at index 2 is: " << Get(2);
    std::cout << "\nSetting index 1 to 5";
    Set(1, 5);
    display();
    std::cout << "\nMaximum is: " << max() << " Minimum is: " << min() << "\n";
    reverse();
    display();
    shift();
    display();
    std::cout << "\n5 found at index: "<< Binarysearch(-2);
    rotate();
    display();
}
