#include "nm.h"

static void	_print_data(t_data *data) 
{
	t_list *sym = data->sym;
	while (sym)
	{
		t_sym *symbol = sym->data;
		if (symbol->sym_64->st_shndx == 0)
			ft_printf("%16c %c %s\n", ' ', symbol->symbol, symbol->name);
		else
			ft_printf("%016lx %c %s\n", symbol->sym_64->st_value, symbol->symbol, symbol->name);
		sym = sym->next;
	}
}

static inline int __is_skiping(Elf64_Sym *sym)
{
	if ((ELF64_ST_TYPE(sym->st_info) != STT_SECTION && !(sym->st_shndx == SHN_LOPROC || 
		sym->st_shndx == SHN_HIPROC || sym->st_shndx == SHN_LOOS   || sym->st_shndx == SHN_ABS || 
		sym->st_shndx == SHN_AFTER  || sym->st_shndx == SHN_COMMON || sym->st_shndx == SHN_BEFORE ||
		sym->st_shndx == SHN_XINDEX || sym->st_shndx == SHN_HIOS   || sym->st_shndx == SHN_HIRESERVE)) ||
		(ELF64_ST_BIND(sym->st_info) == STB_GLOBAL))
			return 0;
	return 1;
}

int	print_data_64(t_data *data)
{
	Elf64_Ehdr *header = data->data;
	data->header_64 = header;
	if (header->e_shoff > (size_t)data->stat.st_size)
		return printf("'%s': error e_shoff bigger than file size\n", data->file_name), 1;

	Elf64_Shdr *sections = data->data + header->e_shoff;
	data->section_64 = sections;
	if (sections->sh_size != 0 && sections->sh_offset != 0)
		return printf("'%s': error bad section\n", data->file_name), 1;

	if (header->e_shstrndx >= header->e_shnum || sections[header->e_shstrndx].sh_type != SHT_STRTAB)
		return printf("'%s': error bad section header\n", data->file_name), 1;

	Elf64_Shdr *section_str = NULL;
	Elf64_Shdr *section_sym = NULL;
	for (int i = 0; i < header->e_shnum; ++i) {
		if (sections[i].sh_name > sections[header->e_shstrndx].sh_size)
			return printf("'%s': error bad section header at %d\n", data->file_name, i), 1;
		if (sections[i].sh_type == SHT_SYMTAB) {
			section_sym = &sections[i];
			section_str = &sections[sections[i].sh_link];
			break;
	  }
	}
	if (section_sym == NULL || section_str == NULL)
		return printf("'%s': no symbol table found\n", data->file_name), 1;

	Elf64_Sym *symbol_table = data->data + section_sym->sh_offset;
	for (int i = 1; i < ft_ceil((double)section_sym->sh_size / (double)sizeof(Elf64_Sym)); ++i)
	{
		uint16_t st_shndx = symbol_table[i].st_shndx;
		Elf64_Sym *sym = &symbol_table[i];
		if (__is_skiping(sym))
			continue;
		t_sym *symbol = malloc(sizeof(t_sym));
		if (!symbol)
			return printf("memory allocation failed\n"), 1;
		ft_bzero(symbol, sizeof(t_sym));
		symbol->sym_64 = sym;
		symbol->name = data->data + section_str->sh_offset + sym->st_name;
		symbol->index = st_shndx;
		if (sym->st_shndx < header->e_shnum)
			if (ELF64_ST_TYPE(sym->st_info) == STT_SECTION)
				symbol->name = (data->data + sections[header->e_shstrndx].sh_offset) + sections[sym->st_shndx].sh_name;
		symbol->symbol = char_Symbol_64(data, symbol);
		t_list *new = ft_lstnew(symbol);
		if (!new)
			return printf("memory allocation failed\n"), 1;
		ft_lstadd_back(&data->sym, new);
	}

	//nm sort alphanumerically but remove '_'
	ft_lstsort(&data->sym, &comp_Val);
	ft_lstsort(&data->sym, &comp_Sym);
	_print_data(data);
	return 0;
}
