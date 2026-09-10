#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *createNode(int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void add(Node *&head, int value)
{
    Node *newNode = createNode(value);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void addbegin(Node *&head, int value)
{
    Node *newNode = createNode(value);

    newNode->next = head;
    head = newNode;
}

void addanypos(Node *&head, int pos, int value)
{
    if (pos == 0)
    {
        addbegin(head, value);
        return;
    }

    Node *temp = head;
    for (int i = 0; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Invalid Position\n";
        return;
    }

    Node *newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
}

bool contains(Node *&head, int value)
{
    Node *temp = head;

    while (temp != NULL)
    {
        if (temp->data == value)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int size(Node *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

bool isEmpty(Node *head)
{
    if (head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get(Node *head, int pos)
{
    if (pos < 0)
    {
        cout << "Invalid Position\n";
        return -1;
    }

    int index = 0;
    while (head != NULL)
    {
        if (index == pos)
        {
            return head->data;
        }

        head = head->next;
        index++;
    }

    cout << "Position Out of Range\n";
    return -1;
}

int indexOf(Node *head, int item)
{
    int index = 0;

    while (head != NULL)
    {
        if (head->data == item)
            return index;

        head = head->next;
        index++;
    }

    return -1;
}

void removefirst(Node *&head)
{
    if (head == NULL)
    {
        cout << "Linked List is empty" << endl;
    }
    else
    {
        Node *temp = head;
        head = head->next;

        delete temp;
    }
}

void removelast(Node *&head)
{
    if (head == NULL)
    {
        cout << "Linked List is empty" << endl;
    }
    else if (head->next == NULL)
    {
        delete head;
        head = NULL;
    }
    else
    {
        Node *temp = head;

        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }

        delete temp->next;

        temp->next = NULL;
    }
}

void remove(Node *&head, int pos)
{
    if (head == NULL)
    {
        cout << "List is empty\n";
        return;
    }

    if (pos == 0)
    {
        removefirst(head);
        return;
    }

    Node *temp = head;

    for (int i = 0; i < pos - 1 && temp->next != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        cout << "Invalid Position\n";
        return;
    }

    Node *delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;
}

void reverse(Node *&head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *nextNode = NULL;

    while (curr != NULL)
    {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    head = prev;
}

void sort(Node *head)
{
    if (head == NULL)
    {
        return;
    }

    Node *i, *j;
    int temp;

    for (i = head; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->data > j->data)
            {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void display(Node *head)
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }

    Node *temp = head;

    while (temp != NULL)
    {
        cout << temp->data << "->";
        temp = temp->next;
    }

    cout << "NULL\n";
}

int main()
{
    Node *head = NULL;

    add(head, 10);
    add(head, 30);
    add(head, 20);
    add(head, 50);

    addbegin(head, 5);

    addanypos(head, 2, 15);

    cout << "List elements: ";
    Node *temp = head;
    display(head);

    cout << "NULL\n";

    cout << "Contains 20? " << contains(head, 20) << endl;
    cout << "Contains 100? " << contains(head, 100) << endl;

    cout << "Size: " << size(head) << endl;

    cout << "Is Empty? " << isEmpty(head) << endl;

    cout << "Element at position 3: " << get(head, 3) << endl;

    cout << "Index of 50: " << indexOf(head, 50) << endl;

    removefirst(head);

    removelast(head);

    remove(head, 2);

    cout << "After deletions: ";
    temp = head;
    display(head);

    reverse(head);
    cout << "After reverse: ";
    temp = head;
    display(head);

    sort(head);
    cout << "After sorting: ";
    temp = head;
    display(head);

    return 0;
}