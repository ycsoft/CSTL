#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/c_vector.h"
#include "../include/c_algorithm.h"
#include "t_test.h"


static int array[] = { 0,1,2,3,4,5,6,7,8,9,10 };



static inline int int_comparer(void * x, void * y)
{
    return *(int *)(x) - *(int *)(y);
}

static void print_vector2(c_iterator first, c_iterator last)
{
    c_iterator iter;
    printf("vector is :\n"); 
    for(iter = first;
          !ITER_EQUAL(iter, last); ITER_INC(iter))
    {
        if(ITER_REF(iter))
            printf("\t%d\n", *((int *)(ITER_REF(iter))));
    }
} 

static void print_vector2_r(c_reverse_iterator first, c_reverse_iterator last)
{
    c_reverse_iterator iter;
    printf("vector is :\n");
    for(iter = first; 
            !ITER_EQUAL(iter, last); ITER_INC(iter))
    {
        printf("\t%d\n", *((int *)(ITER_REF(iter))));
    }
}

static void print_vector(c_vector * p)
{
    c_iterator first, last;
    first = c_vector_begin(p);
    last = c_vector_end(p);
    print_vector2(first, last);
}

static void reverse_print_vector(c_vector * p)
{
    c_reverse_iterator first, last;
    first = c_vector_rbegin(p);
    last = c_vector_rend(p);
    print_vector2_r(first, last);
} 

static void create_with_push_back(c_vector * p)
{
    int i = 0;
    for (; i < sizeof(array) / sizeof(int); ++ i)
    {
        c_vector_push_back(p, &array[i]);
    }
}

static void clear_vector(c_vector * p)
{
    c_vector_clear(p);
}

static void erase_vector()
{
    c_vector vt;
    c_vector * p = &vt;
    c_iterator i1, i3, i4, i6, i10;
    
    __c_vector(&vt, int_comparer);
    
    create_with_push_back(&vt);
    i1 = c_vector_begin(p);
    print_vector(p);
    
    printf("erase last :\n");
    i10 = ITER_POSITIVE_N(i1, 10);
    c_vector_erase(p, i10);
    print_vector(p);
    
    printf("erase middle 1 : \n");
    i4 = ITER_POSITIVE_N(i1, 4);
    c_vector_erase(p, i4);
    print_vector(p);
    
    printf("erase middle n : \n");
    i3 = ITER_POSITIVE_N(i1, 3);
    i6 = ITER_POSITIVE_N(i1, 6);
    c_vector_erase2(p, i3, i6);
    print_vector(p);
    
    printf("erase first :\n");
    c_vector_erase(p, i1);
    print_vector(p);   
    
    printf("erase all :\n");
    c_vector_erase2(p, c_vector_begin(p), c_vector_end(p));
    print_vector(p); 
    
    __c_rotcev(&vt);
}


static void vector_assign(c_vector * p)
{
    c_vector new_vt;
    __c_vector(&new_vt, int_comparer);
    
    c_vector_assign(&new_vt, p);
    
    printf("new vector :\n");
    print_vector(&new_vt);
    __c_rotcev(&new_vt);    
}

static void vector_reserve(c_vector * p)
{
    c_vector newvt;
    __c_vector(&newvt, int_comparer);

    printf("capacity original : %d\n", c_vector_capacity(p));
    c_vector_reserve(p, c_vector_capacity(p) + 5);
    printf("new capacity : %d\n", c_vector_capacity(p));
    
    printf("\nempty capacity : %d\n", c_vector_capacity(&newvt));
    c_vector_reserve(&newvt, c_vector_capacity(&newvt) + 5);
    printf("new capacity : %d\n", c_vector_capacity(&newvt));
       
    __c_rotcev(&newvt);
}

static void vector_front_back(c_vector * p)
{
    printf("front of vector : %d\n", *(int*)c_vector_front(p)); 
    printf("back of vector : %d\n", *(int*)c_vector_back(p));  
}

static void vector_swap(c_vector * p)
{
    c_vector lvt;
    __c_vector(&lvt, int_comparer);
    c_vector_push_back(&lvt, &array[3]);
    
    c_vector_swap(p, &lvt);
    printf("local vector is : \n");
    print_vector(&lvt);
    printf("outside vector is : \n");
    print_vector(p);
    __c_rotcev(&lvt);    
}

static void vector_insert(c_vector * p)
{
    c_iterator iter;
    c_vector_insert(p, c_vector_end(p), &array[0]);
    c_vector_insert(p, c_vector_begin(p), &array[2]);
    c_vector_insert(p, c_vector_end(p), &array[4]);
    c_vector_insert(p, c_vector_end(p), &array[6]);
    c_vector_insert(p, c_vector_begin(p), &array[8]);
    
    iter = c_vector_begin(p);
    iter = ITER_POSITIVE_N(iter, 3);
    c_vector_insert(p, iter, &array[5]);   
    
    printf("vector after insertion\n");
    print_vector(p);
}

