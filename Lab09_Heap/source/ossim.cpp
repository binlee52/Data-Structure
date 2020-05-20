//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                       ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "ptyqueue.cpp"
#include "showb.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int priority,              // Task's priority
        arrived;               // Time when task was enqueued

    int pty () const
        { return priority; }   // Returns the priority
};

//--------------------------------------------------------------------

int getRandom(int n) {
    // 0부터 n-1까지의 랜덤한 수를 리턴하는 함수
    return rand() % n;
}

int main ()
{
    PtyQueue<TaskData> taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals;             // Number of new tasks arriving

    std::cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    std::cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    srand(500);     // init seed
    
    int k;      // determine var of new tasks - 값에 따라 enqueue 횟수 결정

    int* longgest_wait = new int[numPtyLevels];        // each prioty's longgest wait 
    for (int i = 0; i < numPtyLevels; i++)
        longgest_wait[i] = 0;       // init longgest wait value as 0

    for (minute = 0; minute < simLength; minute++)
    {
        // Dequeue the first task in the queue (if any).
        if (!taskPQ.isEmpty())
        {
            task = taskPQ.dequeue();
            numArrivals = minute - task.arrived;
            if (longgest_wait[task.pty()] < numArrivals)        // time renewal
                longgest_wait[task.pty()] = numArrivals;
        }

        // Determine the number of new tasks and add them to
        // the queue.
        k = getRandom(4);   // select menu randomly
        task.arrived = minute;
        if (k == 1)
        {
            task.priority = getRandom(2);
            taskPQ.enqueue(task);
        }
        else if (k == 2)
        {
            task.priority = getRandom(2);
            taskPQ.enqueue(task);
            task.priority = getRandom(2);
            taskPQ.enqueue(task);
        }
    }
    std::cout << "..." << endl;
    std::cout << "Longest wait for any low-priority(0) task: " << longgest_wait[0] << endl;
    std::cout << "Longest wait for any high - priority(0) task: " << longgest_wait[numPtyLevels - 1] << endl;
}
