#include <stdlib.h>
#include <stdio.h>
#include "c_iterator.h"
#include "c_algorithm.h"
#include "c_vector.h"
#include "c_list.h"
#include "t_test.h"

static int ary[] = { 0,1,2,3,4,5,6,7,8,9 };
static int * pary[] = { &ary[0], &ary[1], &ary[2],
			 &ary[3], &ary[4], &ary[5],
			 &ary[6], &ary[7], &ary[8],
			 &ary[9] };
	
static int int_comparer(value_type x, value_type y)
{
	return *(int *)x - *(int *)y;
}

static c_bool is_int_equal(value_type x, value_type y)
{
	return int_comparer(x, y) == 0;
}

static int print2(c_iterator first, c_iterator last)
{
	while(!ITER_EQUAL(first, last))
	{
		printf("%d\n", *(int *)ITER_REF(first));
		ITER_INC(first);
	}
	return 0;
}


static int test_c_array()
{
	c_list list;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	__c_list(&list, int_comparer);
	
	c_list_insert2(&list, c_list_begin(&list), first, last);

	print2(c_list_begin(&list), c_list_end(&list));

	__c_tsil(&list);

	return 0;
}

static int test_advance(c_iterator first, c_iterator last)
{
	c_iterator iter = first;
	int i = 0;

	while(1)
	{
		iter = first;
		c_advance(&iter, i);
		if(ITER_EQUAL(iter, last))
			break;

		printf("advance %d : %d\n", i, *(int *)ITER_REF(iter));
		++ i;
	}

	return 0;
}

static int test_advance_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	printf("advance by c array:\n");
	test_advance(first, last);
	return 0;
}

static int test_advance_by_c_vector()
{
	c_vector vector;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	__c_vector(&vector, int_comparer);

	c_vector_insert2(&vector, c_vector_begin(&vector), first, last);

	printf("advance by vector:\n");	
	test_advance(c_vector_begin(&vector), c_vector_end(&vector));

	__c_rotcev(&vector);
	return 0;
}

static int test_advance_by_c_list()
{
	c_list list;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	__c_list(&list, int_comparer);

	c_list_insert2(&list, c_list_begin(&list), first, last);

	printf("advance by list:\n");	
	test_advance(c_list_begin(&list), c_list_end(&list));

	__c_tsil(&list);
	return 0;
}


static value_type plus_one(value_type val)
{
	*(int*)val += 1;
	return val;
}

static value_type deduct_one(value_type val)
{
	*(int*)val -= 1;
	return val;
}

static int test_for_each_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	printf("for each by c array:\n");
	printf("plus one:\n");
	c_for_each(first, last, plus_one);
	print2(first, last);

	printf("deduct one:\n");
	c_for_each(first, last, deduct_one);
	print2(first, last);

	return 0;
}

static int test_for_each_by_c_vector()
{
	c_vector vector;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	__c_vector(&vector, int_comparer);

	c_vector_insert2(&vector, c_vector_begin(&vector), first, last);

	printf("for each by vector:\n");
	printf("plus one:\n");
	c_for_each(c_vector_begin(&vector), c_vector_end(&vector), plus_one);
	print2(c_vector_begin(&vector), c_vector_end(&vector));

	printf("deduct one:\n");
	c_for_each(c_vector_begin(&vector), c_vector_end(&vector), deduct_one);
	print2(c_vector_begin(&vector), c_vector_end(&vector));

	__c_rotcev(&vector);
	return 0;
}

static int test_for_each_by_c_list()
{
	c_list list;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	__c_list(&list, int_comparer);

	c_list_insert2(&list, c_list_begin(&list), first, last);

	printf("for each by c list:\n");
	printf("plus one:\n");
	c_for_each(c_list_begin(&list), c_list_end(&list), plus_one);
	print2(c_list_begin(&list), c_list_end(&list));

	printf("deduct one:\n");
	c_for_each(c_list_begin(&list), c_list_end(&list), deduct_one);
	print2(c_list_begin(&list), c_list_end(&list));

	__c_tsil(&list);
	return 0;
}

