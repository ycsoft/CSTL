#include <stdio.h>
#include <stdlib.h>
#include "../include/c_def.h"
#include "../include/c_vector.h"
#include "c_map.h"
#include <assert.h>
#include "t_test.h"

c_bool __c_rb_tree_verify(c_prb_tree thiz);

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



static int print_map(c_pmap pt)
{
	c_iterator iter = c_map_begin(pt);
	c_iterator end = c_map_end(pt);
	printf("map is:\n");
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
		printf("key = %d, value = %d\n",
			*(int*)((c_ppair)ITER_REF(iter))->first,
			*(int*)((c_ppair)ITER_REF(iter))->second);
	}
	return 0;
}

static int rprint_map(c_pmap pt)
{
	c_reverse_iterator iter = c_map_rbegin(pt);
	c_reverse_iterator end = c_map_rend(pt);
	printf("map is:\n");
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
		printf("key = %d, value = %d\n",
			*(int*)((c_ppair)ITER_REF(iter))->first,
			*(int*)((c_ppair)ITER_REF(iter))->second);
	}
	return 0;
}


static int create_with_insert_unique(c_pmap thiz)
{
	int i = 0;
	for(; i < sizeof(keys) / sizeof(int); ++ i)
	{
		c_map_insert(thiz, &pairs[i]);
		assert(__c_rb_tree_verify(thiz->_l));
	}

	return 0;
}

static int create_with_insert_equal(c_pmap thiz)
{
	return 0;
}

static int test_clear(c_pmap thiz)
{
	c_iterator begin, end;
	c_reverse_iterator rbegin, rend;
	c_map_clear(thiz);
	begin = c_map_begin(thiz);
	end = c_map_end(thiz);
	rbegin = c_map_rbegin(thiz);
	rend = c_map_rend(thiz);
	
	if(c_map_size(thiz) == 0)
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

static int test_size_empty(c_pmap thiz)
{
	int i = 0;
	printf("max size is %d\n", c_map_max_size(thiz));
	printf("size is %d\n", c_map_size(thiz));
	printf("is empty? %s\n", c_map_empty(thiz) ? "yes" : "no");
	
	for(; i < sizeof(values) / sizeof(int); ++ i)
	{
		printf("now insert %d\n", i + 1);
		c_map_insert(thiz, &pairs[i]);
		printf("size is %d\n", c_map_size(thiz));
		printf("is empty? %s\n", c_map_empty(thiz) ? "yes" : "no");
	}
	printf("now clear\n");
	c_map_clear(thiz);
	printf("size is %d\n", c_map_size(thiz));
	printf("is empty? %s\n", c_map_empty(thiz) ? "yes" : "no");

	return 0;
}

static int test_swap(c_pmap thiz)
{
	c_map tr;
	c_map_create(&tr, int_comparer);	
	
	c_map_swap(thiz, &tr);
	printf("after swap\n");
	print_map(&tr);
	c_map_destroy(&tr);	
	return 0;
}

static int create_with_insert_unique1(c_pmap thiz)
{
	c_iterator iter = c_map_begin(thiz);
	int i = 0;
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
		iter = c_map_insert1(thiz, iter, &pairs[i]);
		assert(__c_rb_tree_verify(thiz->_l));
	}
	return 0;
}

static int create_with_insert_equal1(c_pmap thiz)
{
	return 0;
}

static int create_with_insert_unique2(c_pmap thiz)
{
	c_vector vt;
	int i = 0;
	c_vector_create(&vt, int_comparer);
	for(i = 0; i < sizeof(values) / sizeof(int); ++ i)
	{
		c_iterator v_beg, v_end;
		c_vector_push_back(&vt, &pairs[i]);

		v_beg = c_vector_begin(&vt);
		v_end = c_vector_end(&vt);
		c_map_insert2(thiz, v_beg, v_end);

		assert(__c_rb_tree_verify(thiz->_l));
	}

	c_vector_destroy(&vt);
	return 0;
}

static int create_with_insert_equal2(c_pmap thiz)
{
	return 0;
}

static void assert_valid_iter(c_pmap thiz, c_iterator val)
{
	c_iterator end = c_map_end(thiz);
	c_iterator iter = c_map_begin(thiz);
	for(; !ITER_EQUAL(iter, end); ITER_INC(iter))
	{
		if(ITER_EQUAL(iter, val))
			return;
	}
	assert(false);
}

