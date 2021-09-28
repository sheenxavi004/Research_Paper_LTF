# Largest Task First(LTF) Algorithm

#### 1. Compile and run the program named [ltf.cpp](https://github.com/sheenxavi004/Research_Paper_LTF/blob/main/ltf.cpp).
#### 2. Prompt will ask you enter the number of tasks and the execution time of the tasks in High Performance and Low Performance Processors.
#### 3. Then we will be asked to input the Dependency DAG of the processes. In order to input the DAG, we feed the edges into the graph in the format u v, which implies there is an edge from u to v.
#### 4. Now the program will generate the allocation of tasks to High Performance and Low Performance processors using the information supplied. The allocation shows the task ID, start time and end time of each task assigned to the processors.

## Example Output 
```
sheenxavi004@Beta-Station:~/Research_Paper_LTF$ g++ ltf.cpp
sheenxavi004@Beta-Station:~/Research_Paper_LTF$ ./a.out
No of Tasks : 7
Tasks Details : 
Task 0: 
High Perfomance Execution Time(Wi[HP]) : 3.0
Low Perfomance Execution Time(Wi[LP]) : 7.5

Task 1: 
High Perfomance Execution Time(Wi[HP]) : 10.0
Low Perfomance Execution Time(Wi[LP]) : 23.1

Task 2: 
High Perfomance Execution Time(Wi[HP]) : 6.0 
Low Perfomance Execution Time(Wi[LP]) : 13.5

Task 3: 
High Perfomance Execution Time(Wi[HP]) : 6.5
Low Perfomance Execution Time(Wi[LP]) : 14.6

Task 4: 
High Perfomance Execution Time(Wi[HP]) : 5.0
Low Perfomance Execution Time(Wi[LP]) : 9.4

Task 5: 
High Perfomance Execution Time(Wi[HP]) : 4.5
Low Perfomance Execution Time(Wi[LP]) : 7.9

Task 6: 
High Perfomance Execution Time(Wi[HP]) : 4.0
Low Perfomance Execution Time(Wi[LP]) : 7.0

Task Dependency DAG Details
No of Edges : 6
Enter Edges in the format TaskID1 TaskID2 : 
0 1
0 2
0 4
1 3
1 5
2 6

------------------------------------
High Perfomance Processor Schedule :
------------------------------------
Task ID    : 2
Start Time : 7.5
End Time   : 13.5
------------------------------------
Task ID    : 4
Start Time : 13.5
End Time   : 18.5
------------------------------------
Task ID    : 6
Start Time : 18.5
End Time   : 22.5
------------------------------------
Task ID    : 5
Start Time : 30.6
End Time   : 35.1
------------------------------------
Low  Perfomance Processor Schedule :
------------------------------------
Task ID    : 0
Start Time : 0
End Time   : 7.5
------------------------------------
Task ID    : 1
Start Time : 7.5
End Time   : 30.6
------------------------------------
Task ID    : 3
Start Time : 30.6
End Time   : 45.2
------------------------------------ 