static int test_find_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	c_iterator iter;

	printf("find by c array:\n");
	printf("to find 0:\n");
	iter = c_find(first, last, pary[0]);
	if(!ITER_EQUAL(iter, last))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 5:\n");
	iter = c_find(first, last, pary[5]);
	if(!ITER_EQUAL(iter, last))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 9:\n");
	iter = c_find(first, last, pary[9]);
	if(!ITER_EQUAL(iter, last))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");

	printf("to find 10:\n");
	iter = c_find(first, last, pary[10]);
	if(!ITER_EQUAL(iter, last))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	return 0;
}

static int test_find_by_c_vector()
{
	c_vector vector;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	c_iterator iter;

	__c_vector(&vector, int_comparer);
	c_vector_insert2(&vector, c_vector_end(&vector), first, last);

	printf("find by vector:\n");
	printf("to find 0:\n");
	iter = c_find(c_vector_begin(&vector), c_vector_end(&vector), pary[0]);
	if(!c_iter_equal(iter, c_vector_end(&vector)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 5:\n");
	iter = c_find(c_vector_begin(&vector), c_vector_end(&vector), pary[5]);
	if(!c_iter_equal(iter, c_vector_end(&vector)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 9:\n");
	iter = c_find(c_vector_begin(&vector), c_vector_end(&vector), pary[9]);
	if(!c_iter_equal(iter, c_vector_end(&vector)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");

	printf("to find 10:\n");
	iter = c_find(c_vector_begin(&vector), c_vector_end(&vector), pary[10]);
	if(!c_iter_equal(iter, c_vector_end(&vector)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");

	__c_rotcev(&vector);
	return 0;
}

static int test_find_by_c_list()
{
	c_list list;
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	c_iterator iter;

	__c_list(&list, int_comparer);
	c_list_insert2(&list, c_list_end(&list), first, last);

	printf("find by list:\n");
	printf("to find 0:\n");
	iter = c_find(c_list_begin(&list), c_list_end(&list), pary[0]);
	if(!c_iter_equal(iter, c_list_end(&list)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 5:\n");
	iter = c_find(c_list_begin(&list), c_list_end(&list), pary[5]);
	if(!c_iter_equal(iter, c_list_end(&list)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");
	
	printf("to find 9:\n");
	iter = c_find(c_list_begin(&list), c_list_end(&list), pary[9]);
	if(!c_iter_equal(iter, c_list_end(&list)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");

	printf("to find 10:\n");
	iter = c_find(c_list_begin(&list), c_list_end(&list), pary[10]);
	if(!c_iter_equal(iter, c_list_end(&list)))
		printf("find it! it's %d\n", *(int*)ITER_REF(iter));
	else
		printf("not find!\n");

	__c_tsil(&list);
	return 0;
}

static c_bool is_even(value_type val)
{
	return !((*((int*)val)) % 2);
}

static int test_find_if_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	printf("find_if is_even by array:\n");
	while(!ITER_EQUAL(first, last))
	{
		first = c_find_if(first, last, is_even);
		if(ITER_EQUAL(first, last))
			break;
		printf("find a even : %d\n", *(int *)ITER_REF(first));
		ITER_INC(first);
	}

	return 0;
}

static int test_find_if_by_c_vector()
{
	c_vector vector;
	c_iterator first, last;

	__c_vector(&vector, int_comparer);

	c_vector_insert2(&vector, c_vector_end(&vector), 
				c_get_array_iterator((void**)&pary[0]),
		       		c_get_array_iterator((void**)&pary[10]));

	first = c_vector_begin(&vector);
	last = c_vector_end(&vector);
	printf("find_if is_even by vector:\n");
	while(!ITER_EQUAL(first, last))
	{
		first = c_find_if(first, last, is_even);
		if(ITER_EQUAL(first, last))
			break;
		printf("find a even : %d\n", *(int *)ITER_REF(first));
		ITER_INC(first);
	}

	__c_rotcev(&vector);
	return 0;
}

static int test_find_if_by_c_list()
{
	c_list list;
	c_iterator first, last;

	__c_list(&list, int_comparer);

	c_list_insert2(&list, c_list_end(&list), 
				c_get_array_iterator((void**)&pary[0]),
		       		c_get_array_iterator((void**)&pary[10]));

	first = c_list_begin(&list);
	last = c_list_end(&list);

	printf("find_if is_even by list:\n");
	while(!ITER_EQUAL(first, last))
	{
		first = c_find_if(first, last, is_even);
		if(ITER_EQUAL(first, last))
			break;
		printf("find a even : %d\n", *(int *)ITER_REF(first));
		ITER_INC(first);
	}

	__c_tsil(&list);
	return 0;
}


static c_bool multi_equal_30(value_type x, value_type y)
{
	return  *(int*)(x) * *(int*)(y) == 30;
}

static int test_adjacent_find_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	c_iterator iter;

	printf("adjacent_find multi_equal_30 by array:\n");

	iter = c_adjacent_find(first, last, multi_equal_30);
	if(!ITER_EQUAL(iter, last))
	{
		printf("find : ");
		first = ITER_POSITIVE_N(iter, 1);
		printf("%d %d\n", *(int*)ITER_REF(iter), *(int*)ITER_REF(first));
	}
	else
		printf("not find!\n");

	return 0;	
}

static int test_adjacent_find_by_c_vector()
{
	c_vector vector;
	c_iterator first, last, iter;
	__c_vector(&vector, int_comparer);
	
	c_vector_insert2(&vector, c_vector_end(&vector), 
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	first = c_vector_begin(&vector);
	last = c_vector_end(&vector);

	printf("adjacent_find multi_equal_30 by c vector:\n");
	iter = c_adjacent_find(c_vector_begin(&vector), c_vector_end(&vector), multi_equal_30);
	if(!ITER_EQUAL(iter, last))
	{
		printf("find : ");
		first = ITER_POSITIVE_N(iter, 1);
		printf("%d %d\n", *(int*)ITER_REF(iter), *(int*)ITER_REF(first));
	}
	else
		printf("not find!\n");

	__c_rotcev(&vector);
	return 0;
}

static int test_adjacent_find_by_c_list()
{
	c_list list;
	c_iterator first, last, iter;
	__c_list(&list, int_comparer);
	
	c_list_insert2(&list, c_list_end(&list), 
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	first = c_list_begin(&list);
	last = c_list_end(&list);

	printf("adjacent_find multi_equal_30 by c list:\n");
	iter = c_adjacent_find(c_list_begin(&list), c_list_end(&list), multi_equal_30);
	if(!ITER_EQUAL(iter, last))
	{
		printf("find : ");
		first = iter;
		ITER_INC(first);
		printf("%d %d\n", *(int*)ITER_REF(iter), *(int*)ITER_REF(first));
	}
	else
		printf("not find!\n");

	__c_tsil(&list);
	return 0;
}



static int test_count_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	int i;

	printf("test count by c array:\n");

	for(i = 0; i < sizeof(pary) / sizeof(int *); ++ i)
	{
		printf("there are %d of %d in this array\n", c_count(first, last, pary[i]), *pary[i]);

	}

	return 0;
}

static int test_count_by_c_vector()	
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	int i;
	c_vector vector;

	__c_vector(&vector, int_comparer);
	c_vector_insert2(&vector, c_vector_end(&vector), first, last);

	printf("test count by c vector:\n");

	for(i = 0; i < sizeof(pary) / sizeof(int *); ++ i)
	{
		printf("there are %d of %d in this vector\n", c_count(c_vector_begin(&vector), 
									c_vector_end(&vector),
									 pary[i]), *pary[i]);
	}

	__c_rotcev(&vector);
	return 0;
}

static int test_count_by_c_list()
{	
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	int i;
	c_list list;

	__c_list(&list, int_comparer);
	c_list_insert2(&list, c_list_end(&list), first, last);

	printf("test count by c array:\n");

	for(i = 0; i < sizeof(pary) / sizeof(int *); ++ i)
	{
		printf("there are %d of %d in this list\n", c_count(c_list_begin(&list), 
									c_list_end(&list), 
									pary[i]), 
									*pary[i]);
	}

	__c_tsil(&list);
	return 0;
}

static int test_count_if_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);
	
	printf("test count by c vector\n");

	printf("there are %d of even in this array\n", c_count_if(first, 
									last,
									is_even));

	return 0;
}

static int test_count_if_by_c_vector()
{
	c_vector vector;
	__c_vector(&vector, int_comparer);
	c_vector_insert2(&vector,
		       		c_vector_end(&vector),	
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	
	printf("test count by c vector\n");

	printf("there are %d of even in this vector\n", c_count_if(c_vector_begin(&vector), 
									c_vector_end(&vector),
									is_even));

	__c_rotcev(&vector);
	return 0;
}

static int test_count_if_by_c_list()
{
	c_list list;
	__c_list(&list, int_comparer);
	c_list_insert2(&list,
		       		c_list_end(&list),	
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	
	printf("test count by c list\n");

	printf("there are %d of even in this list\n", c_count_if(c_list_begin(&list), 
									c_list_end(&list),
									is_even));

	__c_tsil(&list);
	return 0;
}

static int test_reverse_by_c_array()
{
	c_iterator first = c_get_array_iterator((void**)&pary[0]);
	c_iterator last = c_get_array_iterator((void**)&pary[10]);

	printf("test reverse by c array\n");

	printf("before reverse:\n");
	print2(first, last);

	c_reverse(first, last);
	printf("after reverse:\n");
	print2(first, last);
	
	c_reverse(first, last);
	printf("after recover:\n");
	print2(first, last);
	
	return 0;
}

static int test_reverse_by_c_vector()
{
	c_vector vector;
	__c_vector(&vector, int_comparer);
	c_vector_insert2(&vector,
		       		c_vector_end(&vector),	
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	
	printf("test reverse by c vector\n");

	printf("before reverse:\n");
	print2(c_vector_begin(&vector), c_vector_end(&vector));

	c_reverse(c_vector_begin(&vector), c_vector_end(&vector));
	printf("after reverse:\n");
	print2(c_vector_begin(&vector), c_vector_end(&vector));

	c_reverse(c_vector_begin(&vector), c_vector_end(&vector));
	printf("after recover:\n");
	print2(c_vector_begin(&vector), c_vector_end(&vector));

	__c_rotcev(&vector);
	return 0;
}

static int test_reverse_by_c_list()
{
	c_list list;
	__c_list(&list, int_comparer);
	c_list_insert2(&list,
		       		c_list_end(&list),	
				c_get_array_iterator((void**)&pary[0]),
				c_get_array_iterator((void**)&pary[10]));
	
	printf("test reverse by c list\n");
		
	printf("before reverse:\n");
	print2(c_list_begin(&list), c_list_end(&list));

	c_reverse(c_list_begin(&list), c_list_end(&list));
	printf("after reverse:\n");
	print2(c_list_begin(&list), c_list_end(&list));

	c_reverse(c_list_begin(&list), c_list_end(&list));
	printf("after recover:\n");
	print2(c_list_begin(&list), c_list_end(&list));
	
	__c_tsil(&list);
	return 0;
}

static int test_search_by_c_array()
{
	c_iterator first = c_get_array_iterator((void **)&pary[0]);
	c_iterator last = c_get_array_iterator((void **)&pary[10]);

	int * tmppary[] = { &ary[3], &ary[2], &ary[1], &ary[0], &ary[4], &ary[5], &ary[6], &ary[7], &ary[8], &ary[9], 0 };
	
	c_iterator result;

	printf("\n\ntest search by c array\n");
	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[1]),
				is_int_equal);

	printf("\nsearch [tmppary[0], tmppary[1])\n");
	print2(result, last);

	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[2]),
				is_int_equal);
	printf("\nsearch [tmppary[0], tmppary[2])\n");
	print2(result, last);

	
	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[5]),
				c_get_array_iterator((void **)&tmppary[7]),
				is_int_equal);
	printf("\nsearch [tmppary[5], tmppary[7])\n");
	print2(result, last);

	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[4]),
				c_get_array_iterator((void **)&tmppary[10]),
				is_int_equal);
	printf("\nsearch [tmppary[4], tmppary[10])\n");
	print2(result, last);

	return 0;	
}


static int test_search_by_c_vector()
{
	c_vector vector;
	c_iterator first, last;
	c_iterator result;
	int * tmppary[] = { &ary[3], &ary[2], &ary[1], &ary[0], &ary[4], &ary[5], &ary[6], &ary[7], &ary[8], &ary[9], 0 };
	
	__c_vector(&vector, int_comparer);
	c_vector_insert2(&vector, c_vector_end(&vector), 
			c_get_array_iterator((void **)&pary[0]), c_get_array_iterator((void **)&pary[10]));

	first = c_vector_begin(&vector);
	last = c_vector_end(&vector);


	printf("\n\ntest search by c vector\n");
	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[1]),
				is_int_equal);

	printf("\nsearch [tmppary[0], tmppary[1])\n");
	print2(result, last);

	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[2]),
				is_int_equal);
	printf("\nsearch [tmppary[0], tmppary[2])\n");
	print2(result, last);

	
	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[5]),
				c_get_array_iterator((void **)&tmppary[7]),
				is_int_equal);
	printf("\nsearch [tmppary[5], tmppary[7])\n");
	print2(result, last);

	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[4]),
				c_get_array_iterator((void **)&tmppary[10]),
				is_int_equal);
	printf("\nsearch [tmppary[4], tmppary[10])\n");
	print2(result, last);
	

	__c_rotcev(&vector);
	return 0;
}