static void vector_insert2(c_vector * p)
{
    c_vector vt;
    __c_vector(&vt, int_comparer);
    
    c_vector_insert2(&vt, 
                    c_vector_begin(&vt), 
                    c_vector_begin(p),
                    c_vector_end(p));
    printf("after insert2\n");
    print_vector(&vt);
    __c_rotcev(&vt);    
}

static void vector_fill_insert(c_vector * p)
{
    c_iterator iter = c_vector_begin(p);
    
    c_vector_fill_insert(p, ITER_INC(iter), 10, &array[8]);
    printf("after fill insert middle\n");
    print_vector(p);    
    
    c_vector_fill_insert(p, c_vector_begin(p), 10, &array[6]);
    printf("after fill insert begin\n");
    print_vector(p);    
    
    c_vector_fill_insert(p, c_vector_end(p), 10, &array[4]);
    printf("after fill insert end\n");
    print_vector(p);
    
}

static void vector_resize(c_vector * p)
{
    print_vector(p);
    printf("vector size : %d\n", c_vector_size(p));
    c_vector_resize(p, 100);
    print_vector(p);
    printf("vector size : %d\n", c_vector_size(p));
    c_vector_resize(p, 0);
    print_vector(p);
    printf("vector size : %d\n", c_vector_size(p));
    create_with_push_back(p);
    c_vector_resize(p, 3);
    print_vector(p);
    printf("vector size : %d\n", c_vector_size(p));    
}

static void vector_equal(c_vector * p)
{
    c_iterator iter;
    int * old;
    c_vector vt;
    __c_vector(&vt, int_comparer);
    
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_equal(&vt, p) ? "IS equal\n" : "NOT equal\n");
    
    create_with_push_back(&vt);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_equal(&vt, p) ? "IS equal\n" : "NOT equal\n");
    
    iter = c_vector_begin(&vt);
    old = (int*)ITER_REF(iter); 
    ITER_REF_ASSIGN(iter, &array[5]);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_equal(&vt, p) ? "IS equal\n" : "NOT equal\n");       
    ITER_REF_ASSIGN(iter, old);
    
    c_vector_clear(&vt);
    c_vector_clear(p);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_equal(&vt, p) ? "IS equal\n" : "NOT equal\n");
    __c_rotcev(&vt);
}

static void vector_less(c_vector * p)
{
    c_iterator iter;
    int * old;
    c_vector vt;
    __c_vector(&vt, int_comparer);
    
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_less(&vt, p) ? "IS less\n" : "NOT less\n");
    
    create_with_push_back(&vt);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_less(&vt, p) ? "IS less\n" : "NOT less\n");
    
    iter = c_vector_begin(&vt);
    old = (int*)ITER_REF(iter);
    ITER_REF_ASSIGN(iter, &array[5]);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_less(&vt, p) ? "IS less\n" : "NOT less\n");
    ITER_REF_ASSIGN(iter, old);
    
    ITER_INC_N(iter, 3);
    old = (int*)ITER_REF(iter);
    ITER_REF_ASSIGN(iter, &array[0]);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_less(&vt, p) ? "IS less\n" : "NOT less\n");
        
    c_vector_clear(&vt);
    c_vector_clear(p);
    print_vector(&vt);
    print_vector(p);
    printf(c_vector_less(&vt, p) ? "IS less\n" : "NOT less\n");
    __c_rotcev(&vt);
}


int t_vector()
{
    c_vector vt;
    __c_vector(&vt, int_comparer);
    

    printf("1.test create vector\n");
    create_with_push_back(&vt);
    print_vector(&vt);
    reverse_print_vector(&vt);
    clear_vector(&vt);
    
    printf("\n\n2.test vector assign\n");
    create_with_push_back(&vt);    
    vector_assign(&vt);
    clear_vector(&vt);
    
    printf("\n\n3.test erase vector\n");
    erase_vector();
    
    printf("\n\n4.test reserve vector\n");
    create_with_push_back(&vt);
    vector_reserve(&vt);
    clear_vector(&vt);
    
    printf("\n\n5.test front back\n");
    create_with_push_back(&vt);
    vector_front_back(&vt);
    clear_vector(&vt);

    printf("\n\n6.test swap\n");
    create_with_push_back(&vt);
    vector_swap(&vt);
    clear_vector(&vt);

    printf("\n\n7.test insert\n");
    vector_insert(&vt);
    clear_vector(&vt);    
    
    printf("\n\n8.test insert2\n");
    create_with_push_back(&vt);
    vector_insert2(&vt);
    clear_vector(&vt);
    
    printf("\n\n9.test fill insert\n");
    create_with_push_back(&vt);
    vector_fill_insert(&vt);
    clear_vector(&vt);
    
    printf("\n\n10.test resize\n");
    create_with_push_back(&vt);
    vector_resize(&vt);
    clear_vector(&vt);
        
    printf("\n\n11.test equal\n");
    create_with_push_back(&vt);
    vector_equal(&vt);
    clear_vector(&vt);
    
    printf("\n\n12.test less\n");
    create_with_push_back(&vt);
    vector_less(&vt);
    clear_vector(&vt);        
    
    __c_rotcev(&vt);
    printf("\n\nfinish testing vector!\n");
    return 0;
}

