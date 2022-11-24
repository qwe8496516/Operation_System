#include <stdio.h>
#include <pthread.h>
#define LOOP 100000

int data = 0;

void *subchild()
{
	for (int i = 0; i < LOOP; i++)
	{
		data--;
	}
}

void *addchild()
{
	for (int i = 0; i < LOOP; i++)
	{
		data++;
	}
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
