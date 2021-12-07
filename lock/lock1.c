#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int i = 1; //global variable

void *thread1(void *arg){
    pthread_mutex_lock(&lock);
    i = 2;
    printf("%d\n", i);
    sleep(5);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread2(void *arg){
    pthread_mutex_lock(&lock);
    i = 3;
    printf("%d\n", i);
    pthread_mutex_unlock(&lock);
    return NULL;
}


int main(){
    pthread_t t_1;
    pthread_t t_2;
    pthread_create(&t_1, NULL, thread1, (void *)NULL);
    pthread_create(&t_2, NULL, thread2, (void *)NULL);
    pthread_join(t_2, NULL);
    return 0;
}