static int test_erase(c_pmap thiz)
{
	c_iterator iter = c_map_begin(thiz);
	c_iterator end = c_map_end(thiz);
	assert(__c_rb_tree_verify(thiz->_l));
	//c_map_erase(thiz, end);  // erasing end results in error
	assert(__c_rb_tree_verify(thiz->_l));
	while(!ITER_EQUAL(iter, end))
	{
		c_iterator to_erase = iter;
		assert_valid_iter(thiz, to_erase);
		c_map_erase(thiz, to_erase);
		assert(__c_rb_tree_verify(thiz->_l));
		
		iter = c_map_begin(thiz);
		end = c_map_end(thiz);
	}
	assert(__c_rb_tree_verify(thiz->_l));
	assert(c_map_empty(thiz));
	return 0;
}

static int test_reverse_erase(c_pmap thiz)
{
	c_iterator iter = c_map_begin(thiz);
	c_iterator end = c_map_end(thiz);
	assert(__c_rb_tree_verify(thiz->_l));
	//c_map_erase(thiz, end);  // erasing end results in error
	assert(__c_rb_tree_verify(thiz->_l));
	while(!ITER_EQUAL(iter, end))
	{
		c_iterator to_erase = end;
		ITER_DEC(to_erase);
		assert_valid_iter(thiz, to_erase);
		c_map_erase(thiz, to_erase);
		assert(__c_rb_tree_verify(thiz->_l));

		iter = c_map_begin(thiz);
		end = c_map_end(thiz);
	}
	assert(__c_rb_tree_verify(thiz->_l));
	assert(c_map_empty(thiz));
	return 0;
}

static int test_find_erase(c_pmap thiz)
{
	int j = 0;
	for(j = 0; j < sizeof(keys) / sizeof(int); ++ j)
	{
		c_iterator target, map_end;	
		printf("j = %d, key = %d\n", j, keys[j]);

		target = c_map_find(thiz, &keys[j]); // set same as map 
			
		map_end = c_map_end(thiz);
		if(!ITER_EQUAL(map_end, target))
		{
			printf("to erase : %d\n", *(int*)(((c_ppair)ITER_REF(target))->first));

			assert_valid_iter(thiz, target);
			c_map_erase(thiz, target);
			assert(__c_rb_tree_verify(thiz->_l));
		}			
	}
	return 0;
}

static int test_reverse_find_erase(c_pmap thiz)
{
	int j = 0;
	for(j = sizeof(keys) / sizeof(int) - 1; j >= 0; -- j)
	{
		c_iterator target, map_end;	
		printf("j = %d\n", j);

		target = c_map_find(thiz, &keys[j]); // set same as map
		
		map_end = c_map_end(thiz);
		if(!ITER_EQUAL(map_end, target))
		{			
			printf("to erase : %d\n", *(int*)(((c_ppair)ITER_REF(target))->first));
			assert_valid_iter(thiz, target);
			c_map_erase(thiz, target);
			assert(__c_rb_tree_verify(thiz->_l));
		}			
	}
	return 0;	
}

static int test_count(c_pmap thiz)
{
	int i = 0;
	create_with_insert_equal2(thiz);
		
	for(i = 0; i < sizeof(keys) / sizeof(int); ++ i)
	{
		size_t count = c_map_count(thiz, &keys[i]);
		printf("i : %d; key : %d; count : %d\n", i, keys[i], count);
	}
	return 0;
}

static int test_less()
{
	c_bool rt;
	c_map ta, tb;

	c_map_create(&ta, int_comparer);
	c_map_create(&tb, int_comparer);

	
	create_with_insert_equal(&ta);
	create_with_insert_equal(&tb);
	printf("*ta is :\n");
	print_map(&ta);
	printf("*tb is :\n");
	print_map(&tb);
	rt = c_map_less(&ta, &tb, pair_comparer);
	if(rt)
		printf("is less\n");
	else
		printf("is not less\n");

	c_map_clear(&ta);
	c_map_clear(&tb);
	create_with_insert_unique(&ta);
	create_with_insert_equal(&tb);
	printf("*ta is :\n");
	print_map(&ta);
	printf("*tb is :\n");
	print_map(&tb);
	rt = c_map_less(&ta, &tb, pair_comparer);
	if(rt)
		printf("is less\n");
	else 
		printf("is not less\n");

	c_map_clear(&ta);
	c_map_clear(&tb);
	create_with_insert_equal(&ta);
	create_with_insert_unique(&tb);
	printf("*ta is :\n");
	print_map(&ta);
	printf("*tb is :\n");
	print_map(&tb);
	rt = c_map_less(&ta, &tb, pair_comparer);

	if(rt)
		printf("is less\n");
	else 
		printf("is not less\n");

	return 0;
}


