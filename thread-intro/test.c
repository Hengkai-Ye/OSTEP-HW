#include <stdio.h>
#include <malloc.h>
#include <string.h>
 
void test(int *arg)
{
    *arg = 100;
}


int main()
{
    int target = 50;
    test(&target);
    printf("%d", target);
}