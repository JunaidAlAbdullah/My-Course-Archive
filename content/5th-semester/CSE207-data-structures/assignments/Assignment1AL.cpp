#include <bits/stdc++.h>
using namespace std;

struct ArrayList
{
    int *arr;
    int size;
    int capacity;
};

void init(ArrayList &list, int cap = 2)
{
    list.capacity = cap;
    list.size = 0;
    list.arr = new int[list.capacity];
}

void resize(ArrayList &list, int newCap)
{
    int *newArr = new int[newCap];

    for (int i = 0; i < list.size; i++)
    {
        newArr[i] = list.arr[i];
    }

    delete[] list.arr;
    list.arr = newArr;
    list.capacity = newCap;
}

void add(ArrayList &list, int item)
{
    if (list.size == list.capacity)
    {
        resize(list, list.capacity * 2);
    }

    list.arr[list.size] = item;
    list.size++;
}

void addbegin(ArrayList &list, int item)
{
    if (list.size == list.capacity)
    {
        resize(list, list.capacity * 2);
    }

    for (int i = list.size; i > 0; i--)
    {
        list.arr[i] = list.arr[i - 1];
    }

    list.arr[0] = item;
    list.size++;
}

void addanypos(ArrayList &list, int pos, int item)
{
    if (pos < 0 || pos > list.size)
    {
        cout << "Invalid Position\n";
        return;
    }

    if (list.size == list.capacity)
    {
        resize(list, list.capacity * 2);
    }

    for (int i = list.size; i > pos; i--)
    {
        list.arr[i] = list.arr[i - 1];
    }

    list.arr[pos] = item;
    list.size++;
}

bool contains(ArrayList &list, int item)
{
    for (int i = 0; i < list.size; i++)
    {
        if (list.arr[i] == item)
            return true;
    }
    return false;
}

int size(ArrayList &list)
{
    return list.size;
}

bool isEmpty(ArrayList &list)
{
    return list.size == 0;
}

int get(ArrayList &list, int pos)
{
    if (pos < 0 || pos >= list.size)
    {
        cout << "Invalid Position\n";
        return -1;
    }
    return list.arr[pos];
}

int indexOf(ArrayList &list, int item)
{
    for (int i = 0; i < list.size; i++)
    {
        if (list.arr[i] == item)
        {
            return i;
        }
    }
    return -1;
}

void removefirst(ArrayList &list)
{
    if (isEmpty(list))
    {
        cout << "List is empty\n";
        return;
    }

    for (int i = 0; i < list.size - 1; i++)
    {
        list.arr[i] = list.arr[i + 1];
    }

    list.size--;

    if (list.size > 0 && list.size <= list.capacity / 4)
    {
        resize(list, list.capacity / 2);
    }
}

void removelast(ArrayList &list)
{
    if (isEmpty(list))
    {
        cout << "List is empty\n";
        return;
    }

    list.size--;

    if (list.size > 0 && list.size <= list.capacity / 4)
    {
        resize(list, list.capacity / 2);
    }
}

void remove(ArrayList &list, int pos)
{
    if (pos < 0 || pos >= list.size)
    {
        cout << "Invalid Position\n";
        return;
    }

    for (int i = pos; i < list.size - 1; i++)
    {
        list.arr[i] = list.arr[i + 1];
    }

    list.size--;

    if (list.size > 0 && list.size <= list.capacity / 4)
    {
        resize(list, list.capacity / 2);
    }
}

void reverse(ArrayList &list)
{
    int i = 0, j = list.size - 1;
    while (i < j)
    {
        int temp = list.arr[i];
        list.arr[i] = list.arr[j];
        list.arr[j] = temp;
        i++;
        j--;
    }
}

void sort(ArrayList &list)
{
    for (int i = 0; i < list.size - 1; i++)
    {
        for (int j = i + 1; j < list.size; j++)
        {
            if (list.arr[i] > list.arr[j])
            {
                int temp = list.arr[i];
                list.arr[i] = list.arr[j];
                list.arr[j] = temp;
            }
        }
    }
}

void display(ArrayList &list)
{
    for (int i = 0; i < list.size; i++)
    {
        cout << list.arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    ArrayList list;
    init(list);

    add(list, 10);
    add(list, 30);
    add(list, 20);
    addbegin(list, 5);
    addanypos(list, 2, 15);

    display(list);

    cout << "Contains 20: " << contains(list, 20) << endl;
    cout << "Size: " << size(list) << endl;

    removefirst(list);
    removelast(list);
    remove(list, 1);

    display(list);

    reverse(list);
    display(list);

    sort(list);
    display(list);

    delete[] list.arr;
    return 0;
}