static int test_search_by_c_list()
{
	c_list list;
	c_iterator first, last;
	c_iterator result;
	int * tmppary[] = { &ary[3], &ary[2], &ary[1], &ary[0], &ary[4], &ary[5], &ary[6], &ary[7], &ary[8], &ary[9], 0 };
	
	__c_list(&list, int_comparer);
	c_list_insert2(&list, c_list_end(&list), 
			c_get_array_iterator((void **)&pary[0]), c_get_array_iterator((void **)&pary[10]));

	first = c_list_begin(&list);
	last = c_list_end(&list);

	printf("\n\ntest search by c list\n");
	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[1]),
				is_int_equal);

	printf("\nsearch [tmppary[0], tmppary[1])\n");
	print2(result, last);

	result = c_search(first, last, 
				c_get_array_iterator((void **)&tmppary[0]),
				c_get_array_iterator((void **)&tmppary[2]),
				is_int_equal);
	printf("\nsearch [tmppary[0], tmppary[2])\n");
	print2(result, last);

	
	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[5]),
				c_get_array_iterator((void **)&tmppary[7]),
				is_int_equal);
	printf("\nsearch [tmppary[5], tmppary[7])\n");
	print2(result, last);

	result = c_search(first, last,
				c_get_array_iterator((void **)&tmppary[4]),
				c_get_array_iterator((void **)&tmppary[10]),
				is_int_equal);
	printf("\nsearch [tmppary[4], tmppary[10])\n");
	print2(result, last);
	

	__c_tsil(&list);
	return 0;
}


