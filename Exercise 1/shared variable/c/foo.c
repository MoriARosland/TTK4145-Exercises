// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <math.h>
#include <pthread.h>
#include <stdio.h>

int i = 0;

pthread_mutex_t lock;

// Note the return type: void*
void *
incrementingThreadFunction() {
  // TODO: increment i 1_000_000 times

  for (int loop = 0; loop < pow(10, 6); loop++) {
    pthread_mutex_lock(&lock); // Lock thread before modifying i.
    i++;
    pthread_mutex_unlock(&lock); // Unlock thread after updating i.
  }
  return NULL;
}

void *decrementingThreadFunction() {
  // TODO: decrement i 1_000_000 times
  for (int loop = 0; loop < 999999; loop++) {
    pthread_mutex_lock(&lock); // Lock thread before modifying i.
    i--;
    pthread_mutex_unlock(&lock); // Unlock thread after updating i.
  }
  return NULL;
}

int main() {

  // TODO:
  // start the two functions as their own threads using `pthread_create`
  // Hint: search the web! Maybe try "pthread_create example"?

  pthread_mutex_init(&lock, NULL);

  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, incrementingThreadFunction, "increment function");
  pthread_create(&thread2, NULL, decrementingThreadFunction, "decrement function");

  // TODO:
  // wait for the two threads to be done before printing the final result
  // Hint: Use `pthread_join`

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_mutex_destroy(&lock);

  printf("The magic number is: %d\n", i);
  return 0;
}
