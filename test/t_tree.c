#include <stdio.h>
#include <stdlib.h>
#include "../include/c_def.h"
#include "../include/c_vector.h"
#include "../c_tree.h"
#include <assert.h>
#include "t_test.h"


#define MAP	0
#define SET	1

#define IMPL	MAP
//#define IMPL 	SET


static int values[] = 
{ 
	8,	/* 0 */
	3,	/* 1 */
	8,	/* 2 */
	4,	/* 3 */
	3,	/* 4 */
	8,	/* 5 */
	5,	/* 6 */
	43,	/* 7 */
	994,	/* 8 */
	32,	/* 9 */
	6,	/* 10 */
	9,	/* 11 */
	3,	/* 12 */
	7,	/* 13 */
	7,	/* 14 */
	32,	/* 15 */
	8,	/* 16 */
	2,	/* 17 */
	343 	/* 18 */
};

static inline int int_comparer(void * x, void * y)
{
    return *(int *)(x) - *(int *)(y);
}

static int keys[] = 
{ 
	12,	/* 0 */	
	4,	/* 1 */	
	71,	/* 2 */
	2,	/* 3 */
	90,	/* 4 */
	99,	/* 5 */
	30,	/* 6 */
	61,	/* 7 */
	29,	/* 8 */
	84,	/* 9 */
	6,	/* 10 */
	97,	/* 11 */
	3,	/* 12 */
	8,	/* 13 */
	54,	/* 14 */
	78,	/* 15 */
	9,	/* 16 */
	16,	/* 17 */
	62,	/* 18 */
};

static c_pair pairs[] =
{
	{ &keys[0], &values[0] },
	{ &keys[1], &values[1] },
	{ &keys[2], &values[2] },
	{ &keys[3], &values[3] },
	{ &keys[4], &values[4] },
	{ &keys[5], &values[5] },
	{ &keys[6], &values[6] },
	{ &keys[7], &values[7] },
	{ &keys[8], &values[8] },
	{ &keys[9], &values[9] },
	{ &keys[10], &values[10] },
	{ &keys[11], &values[11] },
	{ &keys[12], &values[12] },
	{ &keys[13], &values[13] },
	{ &keys[14], &values[14] },
	{ &keys[15], &values[15] },
	{ &keys[16], &values[16] },
	{ &keys[17], &values[17] },
	{ &keys[18], &values[18] }
};

static inline int pair_comparer(void * x, void * y)
{
	value_type x_f = ((c_ppair)x)->first;
	value_type x_s = ((c_ppair)x)->second;
	value_type y_f = ((c_ppair)y)->first;
	value_type y_s = ((c_ppair)y)->second;
	int f_val = int_comparer(x_f, y_f);
	if(!f_val)
		return int_comparer(x_s, y_s);
	else
		return f_val; 
}



int print_tree(c_prb_tree pt)
{
	c_iterator iter = c_rb_tree_begin(pt);
	c_iterator end = c_rb_tree_end(pt);
	printf("tree is:\n");
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
#if IMPL == MAP
		printf("key = %d, value = %d\n",
			*(int*)((c_ppair)ITER_REF(iter))->first,
			*(int*)((c_ppair)ITER_REF(iter))->second);
#endif

#if IMPL == SET
		printf("value = %d\n",
			*(int*)(ITER_REF(iter)));
#endif
	}
	return 0;
}

int rprint_tree(c_prb_tree pt)
{
	c_reverse_iterator iter = c_rb_tree_rbegin(pt);
	c_reverse_iterator end = c_rb_tree_rend(pt);
	printf("tree is:\n");
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
#if IMPL == MAP
		printf("key = %d, value = %d\n",
			*(int*)((c_ppair)ITER_REF(iter))->first,
			*(int*)((c_ppair)ITER_REF(iter))->second);
#endif

#if IMPL == SET
		printf("value = %d\n",
			*(int*)(ITER_REF(iter)));
#endif
	}
	return 0;
}


int create_with_insert_unique(c_prb_tree thiz)
{
	int i = 0;
	for(; i < sizeof(keys) / sizeof(int); ++ i)
	{
#if IMPL == MAP
		c_rb_tree_insert_unique(thiz, &pairs[i]);
#endif
#if IMPL == SET
		c_rb_tree_insert_unique(thiz, &keys[i]);
#endif
		assert(__c_rb_tree_verify(thiz));
	}
	return 0;
}

