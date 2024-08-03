#include "nm.h"

t_list *init_list(t_list *list)
{
	list = malloc(sizeof(t_list));
	if (!list)
	{
		perror("malloc");
		exit (0);
	}
	list->addr = 0;
	list->type = 0;
	list->symbol = NULL;
	list->next = NULL;
	return (list);
}


void is_64(t_data *data)
{
	t_list *list = NULL;

	list = init_list(list);
	printf("%s:     file format elf64-x86-64\n", data->filename);
	free(list);

}