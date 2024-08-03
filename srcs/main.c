#include "nm.h"


void is_32_64(t_data *data)
{
	if (data->header->e_ident[EI_CLASS] == ELFCLASS32)
		is_32(data);
	else if (data->header->e_ident[EI_CLASS] == ELFCLASS64)
		is_64(data);
	else
		printf("ft_nm: %s: File format not recognized\n", data->filename);
}

void ft_nm(char *filename)
{
	t_data data;

	data.filename = filename;
	data.fd = open(filename, O_RDONLY);
	if (data.fd < 0 || fstat(data.fd, &data.buf) < 0)
	{
		printf("ft_nm: '%s': No such file\n", filename);
		exit (0);
	}
	if (S_ISDIR(data.buf.st_mode))
	{
		printf("ft_nm: %s: Is a directory\n", filename);
		exit (0);
	}
	data.header = mmap(NULL, sizeof(Elf64_Ehdr), PROT_READ, MAP_PRIVATE, data.fd, 0);
	if (data.header == MAP_FAILED)
	{
		printf("ft_nm: '%s': No such file\n", filename);
		exit (0);
	}
	if (data.header->e_ident[EI_MAG0] != ELFMAG0 || data.header->e_ident[EI_MAG1] != ELFMAG1 \
		|| data.header->e_ident[EI_MAG2] != ELFMAG2 || data.header->e_ident[EI_MAG3] != ELFMAG3)
	{
		printf("ft_nm: %s: File format not recognized\n", filename);
		exit (0);
	}
	is_32_64(&data);
}

int main(int arc, char **arv)
{
	if (arc == 1)
		ft_nm("a.out");
	else
		for (int i = 1; i < arc; i++)
			ft_nm(arv[i]);
	return (0);
}