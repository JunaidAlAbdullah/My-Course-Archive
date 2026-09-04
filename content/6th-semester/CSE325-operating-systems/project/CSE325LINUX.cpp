/*
    =====================================================================
    CSE325 - Operating System Course Project
    Title   : IELTS / GRE Mock Exam Room Allocation System
    Language: C++ (using POSIX threads, POSIX semaphores, fork, signals)
    =====================================================================

    WHAT THIS PROGRAM DOES (in plain words)
    ----------------------------------------
    - We have 300 students and 10 rooms (30 seats each).
    - Every student is given a unique ID and is assigned to exactly one room.
    - A student (represented by a THREAD) is only allowed to walk into the
      room once the exam officially "starts". We use a SEMAPHORE for this.
    - Each room can only hold 30 students at a time. We use one counting
      SEMAPHORE per room to guarantee this (a "seat permit" system).
    - A separate PROCESS (created using fork()) acts as the exam timer.
      It "waits" for the exam duration and then tells the main program
      that time is up.
    - A MUTEX (+ condition variable) makes sure that NO student thread is
      allowed to leave the room before the timer process says the exam
      has ended.
    - At the end, the program prints a clean attendance summary.

    HOW THE FOUR REQUIRED OS CONCEPTS ARE USED
    -------------------------------------------
    1. SEMAPHORE  -> startExamSem   (controls when students may enter)
                  -> roomSeatSem[]  (controls room capacity, 30 per room)
    2. PROCESS    -> fork() creates a separate "Timer Process" that
                     represents the invigilator announcing start/end time.
    3. THREAD     -> each student is simulated using a pthread.
    4. MUTEX      -> examMutex + examEndCond make sure a student thread
                     cannot leave the hall before the exam officially ends.

    NOTE ON TIMING
    ---------------
    A real exam runs for 3 hours. To make testing/demo fast, we represent
    the "3 hours" using a small number of seconds (EXAM_DURATION_SECONDS).
    You can change this constant to any value you like.
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // fork(), sleep(), usleep()
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <signal.h>   // kill(), signal()
#include <csignal>    // sig_atomic_t
#include <cstdlib>

using namespace std;

// ---------------------------------------------------------------------
// CONFIGURATION CONSTANTS (change these if you want a bigger/smaller demo)
// ---------------------------------------------------------------------
const int TOTAL_STUDENTS = 300;                       // total registered students
const int ROOM_CAPACITY = 30;                         // max students per room
const int NUM_ROOMS = TOTAL_STUDENTS / ROOM_CAPACITY; // 10 rooms
const int EXAM_DURATION_SECONDS = 6;                  // simulated exam length (stand-in for 3 hours)

// ---------------------------------------------------------------------
// DATA STRUCTURE FOR A STUDENT (simple struct, no complex data structure)
// ---------------------------------------------------------------------
struct Student
{
    int id;       // unique student ID (0 .. TOTAL_STUDENTS-1)
    int roomId;   // room assigned to this student (0 .. NUM_ROOMS-1)
    bool present; // did the student actually check in?
};

Student students[TOTAL_STUDENTS]; // plain array holding all students
pthread_t studentThreads[TOTAL_STUDENTS];

// ---------------------------------------------------------------------
// SEMAPHORES
// ---------------------------------------------------------------------
// One "seat permit" semaphore per room. Initial value = ROOM_CAPACITY.
// A student must acquire (sem_wait) a seat before entering a room, and
// release it (sem_post) when leaving.
sem_t roomSeatSem[NUM_ROOMS];

// The exam does not start immediately. Every student thread first waits
// on this semaphore. The main program "opens the gate" by posting to
// this semaphore once for every student, only after the exam starts.
sem_t startExamSem;

// ---------------------------------------------------------------------
// MUTEX + CONDITION VARIABLE
// ---------------------------------------------------------------------
// These are used to make sure NO student leaves before the exam ends.
pthread_mutex_t examMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t examEndCond = PTHREAD_COND_INITIALIZER;
bool examOver = false; // protected by examMutex

// Attendance counters (also protected by examMutex since many threads
// update them at the same time).
int attendanceInRoom[NUM_ROOMS];
int totalPresent = 0;

// ---------------------------------------------------------------------
// PROCESS <-> SIGNAL COMMUNICATION
// ---------------------------------------------------------------------
// The child "Timer Process" will send SIGUSR1 to the parent process when
// the exam time is up. The signal handler only sets a simple flag
// (this is the only thing that is 100% safe to do inside a signal
// handler). A separate "monitor thread" watches this flag and then
// properly wakes up all waiting student threads using the mutex/condvar.
volatile sig_atomic_t timeIsUp = 0;

void examTimerSignalHandler(int signum)
{
    (void)signum;
    timeIsUp = 1; // just flip the flag, nothing else (signal-safe)
}

// ---------------------------------------------------------------------
// MONITOR THREAD
// ---------------------------------------------------------------------
// Waits for the "timeIsUp" flag to become true (set by the signal
// handler above) and then formally ends the exam by updating the
// shared "examOver" flag under the mutex and waking every student
// thread that is waiting to leave.
void *monitorRoutine(void * /*arg*/)
{
    while (!timeIsUp)
    {
        usleep(100000); // check 10 times per second, cheap and simple
    }

    pthread_mutex_lock(&examMutex);
    examOver = true;
    cout << "\n[INVIGILATOR] Time's up! Students may now leave their rooms.\n"
         << endl;
    pthread_cond_broadcast(&examEndCond); // wake up every waiting student
    pthread_mutex_unlock(&examMutex);

    return nullptr;
}

