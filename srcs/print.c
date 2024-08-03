#include "nm.h"

void print_list(t_list *list)
{
	//need to print the list if 64 need add 0 
	while (list)
	{
		printf("%s\n", list->symbol);
		list = list->next;
	}
}