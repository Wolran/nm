# ifndef NM_H
# define NM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_data t_data;
typedef struct s_list t_list;

void is_64(t_data *data);
void is_32(t_data *data);

struct s_data
{
	char *filename;
	int fd;
	Elf64_Ehdr *header;
	Elf64_Shdr *section;
	struct stat buf;
};

struct s_list
{
	unsigned int addr;
	char type;
	char *symbol;
	t_list *next;
};


#endif