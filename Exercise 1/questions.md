Exercise 1 - Theory questions
-----------------------------

### Concepts

What is the difference between *concurrency* and *parallelism*?
> *Concurrency regards handling multiple proccesses at the same time. This means running several independent proccesses concurrently (using e.g. threads). In a concurrent system, mutiple proccesses progress at the same time, but they don`t have to be excecuting at the same time. By switching between quickly, we can create the illusion of tasks executing at the same time.*

>*Parallelism on the other hand means actually executing several tasks simultaniously. With parallelism, tasks are run independently on different CPU cores, and executed simultaniously.*

What is the difference between a *race condition* and a *data race*? 
> *Threads in a proccess can switch sequencally. If the switching can lead to upredicted behaviours or bugs, we have a race condition*

>*A data race occurs when two or more threads try to access and modify the same resource concurrently. (check this)*
 
*Very* roughly - what does a *scheduler* do, and how does it do it?
>*A scheduler descides what thread will run and for how long. A scheduler can be implemented preemptive (time based)  or cooperativly (manualy coded or compiler coded).*


### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?
> *Your answer here*

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?
> *Your answer here*

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?
> *Your answer here*

What do you think is best - *shared variables* or *message passing*?
> *Your answer here*


