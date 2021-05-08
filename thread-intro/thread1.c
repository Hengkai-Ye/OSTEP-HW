#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *mythread(void *arg) {
    printf("%s\n", arg);
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 1){
        fprintf(stderr, "error\n");
        exit(1);
    }

    pthread_t p1, p2; //设置两个线程号
    printf("main begnin\n");
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    /*
    pthread为线程号创建线程分配资源
    NULL表示创建的线程非分离属性的，这意味着线程结束后分配的资源并未释放
    只有在pthread_join函数返回时才会释放线程资源
    mythread指创建的线程从mythread函数开始执行，“A”是传入mythread函数的参数
    int pthread_create(
                 pthread_t *restrict tidp,   //新创建的线程ID指向的内存单元。
                 const pthread_attr_t *restrict attr,  //线程属性，默认为NULL
                 void *(*start_rtn)(void *), //新创建的线程从start_rtn函数的地址开始运行
                 void *restrict arg //默认为NULL。若上述函数需要参数，将参数放入结构中并将地址作为arg传入。
                  );
    */
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    /*
    让调用线程（主线程）等待p1线程执行结束，并回收对应资源
    */
    printf("main: end\n");
    return 0;
}