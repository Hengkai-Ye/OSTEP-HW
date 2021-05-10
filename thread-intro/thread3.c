#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int a;
    int b;
    /* data */
}myarg; //创建结构包含两个int

void *mythread(void *arg){
    myarg *args  = (myarg *) arg; //强制将arg转换为指向myarg的指针
    printf("two args: %d, %d\n", args->a,args->b);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t p1;
    myarg arg = {10, 20};
    pthread_create(&p1, NULL, mythread, &arg);
    pthread_join(p1, NULL); //p1为等待的线程，null为线程函数返回值类型
    return 0;
}