#include <stdlib.h>
#include <stdio.h>
#include "t_test.h"

int t_list();
int t_vector();
int t_tree();
int t_map();
int t_set();
int t_stack();
int t_queue();
int t_algo();

int main()
{
	
	t_list();
	t_vector();
	t_tree();
	t_map();
	t_set();
	t_stack();
	t_queue();
	t_algo();
	
#ifdef WIN32
	system("pause");
#endif	
	return 0;
}
