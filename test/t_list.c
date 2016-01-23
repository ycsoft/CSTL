#include <stdio.h>
#include <stdlib.h>
#include "../include/c_list.h"
#include "../include/c_algorithm.h"
#include "t_test.h"

int array[6] = { 0, 1, 2, 3, 4, 5 };

static inline int int_comparer(void * x, void * y)
{
    return *(int *)(x) - *(int *)(y);
}


static void print_list2(c_iterator first, c_iterator last)
{
    c_iterator iter;
    printf("list is :\n"); 
    for(iter = first;
          !ITER_EQUAL(iter, last); ITER_INC(iter))
    {
        printf("\t%d\n", *((int *)(ITER_REF(iter))));
    }
} 

static void print_list2_r(c_reverse_iterator first, c_reverse_iterator last)
{
    c_reverse_iterator iter;
    printf("list is :\n");
    for(iter = first; 
            !ITER_EQUAL(iter, last); ITER_INC(iter))
    {
        printf("\t%d\n", *((int *)(ITER_REF(iter))));
    }
}

static void print_list(c_list * p)
{
    c_iterator first, last;
    first = c_list_begin(p);
    last = c_list_end(p);
    print_list2(first, last);
}

static void reverse_print_list(c_list * p)
{
    c_reverse_iterator first, last;
    first = c_list_rbegin(p);
    last = c_list_rend(p);
    print_list2_r(first, last);
} 

static void create_with_push_back(c_list * p)
{
    int i = 0;
    for (; i < 6; ++ i)
    {
        c_list_push_back(p, &array[i]);
    }
}

static void create_with_push_front(c_list * p)
{
    int i = 0;
    for (; i < sizeof(array) / sizeof(int); ++ i)
    {
        c_list_push_front(p, &array[i]); 
    } 
}

void list_size(c_list * p)
{
    int i = 0;
    for (; i < sizeof(array) / sizeof(int); ++ i)
    {
        printf("is empty? %s\n", (c_list_empty(p) ? "yes" : "no"));
        printf("i = %d, size = %d\n", i, c_list_size(p));
        c_list_push_front(p, &array[i]); 
    } 
}

void list_assign(c_list * p)
{
    c_list lt;
    __c_list(&lt, int_comparer);
    c_list_assign(&lt, p);
    
    printf("list source:\n");
    print_list(p);
    printf("list dest:\n");
    print_list(&lt);
       
    __c_tsil(&lt);
}

void list_front_back(c_list * p)
{
    printf("\tlist front : %d\n", (int *)c_list_front(p) ? 
                                    *(int *)c_list_front(p) : 
                                    0);
    printf("\tlist back : %d\n", (int *)c_list_back(p) ?
                                    *(int *)c_list_back(p) :
                                    0);
}

void list_swap(c_list * p)
{
    c_list lt, lt1;
    __c_list(&lt, int_comparer);
    __c_list(&lt1, int_comparer);
    c_list_push_back(&lt, &array[3]);
    c_list_push_back(&lt, &array[5]);
    
    printf("\tlist A : \n");
    print_list(p);
    printf("\tlist B : \n");
    print_list(&lt);
    c_list_swap(p, &lt);
    printf("\tAfter swap\n");    
    printf("\tlist A : \n");
    print_list(p);
    printf("\tlist B : \n");
    print_list(&lt);
    
    printf("\t\t#########\t\t\n");
    printf("\tlist A : \n");
    print_list(p);
    printf("\tlist C : \n");
    print_list(&lt1);
    c_list_swap(p, &lt1);
    printf("\tAfter swap\n");
    printf("\tlist A : \n");
    print_list(p);
    printf("\tlist C : \n");
    print_list(&lt1);
    
    __c_tsil(&lt);
    __c_tsil(&lt1);
} 

void list_insert(c_list * p)
{
    c_list lt;
    c_iterator iter;
    __c_list(&lt, int_comparer);
    print_list(p);
    c_list_insert(p, c_list_end(p), &array[3]);
    print_list(p);
    c_list_insert(p, c_list_begin(p), &array[5]);
    print_list(p);
    iter = c_list_begin(p);
    ITER_INC(iter); //  insert between 5 and 3
    c_list_insert(p, iter, &array[1]);
    print_list(p);
    
    c_list_insert2(&lt, c_list_begin(&lt), c_list_begin(p), iter);
    print_list(&lt);
    c_list_clear(&lt);
    c_list_push_back(&lt, &array[0]);
    c_list_insert2(&lt, c_list_begin(&lt), c_list_begin(p), c_list_end(p));
    print_list(&lt);    
    __c_tsil(&lt);
}

