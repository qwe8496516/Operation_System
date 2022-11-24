#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#define LOOP 3

typedef struct global_data
{
	int data;
	int count;
	atomic_flag m;
} global_data;
global_data gdata;


void semwait()
{
	while (atomic_flag_test_and_set(&gdata.m));
	// P
	while(gdata.count <= 0);
	gdata.count--;
	/* --- */
	atomic_flag_clear(&gdata.m);
}

void semsignal()
{
	// V
	gdata.count++;
}

void *subchild()
{
	for(int i = 0; i < LOOP; i++){
		semwait();
		gdata.data--;
		// printf("sub = %d\n",gdata.data);
		semsignal();
		// printf("sub_s = %d\n",gdata.count);
	}
}

void *addchild()
{
	for(int i = 0; i < LOOP; i++){
		semwait();
		gdata.data++;
		// printf("add = %d\n",gdata.data);
		semsignal();
		// printf("add_s = %d\n",gdata.count);
	}
}

int main()
{
	pthread_t thread1,thread2;
	
	gdata.count = 1;
	pthread_create(&thread1,NULL,subchild,NULL);
	pthread_create(&thread2,NULL,addchild,NULL);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	printf("global data = %d,%d\n",gdata.data,gdata.count);
	
	return 0;
}
