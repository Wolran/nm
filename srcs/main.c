#include "nm.h"

static int	_pars_arv(t_list **lists, int argc, char **argv)
{
	if (argc == 1) {
	t_list *new = ft_lstnew("a.out");
	if (!new)
	  return ft_printf("memory allocation failed\n"), 1;
	*lists = new;
	}
	else {
		for (int i = 1; i < argc; ++i) {
			t_list *new = ft_lstnew(argv[i]);
			if (!new)
				return ft_printf("memory allocation failed\n"), 1;
			ft_lstadd_back(lists, new);
		}
	}
	return 0;
}

static int	_init_data(t_data *data, int arc)
{
	int fd = open(data->file_name, O_RDONLY);
	if (fd == -1)
		return ft_printf("open: '%s': can't open file\n", data->file_name), 1;
	if (fstat(fd, &data->stat) == -1)
		return ft_printf("fstat: '%s': can't stat file\n", data->file_name), 1;
	if (S_ISDIR(data->stat.st_mode))
		return ft_printf("fstat: '%s': is a directory\n", data->file_name), 1;
	if (data->stat.st_size < (off_t)sizeof(Elf32_Ehdr))
		return ft_printf("'%s': file too small to be ELF", data->file_name), 1;
	data->printing = 0;
	if (arc > 2)
		data->printing = 1;
	data->fd = fd;
	data->data = mmap(NULL, data->stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (!data->data || data->data == MAP_FAILED)
		return ft_printf("mmap: '%s': can't map file\n", data->file_name), 1;

	Elf64_Ehdr* header = (Elf64_Ehdr*)data->data;
	char str[4] = {header->e_ident[0], header->e_ident[1], header->e_ident[2], header->e_ident[3]};
	if (strncmp(str, ELFMAG, SELFMAG) != 0)
		return ft_printf("'%s': invalid ELF file\n", data->file_name), 1;

	if (header->e_ident[EI_CLASS] == ELFCLASS32) 
		data->elf = 32;
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		data->elf = 64;
	else 
		return ft_printf("'%s': invalid ELF class\n", data->file_name), 1;
	return 0;
}

int main(int arc, char **arv)
{
	t_list *lists = NULL;
	if (_pars_arv(&lists, arc, arv) != 0)
		return EXIT_FAILURE;

	t_data data;
	for (int i = 0; i < ft_lstsize(lists); i++)
	{
		ft_bzero(&data, sizeof(t_data));
		data.file_name = ft_lstat(lists, i)->data;
		if (_init_data(&data, arc) != 0)
		{
			free_data(&data);
			continue;
		}
		if (data.elf == 64){
			if (print_data_64(&data) != 0)
			{
				free_data(&data);
				continue;
			}
		}
		else if (data.elf == 32)
		{
			if (print_data_32(&data) != 0)
			{
				free_data(&data);
				continue;
			}
		}
		free_data(&data);
	}
	ft_lstclear(&lists , NULL);
	return 0;
}


//!TODO: change ft_printf, strncmp, strlen
//!TODO: S_ISDIR ? bonus ?