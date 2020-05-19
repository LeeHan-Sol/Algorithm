#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

void someMethod1();
void someMethod2();


int main(void) {
        struct timeb start;
        struct timeb end;

        ftime(&start);
        someMethod1();
        ftime(&end);

        printf("for ( 1000000 ) { malloc(1024); free; } \n");
        printf("Start Time : %ld , %d\n", start.time, start.millitm);
        printf(" End  Time : %ld , %d\n", end.time, end.millitm);
        printf(" Diff Time : %ld , %d\n", end.time - start.time , end.millitm - start.millitm );

        printf("\n\n\n");

        ftime(&start);
        someMethod2();
        ftime(&end);

        printf("malloc(1024) for ( 1000000 ) { memset(t,0,sizeof(t); } free; \n");
        printf("Start Time : %ld , %d\n", start.time, start.millitm);
        printf(" End  Time : %ld , %d\n", end.time, end.millitm);
        printf(" Diff Time : %ld , %d\n", end.time - start.time , end.millitm - start.millitm );

        return 0;
}


void someMethod1() {
        char *t;
        int i;

        for ( i = 0 ; i < 1000000 ; i++) {
                t = (char*)malloc(1024);
                free(t);
        }
}


void someMethod2() {
        char *t;
        int i;

        t = (char*)malloc(1024);
        for ( i = 0 ; i < 1000000 ; i++) {
                memset(t,0,sizeof(t));
        }
        free(t);
}
