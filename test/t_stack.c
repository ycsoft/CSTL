#include <stdio.h>
#include <stdlib.h>

#include "c_stack.h"
#include "c_vector.h"
#include "t_test.h"

static int ary[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
#define SIZE 10


static int int_comparer(value_type x, value_type y)
{
	return *(int *)x - *(int *)y;
}

static int create_with_push(c_pstack ps, int ary[])
{
	int i = 0;
	for(i = 0; i < SIZE; ++ i)
	{
		c_stack_push(ps, &ary[i]);
	}
	return 0;
}	

static int print_stack(c_pstack ps)
{
	c_vector tmpvt;
	__c_vector(&tmpvt, int_comparer);

	printf("stack is : \n");
	while(!c_stack_empty(ps))
	{
		int * tmp = c_stack_top(ps);
		printf("elem is : %d, size is : %d\n", *tmp, c_stack_size(ps));
		c_stack_pop(ps);
		c_vector_push_back(&tmpvt, tmp);
	}

	// recover stack
	do
	{
		c_reverse_iterator riter = c_vector_rbegin(&tmpvt);
		c_reverse_iterator rend = c_vector_rend(&tmpvt);
		for(; !ITER_EQUAL(riter, rend); ITER_INC(riter))
		{
			c_stack_push(ps, ITER_REF(riter));
		}
	} while(0);	

	__c_rotcev(&tmpvt);
	return 0;
}

static int clear_stack(c_pstack ps)
{
	while(!c_stack_empty(ps))
	{
		c_stack_pop(ps);
	}

	return 0;
}	


int t_stack()
{
	c_stack stack, stack1;
	int ary1[] = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1 }; 
	__c_stack(&stack, int_comparer);
	__c_stack(&stack1, int_comparer);

	create_with_push(&stack, ary);
	printf("stack: \n");
	print_stack(&stack);

	create_with_push(&stack1, ary1);
	printf("stack1: \n");
	print_stack(&stack1);
	
	if(c_stack_equal(&stack, &stack1))
		printf("stack == stack1\n");
	else
		printf("stack != stack1\n");

	clear_stack(&stack);
	clear_stack(&stack1);

	create_with_push(&stack, ary1);
	printf("stack: \n");
	print_stack(&stack);

	create_with_push(&stack1, ary1);
	printf("stack1: \n");
	print_stack(&stack1);

	if(c_stack_equal(&stack, &stack1))
		printf("stack == stack1\n");
	else
		printf("stack != stack1\n");


	clear_stack(&stack);
	clear_stack(&stack1);

	create_with_push(&stack, ary);
	printf("stack: \n");
	print_stack(&stack);

	create_with_push(&stack1, ary1);
	printf("stack1: \n");
	print_stack(&stack1);
	
	if(c_stack_less(&stack, &stack1))
		printf("stack < stack1\n");
	else
		printf("stack >= stack1\n");

	clear_stack(&stack);
	clear_stack(&stack1);

	create_with_push(&stack, ary1);
	printf("stack: \n");
	print_stack(&stack);

	create_with_push(&stack1, ary1);
	printf("stack1: \n");
	print_stack(&stack1);

	if(c_stack_less(&stack, &stack1))
		printf("stack < stack1\n");
	else
		printf("stack >= stack1\n");



	__c_kcats(&stack);
	__c_kcats(&stack1);

	printf("\nfinish testing stack!\n\n");
	return 0;
}