int create_with_insert_equal(c_prb_tree thiz)
{
	int i = 0;
	for(; i < sizeof(values) / sizeof(int); ++ i)
	{
#if IMPL == MAP
		c_rb_tree_insert_equal(thiz, &pairs[i]);
#endif
#if IMPL == SET
		c_rb_tree_insert_equal(thiz, &values[i]);
#endif
		assert(__c_rb_tree_verify(thiz));
	}
	return 0;
}

int test_clear(c_prb_tree thiz)
{
	c_iterator begin, end;
	c_reverse_iterator rbegin, rend;
	c_rb_tree_clear(thiz);
	begin = c_rb_tree_begin(thiz);
	end = c_rb_tree_end(thiz);
	rbegin = c_rb_tree_rbegin(thiz);
	rend = c_rb_tree_rend(thiz);
	
	if(c_rb_tree_size(thiz) == 0)
		printf("ok, size is 0\n");
	else
		printf("error, size is not 0\n");
	
	if(ITER_EQUAL(begin, end))
		printf("ok, begin == end\n");
	else
		printf("error, begin != end\n");
	
	if(ITER_EQUAL(rbegin, rend))
		printf("ok, rbegin == rend\n");
	else
		printf("error, rbegin != rend\n");
	return 0;
}

int test_size_empty(c_prb_tree thiz)
{
	int i = 0;
	printf("max size is %d\n", c_rb_tree_max_size(thiz));
	printf("size is %d\n", c_rb_tree_size(thiz));
	printf("is empty? %s\n", c_rb_tree_empty(thiz) ? "yes" : "no");
	
	for(; i < sizeof(values) / sizeof(int); ++ i)
	{
		printf("now insert %d\n", i + 1);
#if IMPL == MAP
		c_rb_tree_insert_unique(thiz, &pairs[i]);
#endif
#if IMPL == SET
		c_rb_tree_insert_unique(thiz, &values[i]);
#endif
		printf("size is %d\n", c_rb_tree_size(thiz));
		printf("is empty? %s\n", c_rb_tree_empty(thiz) ? "yes" : "no");
	}
	printf("now clear\n");
	c_rb_tree_clear(thiz);
	printf("size is %d\n", c_rb_tree_size(thiz));
	printf("is empty? %s\n", c_rb_tree_empty(thiz) ? "yes" : "no");

	return 0;
}

int test_swap(c_prb_tree thiz)
{
	c_rb_tree tr;
	c_rb_tree_create(&tr, int_comparer);	
#if IMPL == MAP
	tr._A_keyofvalue = c_select1st();	
#endif

#if IMPL == SET
	tr._A_keyofvalue = c_identity();
#endif
	c_rb_tree_swap(thiz, &tr);
	printf("after swap\n");
	print_tree(&tr);
	c_rb_tree_destroy(&tr);	
	return 0;
}

int create_with_insert_unique1(c_prb_tree thiz)
{
	c_iterator iter = c_rb_tree_begin(thiz);
	int i = 0;
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
#if IMPL == MAP
		iter = c_rb_tree_insert_unique1(thiz, iter, &pairs[i]);
#else
		iter = c_rb_tree_insert_unique1(thiz, iter, &keys[i]);
#endif
		assert(__c_rb_tree_verify(thiz));
	}
	return 0;
}

int create_with_insert_equal1(c_prb_tree thiz)
{
	c_iterator iter = c_rb_tree_begin(thiz);
	int i = 0;
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
#if IMPL == MAP
		iter = c_rb_tree_insert_equal1(thiz, iter, &pairs[i]);
#else
		iter = c_rb_tree_insert_equal1(thiz, iter, &values[i]);
#endif	
		assert(__c_rb_tree_verify(thiz));
	}
	return 0;
}

int create_with_insert_unique2(c_prb_tree thiz)
{
	c_vector vt;
	int i = 0;
	c_vector_create(&vt, int_comparer);
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
		c_iterator v_beg, v_end;
#if IMPL == MAP
		c_vector_push_back(&vt, &pairs[i]);
#else
		c_vector_push_back(&vt, &keys[i]);
#endif
		v_beg = c_vector_begin(&vt);
		v_end = c_vector_end(&vt);
		c_rb_tree_insert_unique2(thiz, v_beg, v_end);

		assert(__c_rb_tree_verify(thiz));
	}

	c_vector_destroy(&vt);
	return 0;
}

int create_with_insert_equal2(c_prb_tree thiz)
{
	c_vector vt;
	int i = 0;
	c_vector_create(&vt, int_comparer);
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
		c_iterator v_beg, v_end;
#if IMPL == MAP
		c_vector_push_back(&vt, &pairs[i]);
#else
		c_vector_push_back(&vt, &values[i]);
#endif
		v_beg = c_vector_begin(&vt);
		v_end = c_vector_end(&vt);
		c_rb_tree_insert_equal2(thiz, v_beg, v_end);
		
		assert(__c_rb_tree_verify(thiz));
	}

	c_vector_destroy(&vt);
	return 0;
}