int t_algo()
{
	printf("\n\n0.test c array\n");
	test_c_array();

	printf("\n\n1.test advance\n");
	test_advance_by_c_array();
	test_advance_by_c_vector();
	test_advance_by_c_list();


	printf("\n\n2.test for_each\n");
	test_for_each_by_c_array();
	test_for_each_by_c_vector();
	test_for_each_by_c_list();

	printf("\n\n3.test find\n");
	test_find_by_c_array();
	test_find_by_c_vector();
	test_find_by_c_list();

	printf("\n\n4.test find_if\n");
	test_find_if_by_c_array();
	test_find_if_by_c_vector();
	test_find_if_by_c_list();

	printf("\n\n5.test adjacent_find\n");
	test_adjacent_find_by_c_array();
	test_adjacent_find_by_c_vector();
	test_adjacent_find_by_c_list();

	printf("\n\n6.test count\n");
	test_count_by_c_array();
	test_count_by_c_vector();
	test_count_by_c_list();

	printf("\n\n7.test count_if\n");
	test_count_if_by_c_array();
	test_count_if_by_c_vector();
	test_count_if_by_c_list();
	
	printf("\n\n8.test reverse\n");	
	test_reverse_by_c_array();
	test_reverse_by_c_vector();
	test_reverse_by_c_list();

	printf("\n\n9.test search\n");
	test_search_by_c_array();
	test_search_by_c_vector();
	test_search_by_c_list();



	

	printf("finish testing algorithm!\n");
	return 0;
}