// ---------------------------------------------------------------------
// STUDENT THREAD ROUTINE
// ---------------------------------------------------------------------
void *studentRoutine(void *arg)
{
    int id = *(int *)arg;
    int roomId = students[id].roomId;

    // 1) Wait for the exam to officially start (SEMAPHORE)
    sem_wait(&startExamSem);

    // 2) Take a seat in the assigned room (SEMAPHORE controls capacity)
    sem_wait(&roomSeatSem[roomId]);

    // Mark attendance (shared data -> protected by MUTEX)
    pthread_mutex_lock(&examMutex);
    attendanceInRoom[roomId]++;
    totalPresent++;
    students[id].present = true;
    cout << "Student " << id << " entered Room " << (roomId + 1)
         << " (" << attendanceInRoom[roomId] << "/" << ROOM_CAPACITY << " seats filled)" << endl;
    pthread_mutex_unlock(&examMutex);

    // 3) Student is now taking the exam and must NOT leave early.
    //    Wait on the condition variable until the exam officially ends.
    pthread_mutex_lock(&examMutex);
    while (!examOver)
    {
        pthread_cond_wait(&examEndCond, &examMutex);
    }
    pthread_mutex_unlock(&examMutex);

    // 4) Exam has ended, student leaves the room and frees the seat.
    cout << "Student " << id << " is leaving Room " << (roomId + 1) << endl;
    sem_post(&roomSeatSem[roomId]); // give the seat back

    return nullptr;
}

// ---------------------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------------------
int main()
{
    cout << "=====================================================" << endl;
    cout << " IELTS / GRE Mock Exam - Room Allocation System" << endl;
    cout << " Total Students: " << TOTAL_STUDENTS
         << " | Rooms: " << NUM_ROOMS
         << " | Capacity per room: " << ROOM_CAPACITY << endl;
    cout << "=====================================================\n"
         << endl;

    // ---- Step 1: Assign unique IDs and rooms to every student ----
    // Simple round-robin assignment: student 0 -> room 0, student 1 -> room 1, ...
    // This guarantees every room gets exactly ROOM_CAPACITY students and
    // satisfies "each student assigned to exactly one room".
    for (int i = 0; i < TOTAL_STUDENTS; i++)
    {
        students[i].id = i;
        students[i].roomId = i % NUM_ROOMS;
        students[i].present = false;
    }

    // ---- Step 2: Initialize semaphores ----
    for (int r = 0; r < NUM_ROOMS; r++)
    {
        sem_init(&roomSeatSem[r], 0, ROOM_CAPACITY); // each room starts with 30 free seats
        attendanceInRoom[r] = 0;
    }
    sem_init(&startExamSem, 0, 0); // students cannot enter until we post to this

    // ---- Step 3: Set up the signal handler for the Timer Process ----
    signal(SIGUSR1, examTimerSignalHandler);
    pid_t parentPid = getpid();

    // ---- Step 4: Create the Timer Process using fork() (PROCESS) ----
    pid_t pid = fork();

    if (pid < 0)
    {
        cerr << "Error: fork() failed!" << endl;
        return 1;
    }

    if (pid == 0)
    {
        // -------- CHILD PROCESS: acts as the exam timer / invigilator --------
        cout << "[TIMER PROCESS] Exam timer started. Exam will run for "
             << EXAM_DURATION_SECONDS << " seconds (simulating 3 hours).\n"
             << endl;
        sleep(EXAM_DURATION_SECONDS); // wait for the exam duration
        kill(parentPid, SIGUSR1);     // tell the parent "time is up!"
        _exit(0);                     // child process finishes
    }

    // -------- PARENT PROCESS: manages students and rooms --------

    // ---- Step 5: Start the monitor thread (handles ending the exam safely) ----
    pthread_t monitorThread;
    pthread_create(&monitorThread, nullptr, monitorRoutine, nullptr);

    // ---- Step 6: Create one thread per student (THREAD) ----
    static int ids[TOTAL_STUDENTS];
    for (int i = 0; i < TOTAL_STUDENTS; i++)
    {
        ids[i] = i;
        pthread_create(&studentThreads[i], nullptr, studentRoutine, &ids[i]);
    }

    // ---- Step 7: Simulate a short countdown, then officially start the exam ----
    cout << "Students are waiting outside... exam starts in 2 seconds." << endl;
    sleep(2);
    cout << "\n*** EXAM STARTED! Students may now enter their rooms. ***\n"
         << endl;

    // "Open the gate": allow every student thread to proceed past sem_wait()
    for (int i = 0; i < TOTAL_STUDENTS; i++)
    {
        sem_post(&startExamSem);
    }

    // ---- Step 8: Wait for all student threads to finish (they finish only
    //              after the exam officially ends, thanks to the mutex/condvar) ----
    for (int i = 0; i < TOTAL_STUDENTS; i++)
    {
        pthread_join(studentThreads[i], nullptr);
    }
    pthread_join(monitorThread, nullptr);

    // ---- Step 9: Clean up the Timer Process ----
    wait(nullptr); // reap the child process

    // ---- Step 10: Print the final attendance summary ----
    cout << "\n=====================================================" << endl;
    cout << " EXAM ATTENDANCE SUMMARY" << endl;
    cout << "=====================================================" << endl;
    for (int r = 0; r < NUM_ROOMS; r++)
    {
        cout << "Room " << (r + 1) << ": "
             << attendanceInRoom[r] << " / " << ROOM_CAPACITY << " students present" << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    cout << "Total Present: " << totalPresent << " / " << TOTAL_STUDENTS << endl;
    cout << "Total Absent : " << (TOTAL_STUDENTS - totalPresent) << endl;
    cout << "=====================================================" << endl;

    // ---- Step 11: Destroy semaphores (cleanup) ----
    for (int r = 0; r < NUM_ROOMS; r++)
    {
        sem_destroy(&roomSeatSem[r]);
    }
    sem_destroy(&startExamSem);

    return 0;
}