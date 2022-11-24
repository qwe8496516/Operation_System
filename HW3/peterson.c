#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#define LOOP 5

int data = 0;

// Turn show that who enter the critical section
atomic_int turn = 0;
// flag show that who ready to enter the critical section
atomic_int flag[2] = {0};

void *subchild()
{
	flag[0] = 1;
	turn = 1;
	while (flag[1] == 1 && turn == 1);
	for (int i = 0; i < LOOP; i++)
	{
		data--;
		// printf("sub data = %d\n",data);
	}
	flag[0] = 0;
}

void *addchild()
{
	flag[1] = 1;
	turn = 0;
	while (flag[0] == 1 && turn == 0);
	for (int i = 0; i < LOOP; i++)
	{
		data++;
		// printf("add data = %d\n",data);
	}
	flag[1] = 0;
}

int main()
{
	// generate two thread
	pthread_t thread1, thread2;
	
	// thread creation (ID address,Attribute,function,parameter)
	pthread_create(&thread1, NULL, subchild, NULL);
	pthread_create(&thread2, NULL, addchild, NULL);

	// ensure the thread finish before main process finish (ID,return)
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("global data = %d\n", data);

	return 0;
}
