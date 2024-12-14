#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    int data;
    Node* next;
};

void addNode(Node*& head, int value)
{
    Node* newNode = new Node{value, nullptr};
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool hasDuplicateDigits(int number)
{
    bool digitFound[10] = {false};
    while (number > 0)
    {
        int digit = number % 10;
        if (digitFound[digit])
        {
            return true;
        }
        digitFound[digit] = true;
        number /= 10;
    }
    return false;
}

int getFirstDigit(int number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    return number;
}

void sortListByFirstDigit(Node*& head)
{
    std::vector<int> values;
    Node* current = head;

    while (current != nullptr)
    {
        values.push_back(current->data);
        current = current->next;
    }

    std::sort(values.begin(), values.end(), [](int a, int b)
    {
        return getFirstDigit(a) < getFirstDigit(b);
    });

    Node* newHead = nullptr;
    for (int value : values)
    {
        addNode(newHead, value);
    }

    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    head = newHead;
}

void processList(Node*& head)
{
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr)
    {
        if (current->data % 2 == 0)
        {
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        else
        {
            Node* newNode = new Node{current->data, current->next};
            current->next = newNode;
            prev = newNode->next;
            current = newNode->next;
        }
    }
}

void printList(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main()
{
    Node* head = nullptr;
    int n;

    std::cout << "enter number of values: ";
    std::cin >> n;

    std::cout << "enter values: ";
    for (int i = 0; i < n; ++i)
    {
        int value;
        std::cin >> value;
        addNode(head, value);
    }

    bool hasDuplicates = false;
    Node* current = head;
    
    while (current != nullptr)
    {
        if (hasDuplicateDigits(current->data))
        {
            hasDuplicates = true;
            break;
        }
        current = current->next;
    }

    if (hasDuplicates)
    {
        sortListByFirstDigit(head);
    }
    else
    {
        processList(head);
    }

    std::cout << "result: ";
    printList(head);

    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}