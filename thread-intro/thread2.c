#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static volatile int counter = 0;
//counter是静态全局变量，两个thread共享
void *mythread(void *arg) {
    char *letter = arg;
    int i;
    printf("%s: begin [addr of i: %p]\n", letter, &i);
    for(i = 0; i < 1e7; i++){
        counter += 1;
    }
    printf("%s: done\n", letter);
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 1) {
	fprintf(stderr, "error\n");
	exit(1);
    }
    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", counter);
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: done [counter = %d]\n", counter);
    return 0;
}

/*
得到结果远小于2e7，why？
两个线程并行存在竞争关系
counter += 1；
可以分解为:
mov eax，counter
add eax, 1;
mov counter, eax;
存在情况eax完成加一时cpu切换到p2。+1的结果没有被存到counter中
*/