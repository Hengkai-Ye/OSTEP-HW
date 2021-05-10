#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int a;
    int b;
    /* data */
}myarg;

typedef struct
{
    int x;
    int y;
    /* data */
}myret;

void *mythread(void *arg){
    myret *rvals = malloc(sizeof(myret));
    rvals->x = 1;
    rvals->y = 2;
    return (void *)rvals;
}

int main(int argc, char *argv[]){
    pthread_t p;
    myarg arg = {10, 20}; //线程函数的输入参数 本例中其实没有被用到
    myret *rvals; //线程的返回值，一个指向myret结构的指针
    pthread_create(&p, NULL, mythread, &arg);
    pthread_join(p, (void **) &rvals);
    printf("two returns: %d, %d\n", rvals->x, rvals->y);
    free(rvals);
    return 0;
}
