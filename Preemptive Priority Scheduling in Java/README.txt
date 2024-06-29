*****Preemptive Priority Scheduling in Java*****

Preemptive Priority CPU Scheduling Algorithm :
This algorithm uses a rank-based system to define a rank for each process, where lower rank processes have higher priority and higher rank processes have lower priority. For instance, if there are 10 processes to be executed using this Preemptive Algorithm, then process with rank 1 will have the highest priority, the process with rank 2 will have comparatively lesser priority, and process with rank 10 will have least priority.  

Steps:
Step-1: Select the first process whose arrival time will be 0, we need to select that process because that process is only executing at time t=0.
Step-2: Check the priority of the next available process. Here we need to check for 3 conditions.
if priority(current_process) > priority(prior_process) :- then execute the current process.
if priority(current_process) < priority(prior_process) :- then execute the prior process.
if priority(current_process) = priority(prior_process) :- then execute the process which arrives first i.e., arrival time should be first.
Step-3: Repeat Step-2 until it reaches the final process.
Step-4: When it reaches the final process, choose the process which is having the highest priority & execute it. Repeat the same step until all processes complete their execution.

Steps for Implementation :
1. Download the source code of the project.
2. Execute the code in any IDE - Eclipse / NetBeans, etc.