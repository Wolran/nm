#ifndef NM_H
#define NM_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "ft_printf.h"

// DEFINES

typedef struct	s_list	t_list;
typedef struct	s_data	t_data;
typedef struct	s_sym	t_sym;


// PROTOTYPES

int			print_data_64(t_data *data);
int			print_data_32(t_data *data);
char		char_Symbol_64(t_data *data, t_sym *symbol);
char		char_Symbol_32(t_data *data, t_sym *symbol);
int			comp_Val(void *a, void *b);
int			comp_Sym(void *a, void *b);
unsigned	char char_Special_Symbol(const char *name, char ch, unsigned int local);

void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstsort(t_list **lst, int (*cmp)(void *, void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstat(t_list *begin_list, unsigned int nbr);
int			ft_lstsize(t_list *lst);
void		ft_bzero(void *s, size_t n);
int			ft_ceil(double n);
void		free_data(t_data *data);


// STRUCTS

struct s_data
{
	void			*data;
	size_t			data_size;
	const char		*file_name;
	Elf64_Ehdr		*header_64;
	Elf64_Shdr		*section_64;
	Elf32_Ehdr		*header_32;
	Elf32_Shdr		*section_32;
	int				fd;
	int				elf;
	struct stat 	stat;
	t_list			*sym;
};

struct s_sym
{
	Elf64_Sym		*sym_64;
	Elf32_Sym		*sym_32;
	char			*name;
	uint16_t		index;
	char			symbol;
};

struct s_list
{
	void			*data;
	struct s_list	*next;
};

#endif