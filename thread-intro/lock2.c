#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
// reference: https://blog.csdn.net/shichao1470/article/details/89856443
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0; //global variable

void *thread1(void *arg){
    pthread_mutex_lock(&lock);
    while(ready == 0){
        printf("release the lock and sleep untill receive the signal\n");
        pthread_cond_wait(&cond, &lock); //wait自带解锁上锁
    }
    printf("receive the signal, hold the lock and continue the execution\n");
    printf("resume execution of thread1\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread2(void *arg){
    pthread_mutex_lock(&lock);
    sleep(3);
    ready = 1;
    printf("send the signal\n");
    pthread_cond_signal(&cond); //signal只是发送信号并不解锁，wait在收到信号后仍要先等待thread2的解锁才行
    sleep(10);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t t_1;
    pthread_t t_2;
    pthread_create(&t_1, NULL, thread1, (void *)NULL);
    pthread_create(&t_2, NULL, thread2, (void *)NULL);
    pthread_join(t_1, NULL);
    pthread_join(t_2, NULL);
    return 0;
}