void list_erase(c_list * p)
{
    c_iterator iter, iter2;
    create_with_push_back(p);
    print_list(p);
    c_list_erase(p, c_list_begin(p));
    print_list(p);
    iter = c_list_end(p);
    ITER_DEC(iter);
    c_list_erase(p, iter);
    print_list(p);
    iter = c_list_begin(p);
    iter2 = c_list_end(p);
    ITER_INC(iter);
    ITER_DEC(iter2);
    c_list_erase2(p, iter, iter2);
    print_list(p);
    c_list_erase2(p, c_list_begin(p), c_list_end(p));
    print_list(p);    
}

void list_splice(c_list * p)
{
    c_iterator iter;
    c_list lt;
    __c_list(&lt, int_comparer);
    
    create_with_push_back(p);
    c_list_splice(&lt, c_list_begin(&lt), p);
    print_list(&lt);
    print_list(p);
    
    create_with_push_back(p);
    c_list_splice(&lt, c_list_end(&lt), p);
    print_list(&lt);
    print_list(p);
    
    create_with_push_back(p);
    iter = c_list_begin(&lt);
    ITER_INC(iter);
    c_list_splice(&lt, iter, p);
    print_list(&lt);
    print_list(p);
       
    __c_tsil(&lt);
}

void list_splice1(c_list * p)
{
    c_list lt;
    c_iterator iter, iter2, iter3;
    
    __c_list(&lt, int_comparer);
    create_with_push_back(p);
    iter = c_list_begin(p);
    iter2 = c_list_begin(p);
    ITER_INC(iter2); ITER_INC(iter2);
    iter3 = c_list_end(p);
    ITER_DEC(iter3);
    
    
    c_list_splice1(&lt, c_list_begin(&lt), p, iter);
    print_list(&lt);
    print_list(p);
    
    c_list_splice1(&lt, c_list_end(&lt), p, iter2);
    print_list(&lt);
    print_list(p);
    
    
    iter = c_list_begin(&lt);
    ITER_INC(iter);
    c_list_splice1(&lt, iter, p, iter3);
    print_list(&lt);
    print_list(p);
    
    __c_tsil(&lt);
}

void list_splice2(c_list * p)
{
    c_list lt;
    c_iterator iter, iter2, iter3;
    
    __c_list(&lt, int_comparer);
    create_with_push_back(p);
    iter = c_list_begin(p);
    iter2 = c_list_begin(p);
    ITER_INC(iter2);ITER_INC(iter2);ITER_INC(iter2);ITER_INC(iter2);
    c_list_splice2(&lt, c_list_begin(&lt), p, iter, iter2);
    print_list(&lt);
    print_list(p);
    
    c_list_splice2(&lt, c_list_end(&lt), p, c_list_begin(p), c_list_end(p));
    print_list(&lt);
    print_list(p);
    
    create_with_push_back(p);
    iter = c_list_end(p);
    ITER_DEC(iter);ITER_DEC(iter);ITER_DEC(iter);ITER_DEC(iter);
    c_list_splice2(&lt, c_list_begin(&lt), p, iter, c_list_end(p));
    print_list(&lt);
    print_list(p);
    
    c_list_splice2(&lt, c_list_end(&lt), p, c_list_begin(p), c_list_end(p));
    print_list(&lt);
    print_list(p);
    
    create_with_push_back(p);
    iter = c_list_begin(p);
    iter2 = c_list_end(p);
    iter3 = c_list_begin(&lt);
    ITER_INC(iter); 
    ITER_DEC(iter2); ITER_DEC(iter2); ITER_DEC(iter2);
    ITER_INC(iter3);
    c_list_splice2(&lt, iter3, p, iter, iter2);
    print_list(&lt);
    print_list(p);
        
    
    __c_tsil(&lt);
}


void list_remove(c_list * p)
{
    create_with_push_back(p);
    print_list(p);
    
    c_list_remove(p, &array[0]);
    print_list(p);
    
    c_list_remove(p, &array[3]);
    print_list(p);
    
    c_list_remove(p, &array[5]);
    print_list(p);
    
    
    create_with_push_back(p);
    create_with_push_back(p);
    
    c_list_remove(p, &array[4]);
    print_list(p);
    
}

