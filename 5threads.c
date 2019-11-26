#include <pthread.h>
#include <stdio.h>

//test commit 

static int counter = 0;
pthread_mutex_t lock1;
pthread_spinlock_t lock2;
//pthread_cond_t lock3 = PTHREAD_COND_INITIALIZER;
//pthread_mutex_t lock3B = PTHREAD_MUTEX_INITIALIZER;

void *doCount1(void *label) //mutex
{
	for (int i=0; i<10000000; i++)
	{
		pthread_mutex_lock(&lock1);
		counter++;
		pthread_mutex_unlock(&lock1);
	}
}


void *doCount2(void *label) //spin
{
	for (int i=0; i<10000000; i++)
	{
		pthread_spin_lock(&lock2);
		counter++;
		pthread_spin_unlock(&lock2);
	}
}

int lock3 = 0;
void *doCount3(void *label)
{
	for (int i=0; i<10000000; i++)
	{
		wait(lock3 == 0);
		lock3 = 1;
		counter++;
		lock3 = 0;
		signal(lock3 == 0);
		
	}
}


void locker1()
{
	pthread_t p1, p2, p3, p4, p5;
	printf("Locker 1 beginning all: counter = %d\n", counter);
	pthread_create(&p1, NULL, doCount1, "A");
	pthread_create(&p2, NULL, doCount1, "B");
	pthread_create(&p3, NULL, doCount1, "C");
	pthread_create(&p4, NULL, doCount1, "D");
	pthread_create(&p5, NULL, doCount1, "E");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	pthread_join(p5, NULL);
	printf("Locker 1 done with all: counter = %d\n", counter);
}

void locker2()
{
	pthread_t p1, p2, p3, p4, p5;
	printf("Locker 2 beginning all: counter = %d\n", counter);
	pthread_create(&p1, NULL, doCount2, "A");
	pthread_create(&p2, NULL, doCount2, "B");
	pthread_create(&p3, NULL, doCount2, "C");
	pthread_create(&p4, NULL, doCount2, "D");
	pthread_create(&p5, NULL, doCount2, "E");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	pthread_join(p5, NULL);
	printf("Locker 2 done with all: counter = %d\n", counter);
}

void locker3()
{
	pthread_t p1, p2, p3, p4, p5;
	printf("Locker 3 beginning all: counter = %d\n", counter);
	pthread_create(&p1, NULL, doCount3, "A");
	pthread_create(&p2, NULL, doCount3, "B");
	pthread_create(&p3, NULL, doCount3, "C");
	pthread_create(&p4, NULL, doCount3, "D");
	pthread_create(&p5, NULL, doCount3, "E");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	pthread_join(p5, NULL);
	printf("Locker 3 done with all: counter = %d\n", counter);
}


int main (int argc, char * argv[])
{
	locker1(); //mutex
	counter = 0;
	pthread_spin_init(&lock2, 0);
	locker2(); //spin
	counter = 0;
	//pthread_cond_init(&lock3, NULL);
	locker3();
	counter = 0;
	return 0;
}