static int test_equal()
{
	c_bool rt;
	c_map ta, tb;

	c_map_create(&ta, int_comparer);
	c_map_create(&tb, int_comparer);

	
	create_with_insert_equal(&ta);
	create_with_insert_equal(&tb);
	rt = c_map_equal(&ta, &tb, pair_comparer);
	if(rt)
		printf("is equal\n");
	else
		printf("is not equal\n");

	c_map_clear(&ta);
	c_map_clear(&tb);
	create_with_insert_unique(&ta);
	create_with_insert_equal(&tb);
	rt = c_map_equal(&ta, &tb, pair_comparer);

	if(rt)
		printf("is equal\n");
	else 
		printf("is not equal\n");

	c_map_clear(&ta);
	c_map_clear(&tb);
	create_with_insert_equal(&ta);
	create_with_insert_unique(&tb);
	rt = c_map_equal(&ta, &tb, pair_comparer);
	if(rt)
		printf("is equal\n");
	else 
		printf("is not equal\n");

	return 0;
}

static int test_at()
{
	c_map m;
	value_type val = NULL;
	int key = 84;
	int nonkeys[] = { 5, -1, -28, -998, -62356, 95238 };
	int i = 0;
	c_map_create(&m, int_comparer);
	create_with_insert_unique(&m);

	val = c_map_at(&m, &key);

	if(val != NULL)
	{
		printf("map at %i, value is %i\n", key, *(int*)val);
	}

	for(i = 0; i < sizeof(keys) / sizeof(int); ++ i)
	{
		val = c_map_at(&m, &keys[i]);
		if(val != NULL)
		{
			printf("map at %i, value is %i\n", keys[i], *(int*)val);
		}
	}

	for(i = 0; i < sizeof(nonkeys) /sizeof(int); ++ i)
	{
		val = c_map_at(&m, &nonkeys[i]);
		if(val != NULL)
			assert(false);
		else
			printf("ok! pass!\n");
	}
	
	c_map_destroy(&m);
}

int t_map()
{
	c_map map;

	c_map_create(&map, int_comparer);

	
	assert(__c_rb_tree_verify(map._l));
	printf("0. test create with insert unique\n");
	create_with_insert_unique(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n1. test clear\n");
	test_clear(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n2. test size and empty\n");
	test_size_empty(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n3. test create with insert equal\n");
	c_map_clear(&map);
	create_with_insert_equal(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n4. test swap\n");
	create_with_insert_unique(&map);
	test_swap(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n5. test create with insert unique1\n");
	create_with_insert_unique1(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n6. test create with insert equal1\n");
	c_map_clear(&map);
	create_with_insert_equal1(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n7. test create with insert unique2\n");
	c_map_clear(&map);
	create_with_insert_unique2(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n8. test create with insert equal2\n");
	c_map_clear(&map);
	create_with_insert_equal2(&map);
	print_map(&map);
	rprint_map(&map);
	assert(__c_rb_tree_verify(map._l));
	
	printf("\n\n9. test erase\n");
	c_map_clear(&map);
	create_with_insert_unique(&map);
	test_erase(&map);
	create_with_insert_unique(&map);	
	test_reverse_erase(&map);	
	print_map(&map);
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n10. test find and erase\n");
	c_map_clear(&map);
	printf("* test_find_erase:\n");
	create_with_insert_unique(&map);
	print_map(&map);	
	test_find_erase(&map);
	print_map(&map);	
	printf("* test_reverse_find_erase:\n");
	create_with_insert_unique(&map);
	print_map(&map);	
	test_reverse_find_erase(&map);
	print_map(&map);	
	assert(__c_rb_tree_verify(map._l));

	printf("\n\n11. test count:\n"); // 'lower_bound' 'upper_bound' 'equal_range' used	
	create_with_insert_unique(&map);
	test_count(&map);

	printf("\n\n12. test less:\n");
	test_less();

	printf("\n\n13. test equal:\n");
	test_equal();

	printf("\n\n14. test at:\n");
	test_at();
	
	c_map_destroy(&map);
	printf("\n\nfinish testing map!\n");
	return 0;
}
