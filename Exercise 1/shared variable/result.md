# Results
Both the foo.c and foo.g yield the same results. They work in similar way, where the threads try to modify the variable *i* simultaniously.

The CPU threads are scheduled preemptively, meaning they have a fix time intervall of running before they are switched. If the thread is interrupted before writing its result, the next thread will read the old value stored. This yields the distorted result where 10^6 - 10^6 != 0.

The for loop requires multiple steps by the CPU to complete. Fetch the data, increment the data, save the data. If the thread switches before this cycle is complete, the switched thread will start is running with an outdated value.

## Task 4
We use mutex since we only want the integer *i* to be available to one thread at a time (mutual exclusion).