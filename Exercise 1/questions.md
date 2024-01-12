Exercise 1 - Theory questions
-----------------------------

### Concepts

What is the difference between *concurrency* and *parallelism*?
> *Concurrency regards handling multiple proccesses at the same time. This means running several independent proccesses concurrently (e.g. using threads). In a concurrent system, mutiple proccesses progress at the same time, but they don`t have to be excecuting at the same time. By switching between quickly, we can create the illusion of tasks executing in parallell.*

>*Parallelism on the other hand means actually executing several tasks simultaniously. With parallelism, tasks are run independently on different CPU cores, and executed simultaniously.*

What is the difference between a *race condition* and a *data race*? 
> *Threads in a proccess can switch sequencally. If the switching can lead to upredicted behaviours or bugs, we have a race condition.*

>*A data race occurs when two or more threads try to access and modify the same resource concurrently.*
 
*Very* roughly - what does a *scheduler* do, and how does it do it?
>*A scheduler descides what thread will run and for how long. A scheduler can be implemented preemptive (time based)  or cooperativly (manualy coded or compiler coded).*


### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?

Threads allow multiple taks to progress simultaniously. This can improve efficiency, speed, and responsiveness. Multiple threads are especially for CPUs with multiple cores, since tasks can be distributed among the available resources.

Speed and efficiency becomes better due to load-balancing and asynchronous processing. Say a server gets a request. With threads, the request can be handeled on an independent thread and allow other server resources to continue as normal (non-blocking). This also improves responsiveness as background tasks can still run.

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?

The primary difference between fibers and threads are how they are scheduled. Threads are scheduled preemptively and fibers cooperatively.

How fibers are executed gives them some performance advantages. Fibers are implicitly syncronized and are therefore more lightweight than threads. Sycronization constructs such as atomic blocks and spinlock are there fore not nessecary. They require minimal overhead and are not managed by the OS kernel. This makes concurrent tasks faster than threads.

Because of fibers simplicity, they are easier to errorhandle and maintain.

They are not however suited for all taks. Fibers excell in high-volume concurrent operations and I/O bound tasks. More complex tasks such as OS dependent tasks, may benefit more from threads.

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?


This the depends on the complexity and problem of the application being built. Concurrent programs can improve code performance and reliability, but may be harder to design, test and maintain. Some problems are however easier to solve concurrently, such as handling multiple web requests.

What do you think is best - *shared variables* or *message passing*?

It would depend on the nature of the problem. Message passing may improve reliability, but introduce more complexity. Shared variabled are easier to implement, but may require more testing and can be more error prone.

For coupled-tasks and performance critical applications is would use shared variables due to the reduced overhead and complexity. For large distributed systems or code that requires modularity and scaling, i would use message passing.


