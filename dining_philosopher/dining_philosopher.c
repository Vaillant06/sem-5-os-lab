
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    // Pick up left fork
    sem_wait(&forks[id]);

    // Pick up right fork
    sem_wait(&forks[(id + 1) % N]);

    printf("Philosopher %d is eating\n", id);
    sleep(2);

    // Put down forks
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % N]);

    printf("Philosopher %d finished eating\n", id);

    return NULL;
}

int main()
{
    pthread_t philosophers[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);

    return 0;
}