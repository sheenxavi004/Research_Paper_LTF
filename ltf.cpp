// Name  : ltf.cpp
// Desc  : Program which demonstrates Largest Task First Algorithm
//        among two processors(HP and LP)
// Input : Details of tasks and thier dependency graph
// Output: Detailed schedule of tasks alloted to HP and LP processors
// Date  : 27/10/2021
// Author: Sheen Xavier A 

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

// Structure for Processor
struct processors{
    bool available;  // Flag for whether the processor is in use
    float time_remaining; // Time remaining for current process
                          // executing in the processor
}; 

// Structure for Tasks
struct task{
    int taskID;  // Task ID
    float hp_time; // Execution time required in HP processor
    float lp_time; // Execution time required in LP processor
    float start_time; // Start time for process
    float end_time; // End time for process
    bool processor_type; // 0 for LP, 1 for HP
};

bool compare(task a, task b)
{
    return a.start_time < b.start_time;
}

int main()
{
    int n;


    // Declaring high perfomance and low perfomance processors  
    processors high_perfomance, low_perfomance;

    low_perfomance.time_remaining = 0;
    low_perfomance.available = true;
    high_perfomance.time_remaining = 0;
    high_perfomance.available = true;

    // Reading the tasks and their execution times
    cout << "No of Tasks : ";
    cin >> n;
    
    task tasks[n];
    cout << "Tasks Details : \n";
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Task "<<  i << ": \n";
        cout << "High Perfomance Execution Time(Wi[HP]) : ";
        cin >> tasks[i].hp_time;
        cout << "Low Perfomance Execution Time(Wi[LP]) : ";
        cin >> tasks[i].lp_time;     
        tasks[i].start_time = INT_MAX;
        tasks[i].taskID = i;
        cout << endl;
    }
    
    // Clearing the DAG
    bool dag[n][n];
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            dag[i][j] = 0;

    // Reading the number of edges in the dependency DAG
    int E;
    cout << "Task Dependency DAG Details\n";
    cout << "No of Edges : ";
    cin >> E;

    cout << "Enter Edges in the format TaskID1 TaskID2 : \n";
    for(int i = 0 ; i < E ; i++)
    {
        int n1, n2;
        cin >> n1 >> n2;
        dag[n1][n2] = 1;
    }

    // Data structure for storing processes to be scheduled
    vector<int> waiting_list;
    int indegree[n];
    float time = 0;
    for(int i =  0 ; i < n ; i++)
        indegree[i] = 0;
    
    // Computing the indegree of each task inorder to recognize dependency
    for(int i = 0 ; i < n ; i++)
        for(int j = 0; j < n; j++)
            if(dag[i][j])
                indegree[j]++;
    

    // Initializing waiting list with processes having no dependency
    for(int i = 0 ; i < n ; i++)
        if(indegree[i] == 0)
        {
            indegree[i] = -1;
            waiting_list.push_back(i);
            tasks[i].start_time = time;
        }

    // Processes the task until the waiting list is empty
    while(!waiting_list.empty())
    {
        int x = 0, vsize = waiting_list.size(), curr_task = waiting_list[0], remIndex = 0;
        float duration;

        // Finds the task in waiting list which is pending and has greater priority if starting
        // times are the same
        for(int i = 0 ; i < vsize ; i++)
        {
            if(tasks[waiting_list[i]].start_time < tasks[curr_task].start_time)
            {
                curr_task = waiting_list[i];
                remIndex = i;
            }
            else if(tasks[waiting_list[i]].start_time == tasks[curr_task].start_time)
            {
                if(tasks[waiting_list[i]].hp_time > tasks[curr_task].hp_time)
                {
                    curr_task = waiting_list[i];
                    remIndex = i;
                }
            }
        }

        // Removing the prcess from the waiting list
        waiting_list.erase(waiting_list.begin() + remIndex);
        
        // Removing the dependency of the specific task on the 
        // dependant nodes
        for(int i = 0 ; i < n ; i++)
            if(dag[curr_task][i])
                indegree[i]--;

        // If low perfomance processor is available
        if(low_perfomance.available)
        {
            duration = tasks[curr_task].lp_time;
            tasks[curr_task].processor_type = 0;
            tasks[curr_task].start_time = time > tasks[curr_task].start_time ? time : tasks[curr_task].start_time ;
            tasks[curr_task].end_time = tasks[curr_task].start_time + duration;
            low_perfomance.time_remaining = tasks[curr_task].lp_time;
            low_perfomance.available = false;
        }
        else
        {
            // If low perfomance we check the high perfomance processor
            duration = tasks[curr_task].hp_time;
            // We check if we can run the process simulataneuosly in HP while another process 
            // is running in the LP
            if(duration <= low_perfomance.time_remaining && time >= tasks[curr_task].start_time)
            {
                tasks[curr_task].processor_type = 1;
                tasks[curr_task].start_time = time > tasks[curr_task].start_time ? time : tasks[curr_task].start_time ;
                tasks[curr_task].end_time = tasks[curr_task].start_time + duration;
                high_perfomance.time_remaining = duration;
                low_perfomance.time_remaining -= duration;
                if(low_perfomance.time_remaining == 0)
                    low_perfomance.available = true;
                time += duration;
            }
            else
            {
                // If we can't accomodate the process in HP, we wait until the LP is free
                duration = tasks[curr_task].lp_time;
                time += low_perfomance.time_remaining;
                tasks[curr_task].processor_type = 0;
                tasks[curr_task].start_time = time > tasks[curr_task].start_time ? time : tasks[curr_task].start_time ;
                tasks[curr_task].end_time = tasks[curr_task].start_time + duration;
                low_perfomance.time_remaining = tasks[curr_task].lp_time;
                low_perfomance.available = false;
            }
        }

        // Filling the waiting list with process with no dependencies
        for(int i = 0 ; i < n ; i++)
        {
            if(indegree[i] == 0)
            {
                tasks[i].start_time = tasks[curr_task].end_time;
                waiting_list.push_back(i);
                indegree[i] = -1;
            }
        }
    }

    sort(tasks, tasks + n, compare);

    // High Perfomance Processes
    
    cout << endl << "------------------------------------" << endl;
    cout << "High Perfomance Processor Schedule :" << endl;
    cout << "------------------------------------" << endl;
    for(int i = 0 ; i < n ; i++)
    {
        if(tasks[i].processor_type)
        {
            cout << "Task ID    : " << tasks[i].taskID << endl;
            cout << "Start Time : " << tasks[i].start_time << endl;
            cout << "End Time   : " << tasks[i].end_time << endl;
            cout << "------------------------------------" << endl;
        }
    }

    // Low Perfomance Processes
    cout << "Low  Perfomance Processor Schedule :" << endl;
    cout << "------------------------------------" << endl;
    for(int i = 0 ; i < n ; i++)
    {
        if(tasks[i].processor_type == 0)
        {
            cout << "Task ID    : " << tasks[i].taskID << endl;
            cout << "Start Time : " << tasks[i].start_time << endl;
            cout << "End Time   : " << tasks[i].end_time << endl;
            cout << "------------------------------------" << endl;
        }
    }
    return 0;
}