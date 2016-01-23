#include <stdio.h>
#include <stdlib.h>

#include "c_queue.h"
#include "c_vector.h"
#include "t_test.h"

static int ary[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
#define SIZE 10


static int int_comparer(value_type x, value_type y)
{
	return *(int *)x - *(int *)y;
}

static int create_with_push(c_pqueue ps, int ary[])
{
	int i = 0;
	for(i = 0; i < SIZE; ++ i)
	{
		c_queue_push(ps, &ary[i]);
	}
	return 0;
}	

static int print_queue(c_pqueue ps)
{
	c_vector tmpvt;
	__c_vector(&tmpvt, int_comparer);

	printf("queue is : \n");
	while(!c_queue_empty(ps))
	{
		int * tmp = c_queue_front(ps);
		printf("front is : %d, size is : %d, back is : %d\n", 
				*tmp, 
				c_queue_size(ps),
				*(int *)c_queue_back(ps));
		c_queue_pop(ps);
		c_vector_push_back(&tmpvt, tmp);
	}

	// recover queue
	do
	{
		c_iterator iter = c_vector_begin(&tmpvt);
		c_iterator end = c_vector_end(&tmpvt);
		for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
		{
			c_queue_push(ps, ITER_REF(iter));
		}
	} while(0);	

	__c_rotcev(&tmpvt);
	return 0;
}

static int clear_queue(c_pqueue ps)
{
	while(!c_queue_empty(ps))
	{
		c_queue_pop(ps);
	}

	return 0;
}	


int t_queue()
{
	c_queue queue, queue1;
	int ary1[] = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1 }; 
	__c_queue(&queue, int_comparer);
	__c_queue(&queue1, int_comparer);

	create_with_push(&queue, ary);
	printf("queue: \n");
	print_queue(&queue);

	create_with_push(&queue1, ary1);
	printf("queue1: \n");
	print_queue(&queue1);
	
	if(c_queue_equal(&queue, &queue1))
		printf("queue == queue1\n");
	else
		printf("queue != queue1\n");

	clear_queue(&queue);
	clear_queue(&queue1);

	create_with_push(&queue, ary1);
	printf("queue: \n");
	print_queue(&queue);

	create_with_push(&queue1, ary1);
	printf("queue1: \n");
	print_queue(&queue1);

	if(c_queue_equal(&queue, &queue1))
		printf("queue == queue1\n");
	else
		printf("queue != queue1\n");


	clear_queue(&queue);
	clear_queue(&queue1);

	create_with_push(&queue, ary);
	printf("queue: \n");
	print_queue(&queue);

	create_with_push(&queue1, ary1);
	printf("queue1: \n");
	print_queue(&queue1);
	
	if(c_queue_less(&queue, &queue1))
		printf("queue < queue1\n");
	else
		printf("queue >= queue1\n");

	clear_queue(&queue);
	clear_queue(&queue1);

	create_with_push(&queue, ary1);
	printf("queue: \n");
	print_queue(&queue);

	create_with_push(&queue1, ary1);
	printf("queue1: \n");
	print_queue(&queue1);

	if(c_queue_less(&queue, &queue1))
		printf("queue < queue1\n");
	else
		printf("queue >= queue1\n");



	__c_eueuq(&queue);
	__c_eueuq(&queue1);

	printf("\nfinish testing queue!\n\n");
	
	return 0;
}
