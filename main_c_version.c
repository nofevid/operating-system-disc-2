#include "sem_s.h"
#include <unistd.h>

const int RN=2;
sem_s L={RN,0};
sem_s mx={1,0};
int a=1;



void* reader(void *arg)
{
     while (1)
     {
        Swait(&mx,1,0);
        Swait(&L,0,1);

        printf("%d\n",a);

        Ssignal(&L,0,1);
        sleep(1);
     }
     return NULL;
 }

void* writer(void *arg)
{
    while (1)
    {
        Swait(&mx,0,1);
        Swait(&L,RN,0);

        a++;

        Ssignal(&mx,1,1);
        sleep(2);
    }
    return NULL;
}

int main()
{
    sem_s_init(&L);
    sem_s_init(&mx);
    printf("Hello, world!\n");
    pthread_t write,read,read1;
    pthread_create(&write,NULL,writer,NULL);
    pthread_create(&read,NULL,reader,NULL);
    pthread_create(&read1,NULL,reader,NULL);
    pthread_join(write, NULL);
    pthread_join(read, NULL);
    pthread_join(read1, NULL);
}