void assert_valid_iter(c_prb_tree thiz, c_iterator val)
{
	c_iterator end = c_rb_tree_end(thiz);
	c_iterator iter = c_rb_tree_begin(thiz);
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
		if(ITER_EQUAL(iter, val))
			return;
	}
	assert(false);
}

int test_erase(c_prb_tree thiz)
{
	c_iterator iter = c_rb_tree_begin(thiz);
	c_iterator end = c_rb_tree_end(thiz);
	assert(__c_rb_tree_verify(thiz));
	//c_rb_tree_erase(thiz, end);  // erasing end results in error
	assert(__c_rb_tree_verify(thiz));
	while(!ITER_EQUAL(iter, end))
	{
		c_iterator to_erase = iter;
		assert_valid_iter(thiz, to_erase);
		c_rb_tree_erase(thiz, to_erase);
		assert(__c_rb_tree_verify(thiz));
		
		iter = c_rb_tree_begin(thiz);
		end = c_rb_tree_end(thiz);
	}
	assert(__c_rb_tree_verify(thiz));
	assert(c_rb_tree_empty(thiz));
	return 0;
}

int test_reverse_erase(c_prb_tree thiz)
{
	c_iterator iter = c_rb_tree_begin(thiz);
	c_iterator end = c_rb_tree_end(thiz);
	assert(__c_rb_tree_verify(thiz));
	//c_rb_tree_erase(thiz, end);  // erasing end results in error
	assert(__c_rb_tree_verify(thiz));
	while(!ITER_EQUAL(iter, end))
	{
		c_iterator to_erase = end;
		ITER_DEC(to_erase);
		assert_valid_iter(thiz, to_erase);
		c_rb_tree_erase(thiz, to_erase);
		assert(__c_rb_tree_verify(thiz));

		iter = c_rb_tree_begin(thiz);
		end = c_rb_tree_end(thiz);
	}
	assert(__c_rb_tree_verify(thiz));
	assert(c_rb_tree_empty(thiz));
	return 0;
}

int test_find_erase(c_prb_tree thiz)
{
	int j = 0;
	for(j = 0; j < sizeof(keys) / sizeof(int); ++ j)
	{
		c_iterator target, tree_end;	
		printf("j = %d, key = %d\n", j, keys[j]);

		target = c_rb_tree_find(thiz, &keys[j]); // set same as map 
			
		tree_end = c_rb_tree_end(thiz);
		if(!ITER_EQUAL(tree_end, target))
		{
#if IMPL == MAP
			printf("to erase : %d\n", *(int*)(((c_ppair)ITER_REF(target))->first));
#else
			printf("to erase : %d\n", *(int*)ITER_REF(target));
#endif

			assert_valid_iter(thiz, target);
			c_rb_tree_erase(thiz, target);
			assert(__c_rb_tree_verify(thiz));
		}			
	}
	return 0;
}

int test_reverse_find_erase(c_prb_tree thiz)
{
	int j = 0;
	for(j = sizeof(keys) / sizeof(int) - 1; j >= 0; -- j)
	{
		c_iterator target, tree_end;	
		printf("j = %d\n", j);

		target = c_rb_tree_find(thiz, &keys[j]); // set same as map
		
		tree_end = c_rb_tree_end(thiz);
		if(!ITER_EQUAL(tree_end, target))
		{			
#if IMPL == MAP
			printf("to erase : %d\n", *(int*)(((c_ppair)ITER_REF(target))->first));
#else
			printf("to erase : %d\n", *(int*)ITER_REF(target));
#endif
			assert_valid_iter(thiz, target);
			c_rb_tree_erase(thiz, target);
			assert(__c_rb_tree_verify(thiz));
		}			
	}
	return 0;	
}

int test_count(c_prb_tree thiz)
{
	int i = 0;
	create_with_insert_equal2(thiz);
		
	for(i = 0; i < sizeof(keys) / sizeof(int); ++ i)
	{
		size_t count = c_rb_tree_count(thiz, &keys[i]);
		printf("i : %d; key : %d; count : %d\n", i, keys[i], count);
	}
	return 0;
}

