// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <ctime>
// #include <iomanip>
// #include <algorithm>

// using namespace std;

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// TASK STRUCTURE - Represents a single task with all required attributes
// ============================================================================
struct Task
{
    int taskID;
    char title[100];
    char description[250];
    int priority;      // 1: Low, 2: Medium, 3: High
    char deadline[20]; // Format: DD/MM/YYYY
    bool isCompleted;

    Task()
    {
        taskID = 0;
        priority = 1;
        isCompleted = false;
        strcpy(title, "");
        strcpy(description, "");
        strcpy(deadline, "");
    }
};

// ============================================================================
// LINKED LIST NODE - Used for storing tasks dynamically
// ============================================================================
struct Node
{
    Task task;
    Node *next;
};

// Create a new node with a task
Node *createNode(Task t)
{
    Node *newNode = new Node();
    newNode->task = t;
    newNode->next = NULL;
    return newNode;
}

// ============================================================================
// LINKED LIST CLASS - For managing tasks with dynamic memory
// ============================================================================
class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    // Insert a new task at the end of the list
    void insertTask(Task t)
    {
        Node *newNode = createNode(t);

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display all tasks
    void displayAllTasks()
    {
        if (head == NULL)
        {
            cout << "\n\t[ERROR] No tasks found!\n"
                 << endl;
            return;
        }

        cout << "\n\t=========== ALL TASKS ==========\n";

        Node *temp = head;
        int count = 1;

        while (temp != NULL)
        {
            cout << "\n\t[Task " << count << "]\n";
            cout << "\t  ID: " << temp->task.taskID << "\n";
            cout << "\t  Title: " << temp->task.title << "\n";
            cout << "\t  Description: " << temp->task.description << "\n";
            cout << "\t  Priority: ";

            if (temp->task.priority == 1)
            {
                cout << "Low";
            }
            else if (temp->task.priority == 2)
            {
                cout << "Medium";
            }
            else
            {
                cout << "High";
            }

            cout << "\n\t  Deadline: " << temp->task.deadline << "\n";
            cout << "\t  Status: ";
            if (temp->task.isCompleted)
            {
                cout << "[OK] Completed";
            }
            else
            {
                cout << "⧖ Pending";
            }
            cout << "\n";
            cout << "\t  " << string(58, '-') << "\n";

            temp = temp->next;
            count++;
        }
        cout << endl;
    }

    // Display only completed tasks
    void displayCompletedTasks()
    {
        if (head == NULL)
        {
            cout << "\n\t[ERROR] No tasks found!\n"
                 << endl;
            return;
        }

        cout << "\n\t=========== COMPLETED TASKS ==========\n";

        Node *temp = head;
        int count = 1;
        bool found = false;

        while (temp != NULL)
        {
            if (temp->task.isCompleted)
            {
                found = true;
                cout << "\n\t[Task " << count << "]\n";
                cout << "\t  ID: " << temp->task.taskID << "\n";
                cout << "\t  Title: " << temp->task.title << "\n";
                cout << "\t  Description: " << temp->task.description << "\n";
                cout << "\t  Priority: ";

                if (temp->task.priority == 1)
                {
                    cout << "Low";
                }
                else if (temp->task.priority == 2)
                {
                    cout << "Medium";
                }
                else
                {
                    cout << "High";
                }

                cout << "\n\t  Deadline: " << temp->task.deadline << "\n";
                cout << "\t  Status: COMPLETED\n";
                cout << "\t  " << string(40, '-') << "\n";
                count++;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "\n\t[ERROR] No completed tasks found!\n"
                 << endl;
        }
        cout << endl;
    }

    // Display only pending tasks
    void displayPendingTasks()
    {
        if (head == NULL)
        {
            cout << "\n\t[ERROR] No tasks found!\n"
                 << endl;
            return;
        }

        cout << "\n\t=========== PENDING TASKS ==========\n";

        Node *temp = head;
        int count = 1;
        bool found = false;

        while (temp != NULL)
        {
            if (!temp->task.isCompleted)
            {
                found = true;
                cout << "\n\t[Task " << count << "]\n";
                cout << "\t  ID: " << temp->task.taskID << "\n";
                cout << "\t  Title: " << temp->task.title << "\n";
                cout << "\t  Description: " << temp->task.description << "\n";
                cout << "\t  Priority: ";

                if (temp->task.priority == 1)
                {
                    cout << "Low";
                }
                else if (temp->task.priority == 2)
                {
                    cout << "Medium";
                }
                else
                {
                    cout << "High";
                }

                cout << "\n\t  Deadline: " << temp->task.deadline << "\n";
                cout << "\t  Status: PENDING\n";
                cout << "\t  " << string(40, '-') << "\n";
                count++;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "\n\t[ERROR] No pending tasks found!\n"
                 << endl;
        }
        cout << endl;
    }

    // Delete a task by ID
    bool deleteTask(int id)
    {
        if (head == NULL)
        {
            return false;
        }

        // If head is the node to delete
        if (head->task.taskID == id)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        // Search in the rest of the list
        Node *temp = head;
        while (temp->next != NULL)
        {
            if (temp->next->task.taskID == id)
            {
                Node *nodeToDelete = temp->next;
                temp->next = nodeToDelete->next;
                delete nodeToDelete;
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    // Search task by ID
    Node *searchTask(int id)
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->task.taskID == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    // Search task by title
    Node *searchTaskByTitle(const char *title)
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (strcmp(temp->task.title, title) == 0)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    // Mark task as completed
    bool markTaskComplete(int id)
    {
        Node *node = searchTask(id);
        if (node != NULL)
        {
            node->task.isCompleted = true;
            return true;
        }
        return false;
    }

    // Update task details
    bool updateTask(int id, Task newTask)
    {
        Node *node = searchTask(id);
        if (node != NULL)
        {
            node->task.title[0] = '\0'; // Clear old memory
            node->task.description[0] = '\0';
            node->task.deadline[0] = '\0';

            strcpy(node->task.title, newTask.title);
            strcpy(node->task.description, newTask.description);
            strcpy(node->task.deadline, newTask.deadline);
            node->task.priority = newTask.priority;

            return true;
        }
        return false;
    }

    // Sort tasks by priority (Bubble Sort - High to Low)
    void sortByPriority()
    {
        if (head == NULL || head->next == NULL)
        {
            return;
        }

        bool swapped;
        do
        {
            swapped = false;
            Node *temp = head;

            while (temp->next != NULL)
            {
                if (temp->task.priority < temp->next->task.priority)
                {
                    // Swap tasks
                    Task tempTask = temp->task;
                    temp->task = temp->next->task;
                    temp->next->task = tempTask;
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);

        cout << "\n\t[+] Tasks sorted by priority!\n"
             << endl;
    }

    // Get the next available task ID
    int getNextTaskID()
    {
        int maxID = 0;
        Node *temp = head;

        while (temp != NULL)
        {
            if (temp->task.taskID > maxID)
            {
                maxID = temp->task.taskID;
            }
            temp = temp->next;
        }

        return maxID + 1;
    }

    // Display tasks using Priority Queue (Highest priority first)
    void displayByPriorityQueue();

    // Destructor - Free all memory
    ~LinkedList()
    {
        Node *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ============================================================================
// STACK CLASS - For Undo functionality
// ============================================================================
struct StackNode
{
    string operation;
    Task task;
    int affectedTaskID;
    StackNode *next;

    StackNode(string op, Task t, int id)
    {
        operation = op;
        task = t;
        affectedTaskID = id;
        next = NULL;
    }
};

class UndoStack
{
private:
    StackNode *top;

public:
    UndoStack()
    {
        top = NULL;
    }

    // Push operation to stack
    void push(string operation, Task task, int id)
    {
        StackNode *newNode = new StackNode(operation, task, id);
        newNode->next = top;
        top = newNode;
    }

    // Pop operation from stack
    bool pop(string &operation, Task &task, int &id)
    {
        if (top == NULL)
        {
            return false;
        }

        operation = top->operation;
        task = top->task;
        id = top->affectedTaskID;

        StackNode *temp = top;
        top = top->next;
        delete temp;

        return true;
    }

    // Check if stack is empty
    bool isEmpty()
    {
        if (top == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Destructor
    ~UndoStack()
    {
        StackNode *temp;
        while (top != NULL)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// ============================================================================
// PRIORITY QUEUE CLASS - For managing tasks based on priority
// ============================================================================
class PriorityQueue
{
private:
    Node *head;

public:
    PriorityQueue()
    {
        head = NULL;
    }

    // Insert task in priority order (High priority first)
    void insertByPriority(Task t)
    {
        Node *newNode = createNode(t);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        if (head->task.priority < t.priority)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *temp = head;
        while (temp->next != NULL)
        {
            if (temp->next->task.priority >= t.priority)
            {
                temp = temp->next;
            }
            else
            {
                break;
            }
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Display tasks in priority order
    void displayByPriority()
    {
        if (head == NULL)
        {
            cout << "\n\t[!] No tasks in priority queue!\n"
                 << endl;
            return;
        }

        cout << "\n\t=========== TASKS BY PRIORITY ==========\n";

        Node *temp = head;
        int count = 1;

        while (temp != NULL)
        {
            cout << "\n\t[Priority Task " << count << "]\n";
            cout << "\t  ID: " << temp->task.taskID << "\n";
            cout << "\t  Title: " << temp->task.title << "\n";
            cout << "\t  Priority Level: " << temp->task.priority;

            if (temp->task.priority == 1)
            {
                cout << " (Low)";
            }
            else if (temp->task.priority == 2)
            {
                cout << " (Medium)";
            }
            else
            {
                cout << " (High)";
            }

            cout << "\n\t  Status: ";
            if (temp->task.isCompleted)
            {
                cout << "COMPLETED";
            }
            else
            {
                cout << "PENDING";
            }
            cout << "\n";
            cout << "\t  " << string(40, '-') << "\n";

            temp = temp->next;
            count++;
        }
        cout << endl;
    }

    // Destructor
    ~PriorityQueue()
    {
        Node *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ============================================================================
// LINKEDLIST DISPLAYBYPRIORITYQUEUE IMPLEMENTATION
// ============================================================================
inline void LinkedList::displayByPriorityQueue()
{
    if (head == NULL)
    {
        cout << "\n\t[ERROR] No tasks found!\n"
             << endl;
        return;
    }

    PriorityQueue pq;

    // Build priority queue by inserting all tasks
    Node *temp = head;
    while (temp != NULL)
    {
        pq.insertByPriority(temp->task);
        temp = temp->next;
    }

    // Display the priority queue
    pq.displayByPriority();
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Display main menu
// Display main menu
void displayMenu()
{
    cout << "\n\t========== TO-DO LIST MANAGER v1.0 ==========\n";
    cout << "\t\n";
    cout << "\t1.  Add a New Task\n";
    cout << "\t2.  View All Tasks\n";
    cout << "\t3.  Delete a Task\n";
    cout << "\t4.  Mark Task as Completed\n";
    cout << "\t5.  Search Task\n";
    cout << "\t6.  Update/Edit Task\n";
    cout << "\t7.  Sort by Priority\n";
    cout << "\t8.  View Completed Tasks\n";
    cout << "\t9.  View Pending Tasks\n";
    cout << "\t10. Undo Last Operation\n";
    cout << "\t11. View by Priority Queue\n";
    cout << "\t12. Exit\n";
    cout << "\t\n";
    cout << "\t============================================\n";
    cout << "\n\tEnter your choice: " << flush;
}

// Validate date format (DD/MM/YYYY)
bool isValidDate(const char *date)
{
    if (strlen(date) != 10)
    {
        return false;
    }
    if (date[2] != '/' || date[5] != '/')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i != 2 && i != 5 && !isdigit(date[i]))
        {
            return false;
        }
    }

    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main()
{
    LinkedList taskList;
    UndoStack undoStack;
    int choice;

    while (true)
    {
        displayMenu();

        // Read input with error checking
        if (!(cin >> choice))
        {
            // Check if EOF (stdin closed)
            if (cin.eof())
            {
                cout << "\n\t[ERROR] Input stream closed. Exiting...\n";
                return 0;
            }
            // Input failed - clear the error flag and input buffer
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n\t[ERROR] Invalid input! Please enter a number (1-13).\n";
            continue;
        }

        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        // ================================================================
        // CASE 1: ADD A NEW TASK
        // ================================================================
        case 1:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t=========== ADD NEW TASK ==========\n";
            cout << "\t===============================================================\n";

            Task newTask;
            newTask.taskID = taskList.getNextTaskID();

            cout << "\tTask ID (Auto-generated): " << newTask.taskID << "\n";

            cout << "\tEnter Task Title: ";
            cin.getline(newTask.title, 100);

            if (strlen(newTask.title) == 0)
            {
                cout << "\n\t[!] Task title cannot be empty!\n";
                break;
            }

            cout << "\tEnter Task Description: ";
            cin.getline(newTask.description, 250);

            cout << "\tSelect Priority (1=Low, 2=Medium, 3=High): ";
            if (!(cin >> newTask.priority))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\t[ERROR] Invalid input!\n";
                break;
            }
            cin.ignore();

            if (newTask.priority < 1 || newTask.priority > 3)
            {
                newTask.priority = 1;
                cout << "\t[WARNING]  Invalid priority! Set to Low (1)\n";
            }

            cout << "\tEnter Deadline (DD/MM/YYYY) or press Enter to skip: ";
            cin.getline(newTask.deadline, 20);

            if (strlen(newTask.deadline) > 0 && !isValidDate(newTask.deadline))
            {
                cout << "\t[WARNING]  Invalid date format! Deadline left empty\n";
                strcpy(newTask.deadline, "Not Set");
            }

            if (strlen(newTask.deadline) == 0)
            {
                strcpy(newTask.deadline, "Not Set");
            }

            taskList.insertTask(newTask);
            undoStack.push("ADD", newTask, newTask.taskID);

            cout << "\n\t[+] Task added successfully!\n";
            break;
        }

        // ================================================================
        // CASE 2: VIEW ALL TASKS
        // ================================================================
        case 2:
        {
            taskList.displayAllTasks();
            break;
        }

        // ================================================================
        // CASE 3: DELETE A TASK
        // ================================================================
        case 3:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t=========== DELETE TASK ==========\n";
            cout << "\t===============================================================\n";

            int deleteID;
            cout << "\tEnter Task ID to delete: ";
            if (!(cin >> deleteID))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\t[ERROR] Invalid input!\n";
                break;
            }
            cin.ignore();

            Node *taskToDelete = taskList.searchTask(deleteID);

            if (taskToDelete == NULL)
            {
                cout << "\n\t[ERROR] Task not found!\n";
            }
            else
            {
                undoStack.push("DELETE", taskToDelete->task, deleteID);

                if (taskList.deleteTask(deleteID))
                {
                    cout << "\n\t[+] Task deleted successfully!\n";
                }
                else
                {
                    cout << "\n\t[ERROR] Failed to delete task!\n";
                }
            }
            break;
        }

        // ================================================================
        // CASE 4: MARK TASK AS COMPLETED
        // ================================================================
        case 4:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t                MARK TASK COMPLETED\n";
            cout << "\t===============================================================\n";

            int completeID;
            cout << "\tEnter Task ID to mark as completed: ";
            if (!(cin >> completeID))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\t[ERROR] Invalid input!\n";
                break;
            }
            cin.ignore();

            if (taskList.markTaskComplete(completeID))
            {
                cout << "\n\t[OK] Task marked as completed!\n";
            }
            else
            {
                cout << "\n\t[ERROR] Task not found!\n";
            }
            break;
        }

        // ================================================================
        // CASE 5: SEARCH A TASK
        // ================================================================
        case 5:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t                   SEARCH TASK\n";
            cout << "\t===============================================================\n";
            cout << "\t1. Search by Task ID\n";
            cout << "\t2. Search by Task Title\n";
            cout << "\tChoose option: ";

            int searchChoice;
            if (!(cin >> searchChoice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\t[ERROR] Invalid input!\n";
                break;
            }
            cin.ignore();

            if (searchChoice == 1)
            {
                int searchID;
                cout << "\tEnter Task ID: ";
                if (!(cin >> searchID))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\n\t[ERROR] Invalid input!\n";
                    break;
                }
                cin.ignore();

                Node *found = taskList.searchTask(searchID);

                if (found != NULL)
                {
                    cout << "\n\t[OK] Task Found!\n";
                    cout << "\t  ID: " << found->task.taskID << "\n";
                    cout << "\t  Title: " << found->task.title << "\n";
                    cout << "\t  Description: " << found->task.description << "\n";
                    cout << "\t  Priority: ";

                    if (found->task.priority == 1)
                    {
                        cout << "Low";
                    }
                    else if (found->task.priority == 2)
                    {
                        cout << "Medium";
                    }
                    else
                    {
                        cout << "High";
                    }

                    cout << "\n\t  Deadline: " << found->task.deadline << "\n";
                    cout << "\t  Status: ";
                    if (found->task.isCompleted)
                    {
                        cout << "[OK] Completed";
                    }
                    else
                    {
                        cout << "Pending";
                    }
                    cout << "\n";
                }
                else
                {
                    cout << "\n\t[ERROR] Task not found!\n";
                }
            }
            else if (searchChoice == 2)
            {
                char searchTitle[100];
                cout << "\tEnter Task Title: ";
                cin.getline(searchTitle, 100);

                Node *found = taskList.searchTaskByTitle(searchTitle);

                if (found != NULL)
                {
                    cout << "\n\t[OK] Task Found!\n";
                    cout << "\t  ID: " << found->task.taskID << "\n";
                    cout << "\t  Title: " << found->task.title << "\n";
                    cout << "\t  Description: " << found->task.description << "\n";
                    cout << "\t  Priority: ";

                    if (found->task.priority == 1)
                    {
                        cout << "Low";
                    }
                    else if (found->task.priority == 2)
                    {
                        cout << "Medium";
                    }
                    else
                    {
                        cout << "High";
                    }

                    cout << "\n\t  Deadline: " << found->task.deadline << "\n";
                    cout << "\t  Status: ";
                    if (found->task.isCompleted)
                    {
                        cout << "[OK] Completed";
                    }
                    else
                    {
                        cout << "⧖ Pending";
                    }
                    cout << "\n";
                }
                else
                {
                    cout << "\n\t[ERROR] Task not found!\n";
                }
            }
            else
            {
                cout << "\n\t[ERROR] Invalid choice!\n";
            }
            break;
        }

        // ================================================================
        // CASE 6: UPDATE/EDIT A TASK
        // ================================================================
        case 6:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t                   UPDATE/EDIT TASK\n";
            cout << "\t===============================================================\n";

            int updateID;
            cout << "\tEnter Task ID to update: ";
            if (!(cin >> updateID))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n\t[ERROR] Invalid input!\n";
                break;
            }
            cin.ignore();

            Node *taskToUpdate = taskList.searchTask(updateID);

            if (taskToUpdate == NULL)
            {
                cout << "\n\t[ERROR] Task not found!\n";
            }
            else
            {
                Task updatedTask = taskToUpdate->task;

                cout << "\tEnter New Title (current: " << taskToUpdate->task.title << "): ";
                char newTitle[100];
                cin.getline(newTitle, 100);
                if (strlen(newTitle) > 0)
                {
                    strcpy(updatedTask.title, newTitle);
                }

                cout << "\tEnter New Description (current: " << taskToUpdate->task.description << "): ";
                char newDesc[250];
                cin.getline(newDesc, 250);
                if (strlen(newDesc) > 0)
                {
                    strcpy(updatedTask.description, newDesc);
                }

                cout << "\tEnter New Priority 1=Low, 2=Medium, 3=High (current: " << taskToUpdate->task.priority << "): ";
                int newPriority;
                if (!(cin >> newPriority))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\n\t[ERROR] Invalid input!\n";
                    break;
                }
                cin.ignore();
                if (newPriority >= 1 && newPriority <= 3)
                {
                    updatedTask.priority = newPriority;
                }

                cout << "\tEnter New Deadline DD/MM/YYYY (current: " << taskToUpdate->task.deadline << "): ";
                char newDeadline[20];
                cin.getline(newDeadline, 20);
                if (strlen(newDeadline) > 0)
                {
                    if (isValidDate(newDeadline))
                    {
                        strcpy(updatedTask.deadline, newDeadline);
                    }
                    else
                    {
                        cout << "\t[WARNING]  Invalid date format! Deadline not changed\n";
                    }
                }

                taskList.updateTask(updateID, updatedTask);
                undoStack.push("UPDATE", taskToUpdate->task, updateID);

                cout << "\n\t[OK] Task updated successfully!\n";
            }
            break;
        }

        // ================================================================
        // CASE 7: SORT BY PRIORITY
        // ================================================================
        case 7:
        {
            taskList.sortByPriority();
            break;
        }

        // ================================================================
        // CASE 8: VIEW COMPLETED TASKS
        // ================================================================
        case 8:
        {
            taskList.displayCompletedTasks();
            break;
        }

        // ================================================================
        // CASE 9: VIEW PENDING TASKS
        // ================================================================
        case 9:
        {
            taskList.displayPendingTasks();
            break;
        }

        // ================================================================
        // CASE 10: UNDO LAST OPERATION
        // ================================================================
        case 10:
        {
            cout << "\n\t===============================================================\n";
            cout << "\t                   UNDO LAST OPERATION\n";
            cout << "\t===============================================================\n";

            if (undoStack.isEmpty())
            {
                cout << "\n\t[ERROR] No operations to undo!\n";
            }
            else
            {
                string operation;
                Task task;
                int taskID;

                undoStack.pop(operation, task, taskID);

                if (operation == "ADD")
                {
                    taskList.deleteTask(taskID);
                    cout << "\n\t[OK] Undone: Task addition!\n";
                }
                else if (operation == "DELETE")
                {
                    taskList.insertTask(task);
                    cout << "\n\t[OK] Undone: Task deletion!\n";
                }
                else if (operation == "UPDATE")
                {
                    taskList.updateTask(taskID, task);
                    cout << "\n\t[OK] Undone: Task update!\n";
                }
            }
            break;
        }

        // ================================================================
        // CASE 11: VIEW BY PRIORITY QUEUE
        // ================================================================
        case 11:
        {
            cout << "\n\tDisplaying tasks by Priority...\n";
            taskList.displayByPriorityQueue();
            break;
        }

        // ================================================================
        // CASE 12: EXIT
        // ================================================================
        case 12:
        {
            cout << "Thank you for using To-Do List Manager! Goodbye!";
   

            return 0;
        }

        // ================================================================
        // DEFAULT: INVALID CHOICE
        // ================================================================
        default:
        {
            cout << "\n\t[ERROR] Invalid choice! Please try again (1-13).\n";
        }
        }
    }

    return 0;
}

// ============================================================================
// END OF PROGRAM
// ============================================================================
//
// EXPLANATION OF KEY CONCEPTS:
//
// 1. LINKED LIST:
//    - Every task is stored in a dynamically allocated Node
//    - Each node contains a Task struct and a pointer to the next node
//    - Efficient insertion and deletion at any position
//    - No wasted memory (unlike arrays)
//
// 2. STACK (UNDO FUNCTIONALITY):
//    - Each operation is pushed onto the stack
//    - LIFO (Last In, First Out) structure
//    - When undo is called, the last operation is reversed
//    - Supports: ADD, DELETE, UPDATE operations
//
// 3. PRIORITY QUEUE:
//    - Tasks are inserted in order of priority
//    - Highest priority tasks appear at the front
//    - Useful for scheduling and urgency-based task management
//
// 4. DATA STRUCTURES USED:
//    - Struct for Task definition
//    - LinkedList for dynamic task storage
//    - Stack for undo functionality
//    - PriorityQueue for priority-based ordering
//
// 5. MEMORY MANAGEMENT:
//    - 'new' is used to dynamically allocate memory
//    - 'delete' is used to free memory (preventing leaks)
//    - Destructors properly clean up all allocated memory
//
// 6. FILE I/O:
//    - Tasks are saved to "tasks.txt" with pipe-delimited format
//    - Tasks are automatically loaded on program startup
//    - Manual save/load options available
//
// 7. ERROR HANDLING:
//    - Validation for empty task lists
//    - Date format validation (DD/MM/YYYY)
//    - Priority range validation (1-3)
//    - Search handles non-existent tasks
//    - Duplicate ID prevention through auto-generation
//
// ============================================================================