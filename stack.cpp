#include <iostream>
#include <cstring>

template <typename U>

class Stack
{
private:
    int size;
    U *arr;
    int top = -1;

public:
    Stack(int S) : size(S), top(-1)
    {
        arr = new U[size];
    }
    ~Stack()
    {
        delete[] arr;
    }
    bool isFull() const { return top == size - 1; }
    bool isEmpty() const { return top == -1; }
    int push(const U &val)
    {
        if (!isFull())
        {
            top++;
            arr[top] = val;
            return 1;
        }
        else
            return -1;
    }
    int pop(U &returnVal)
    {
        if (!isEmpty())
        {
            U val = arr[top];
            top--;
            returnVal = val;
            return 1;
        }
        else
            return -1;
    }
    U peek() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty"); // error
        }
        return arr[top];
    }
    void print() const
    {
        for (int i = 0; i <= top; i++)
        {
            std::cout << arr[i] << " - ";
        }
        std::cout << "Top\n";
    }
};
int precidence(char op)
{
    if (op == '^')
    {
        return 3;
    }
    if (op == '/' || op == '*')
    {
        return 2;
    }
    if (op == '-' || op == '+')
    {
        return 1;
    }
    return 0;
}
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
void infixToPostfix(const char infix[], char postfix[])
{
    int len = strlen(infix);
    Stack<char> opStack(len);
    int j = 0;
    char popped;
    for (int i = 0; i < len; i++)
    {
        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        }
        else if (infix[i] == ')')
        {
            while (!opStack.isEmpty() && opStack.peek() != '(')
            {
                opStack.pop(popped);
                postfix[j++] = popped;
                postfix[j++] = ' ';
            }
            if (!opStack.isEmpty())
            {
                opStack.pop(popped);
            }
        }
        else if (infix[i] == '(')
        {
            opStack.push(infix[i]);
        }
        else if (isOperator(infix[i]))
        {
            while (!opStack.isEmpty() && precidence(opStack.peek()) >= precidence(infix[i]))
            {
                opStack.pop(popped);
                postfix[j++] = popped;
                postfix[j++] = ' ';
            }
            opStack.push(infix[i]);
        }
    }
    while (!opStack.isEmpty())
    {
        opStack.pop(popped);
        postfix[j++] = popped;
        postfix[j++] = ' ';
    }
    if (j > 0 && postfix[j - 1] == ' ')
    {
        j--;
    }
    postfix[j] = '\0';
}
int main()
{
    Stack<char> Stck(10);
    std::string infix = "A + B * ( C ^ D - E ) ^ ( F + G * H ) - I";
    char postfix[100];
    infixToPostfix(infix.c_str(), postfix);
    std::cout << "Infix  : " << infix << std::endl;
    std::cout << "Postfix: " << postfix << std::endl;
}