int test_less()
{
	c_bool rt;
	c_rb_tree ta, tb;

	c_rb_tree_create(&ta, int_comparer);
	c_rb_tree_create(&tb, int_comparer);

#if IMPL == MAP
	ta._A_keyofvalue = tb._A_keyofvalue = c_select1st();
#else
	ta._A_keyofvalue = tb._A_keyofvalue = c_identity();
#endif

	create_with_insert_equal(&ta);
	create_with_insert_equal(&tb);
#if IMPL == MAP
	rt = c_rb_tree_less(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_less(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is less\n");
	else
		printf("is not less\n");

	c_rb_tree_clear(&ta);
	c_rb_tree_clear(&tb);
	create_with_insert_unique(&ta);
	create_with_insert_equal(&tb);
#if IMPL == MAP
	rt = c_rb_tree_less(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_less(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is less\n");
	else 
		printf("is not less\n");

	c_rb_tree_clear(&ta);
	c_rb_tree_clear(&tb);
	create_with_insert_equal(&ta);
	create_with_insert_unique(&tb);
#if IMPL == MAP
	rt = c_rb_tree_less(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_less(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is less\n");
	else 
		printf("is not less\n");

	return 0;
}


int test_equal()
{
	c_bool rt;
	c_rb_tree ta, tb;

	c_rb_tree_create(&ta, int_comparer);
	c_rb_tree_create(&tb, int_comparer);

#if IMPL == MAP
	ta._A_keyofvalue = tb._A_keyofvalue = c_select1st();
#else
	ta._A_keyofvalue = tb._A_keyofvalue = c_identity();
#endif

	create_with_insert_equal(&ta);
	create_with_insert_equal(&tb);
#if IMPL == MAP
	rt = c_rb_tree_equal(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_equal(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is equal\n");
	else
		printf("is not equal\n");

	c_rb_tree_clear(&ta);
	c_rb_tree_clear(&tb);
	create_with_insert_unique(&ta);
	create_with_insert_equal(&tb);
#if IMPL == MAP
	rt = c_rb_tree_equal(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_equal(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is equal\n");
	else 
		printf("is not equal\n");

	c_rb_tree_clear(&ta);
	c_rb_tree_clear(&tb);
	create_with_insert_equal(&ta);
	create_with_insert_unique(&tb);
#if IMPL == MAP
	rt = c_rb_tree_equal(&ta, &tb, pair_comparer);
#else
	rt = c_rb_tree_equal(&ta, &tb, int_comparer);
#endif
	if(rt)
		printf("is equal\n");
	else 
		printf("is not equal\n");

	return 0;
}

int t_tree()
{
	c_rb_tree tree;

	__c_rb_tree(&tree, int_comparer);

#if IMPL == MAP
	tree._A_keyofvalue = c_select1st();	
#endif
#if IMPL == SET
	tree._A_keyofvalue = c_identity();
#endif

	assert(__c_rb_tree_verify(&tree));
	printf("0. test create with insert unique\n");
	create_with_insert_unique(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n1. test clear\n");
	test_clear(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n2. test size and empty\n");
	test_size_empty(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n3. test create with insert equal\n");
	c_rb_tree_clear(&tree);
	create_with_insert_equal(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n4. test swap\n");
	test_swap(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n5. test create with insert unique1\n");
	create_with_insert_unique1(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n6. test create with insert equal1\n");
	c_rb_tree_clear(&tree);
	create_with_insert_equal1(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n7. test create with insert unique2\n");
	c_rb_tree_clear(&tree);
	create_with_insert_unique2(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n8. test create with insert equal2\n");
	c_rb_tree_clear(&tree);
	create_with_insert_equal2(&tree);
	print_tree(&tree);
	rprint_tree(&tree);
	assert(__c_rb_tree_verify(&tree));
	
	printf("\n\n9. test erase\n");
	c_rb_tree_clear(&tree);
	create_with_insert_unique(&tree);
	test_erase(&tree);
	create_with_insert_unique(&tree);	
	test_reverse_erase(&tree);	
	print_tree(&tree);
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n10. test find and erase\n");
	c_rb_tree_clear(&tree);
	printf("* test_find_erase:\n");
	create_with_insert_unique(&tree);
	print_tree(&tree);	
	test_find_erase(&tree);
	print_tree(&tree);	
	printf("* test_reverse_find_erase:\n");
	create_with_insert_unique(&tree);
	print_tree(&tree);	
	test_reverse_find_erase(&tree);
	print_tree(&tree);	
	assert(__c_rb_tree_verify(&tree));

	printf("\n\n11. test count:\n"); // 'lower_bound' 'upper_bound' 'equal_range' used	
	test_count(&tree);

	printf("\n\n12. test less:\n");
	test_less();

	printf("\n\n13. test equal:\n");
	test_equal();
	
	__c_eert_br(&tree);
	printf("\n\nfinish testing tree!\n");
	return 0;
}
