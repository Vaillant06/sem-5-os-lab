
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;
int data = 0;

sem_t mutex;
sem_t rw_mutex;

void *reader(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);

    read_count++;

    if (read_count == 1)
        sem_wait(&rw_mutex);

    sem_post(&mutex);

    printf("Reader %d is reading data = %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);

    read_count--;

    if (read_count == 0)
        sem_post(&rw_mutex);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&rw_mutex);

    data++;

    printf("Writer %d is writing data = %d\n", id, data);
    sleep(1);

    sem_post(&rw_mutex);

    return NULL;
}

int main()
{
    pthread_t readers[5], writers[2];
    int r_id[5], w_id[2];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < 5; i++)
    {
        r_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &r_id[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        w_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &w_id[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}