void list_unique(c_list * p)
{
    int ary[] = { 0,0,1,1,1,3,3,3,2,2,2 };
    c_list lt;
    int i;
    __c_list(&lt, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    
    print_list(&lt);
    c_list_unique(&lt);
    print_list(&lt);
    __c_tsil(&lt);
}

void list_merge()
{
    int ary[] = { 1,2,7,2,8,9,2,5,8,36,0,2,12,0,2 };
    int ary2[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    c_list lt, lt2;
    int i;
    __c_list(&lt, int_comparer);
    __c_list(&lt2, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    for(i = 0; i < (sizeof(ary2) /sizeof(int)); ++ i)
    {
        c_list_push_back(&lt2, &ary2[i]);
    }
    
    print_list(&lt);
    print_list(&lt2);
    printf("after merge\n");
    c_list_merge(&lt, &lt2);
    print_list(&lt);
    print_list(&lt2);
    
    __c_tsil(&lt);
    __c_tsil(&lt2);
}

void list_sort()
{
    int ary[] = { 1,2,7,2,8,9,2,5,8,36,0,2,12,0,2 };
    int ary2[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    c_list lt, lt2;
    int i;
    __c_list(&lt, int_comparer);
    __c_list(&lt2, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    for(i = 0; i < (sizeof(ary2) /sizeof(int)); ++ i)
    {
        c_list_push_back(&lt2, &ary2[i]);
    }
    
    print_list(&lt);
    print_list(&lt2);
    printf("after sort\n");
    c_list_sort(&lt);
    c_list_sort(&lt2);
    print_list(&lt);
    print_list(&lt2);
    
    __c_tsil(&lt);
    __c_tsil(&lt2);    
}

void list_equal()
{
    int ary[] = { 1,2,7,2,8,9,2,5,8,36,0,2,12,0,2 };
    int ary2[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    int ary3[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    c_list lt, lt2, lt3;
    int i;
    __c_list(&lt, int_comparer);
    __c_list(&lt2, int_comparer);
    __c_list(&lt3, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    for(i = 0; i < (sizeof(ary2) /sizeof(int)); ++ i)
    {
        c_list_push_back(&lt2, &ary2[i]);
    }
    for(i = 0; i < (sizeof(ary3) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt3, &ary3[i]);
    }
    
    print_list(&lt);
    print_list(&lt2);
    print_list(&lt3);
    
    if(c_list_equal(&lt, &lt2))
        printf("lt == lt2\n");
    else 
        printf("lt != lt2\n");
        
    if(c_list_equal(&lt2, &lt3))
        printf("lt2 == lt3\n");
    else
        printf("lt2 != lt3\n");
    
    __c_tsil(&lt);
    __c_tsil(&lt2);    
    __c_tsil(&lt3);
}

void list_less()
{
    int ary[] = { 2,89,7,2,8,9,2,5,8,36,0,2,12,0,2 };
    int ary2[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    int ary3[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9,3 };
    c_list lt, lt2, lt3;
    int i;
    __c_list(&lt, int_comparer);
    __c_list(&lt2, int_comparer);
    __c_list(&lt3, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    for(i = 0; i < (sizeof(ary2) /sizeof(int)); ++ i)
    {
        c_list_push_back(&lt2, &ary2[i]);
    }
    for(i = 0; i < (sizeof(ary3) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt3, &ary3[i]);
    }
    
    print_list(&lt);
    print_list(&lt2);
    print_list(&lt3);
    
    if(c_list_less(&lt, &lt2))
        printf("lt < lt2\n");
    else 
        printf("lt >= lt2\n");
        
    if(c_list_less(&lt2, &lt3))
        printf("lt2 < lt3\n");
    else
        printf("lt2 >= lt3\n");
    
    __c_tsil(&lt);
    __c_tsil(&lt2);    
    __c_tsil(&lt3);
}

void list_copy()
{
    int ary[] = { 0,0,0,0,0,0 };
    int ary2[] = { 2,87,1,9,2,5,0,54,1,7,23,0,43,2,9 };
    c_list lt, lt2;
    int i;
    __c_list(&lt, int_comparer);
    __c_list(&lt2, int_comparer);
    for(i = 0; i < (sizeof(ary) / sizeof(int)); ++ i)
    {
        c_list_push_back(&lt, &ary[i]);
    }
    for(i = 0; i < (sizeof(ary2) /sizeof(int)); ++ i)
    {
        c_list_push_back(&lt2, &ary2[i]);
    }
    
    print_list(&lt);
    print_list(&lt2);
    
    c_copy(c_list_begin(&lt), c_list_end(&lt), c_list_begin(&lt2));
    printf("after copy \n");
    print_list(&lt);
    print_list(&lt2);
    
    c_copy_backward(c_list_begin(&lt), c_list_end(&lt), c_list_end(&lt2));
    printf("after copy backward\n");
    print_list(&lt);
    print_list(&lt2);
        
    __c_tsil(&lt);
    __c_tsil(&lt2);
}

int t_list()
{
    c_list lt;
    
    
    __c_list(&lt, int_comparer);
    
    
    
    printf("\n\n##\t1.\ttest creating list with push_back\n");
    create_with_push_back(&lt);
    print_list(&lt);
    reverse_print_list(&lt);
    c_list_clear(&lt);
    printf("after clear :\n"); 
    print_list(&lt);
    
    
    printf("\n\n##\t2.\ttest creating list with push_front\n");
    create_with_push_front(&lt);
    print_list(&lt);
    reverse_print_list(&lt);
    c_list_clear(&lt);


    printf("\n\n##3.\ttest list size\n");
    list_size(&lt);
    c_list_clear(&lt);
    
    printf("\n\n##4.\ttest list assign\n");
    list_assign(&lt);
    create_with_push_back(&lt);
    list_assign(&lt);
    c_list_clear(&lt);
    

    printf("\n\n##5.\ttest list front back\n");
    list_front_back(&lt);
    c_list_push_back(&lt, &array[1]);
    list_front_back(&lt);
    c_list_push_back(&lt, &array[3]);
    list_front_back(&lt);
    c_list_push_back(&lt, &array[5]);
    list_front_back(&lt);
    c_list_clear(&lt);
    
    printf("\n\n##6.\ttest list pop front back\n");
    create_with_push_back(&lt);
    list_front_back(&lt);
    printf("\tlist size : %d\n", c_list_size(&lt));
    c_list_pop_front(&lt);
    list_front_back(&lt);
    c_list_pop_back(&lt);
    list_front_back(&lt);
    printf("\tlist size : %d\n", c_list_size(&lt));
    c_list_pop_front(&lt);
    list_front_back(&lt);
    c_list_pop_back(&lt);
    list_front_back(&lt);
    printf("\tlist size : %d\n", c_list_size(&lt));
    c_list_pop_front(&lt);
    list_front_back(&lt);
    c_list_pop_back(&lt);
    list_front_back(&lt);
    printf("\tlist size : %d\n", c_list_size(&lt));
    c_list_pop_front(&lt);
    list_front_back(&lt);  
    c_list_pop_back(&lt);
    list_front_back(&lt);
    printf("\tlist size : %d\n", c_list_size(&lt));
    c_list_clear(&lt);
    
    printf("\n\n##7.\ttest list swap\n");
    create_with_push_back(&lt); 
    list_swap(&lt);
    c_list_clear(&lt); 
    
    printf("\n\n##8.\ttest list insert\n");
    list_insert(&lt);
    c_list_clear(&lt);
    
    printf("\n\n##9.\ttest list erase\n");
    list_erase(&lt); 
    c_list_clear(&lt);
    
    printf("\n\n##10.\ttest list splice\n");
    list_splice(&lt);
    c_list_clear(&lt);
    
    printf("\n\n##11.\ttest list splice1\n");
    list_splice1(&lt);
    c_list_clear(&lt);
    
    printf("\n\n12.\ttest list splice2\n");
    list_splice2(&lt);
    c_list_clear(&lt);
    
    printf("\n\n13.\ttest list remove\n");
    list_remove(&lt);
    c_list_clear(&lt);
    
    printf("\n\n14.\ttest list unique\n");
    list_unique(&lt);
    c_list_clear(&lt);
    
    printf("\n\n15.\ttest list merge\n");
    list_merge();
    
    printf("\n\n16.\ttest list sort\n");
    list_sort();
    
    printf("\n\n17.\ttest list equal\n");
    list_equal();
    
    printf("\n\n18.\ttest list less\n");
    list_less();
    
    printf("\n\n19.\ttest list copy\n");
    list_copy();
    
    __c_tsil(&lt); 
    printf("\n\nfinish testing list!\n");
    return 0;
}
