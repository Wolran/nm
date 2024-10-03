#include "nm.h"

unsigned char char_Special_Symbol(const char *name, char ch, unsigned int local)
{
	char c = 0;

	if (!ft_strncmp(name, ".symtab", ft_strlen(".symtab")) || 
		!ft_strncmp(name, ".shstrtab", ft_strlen(".shstrtab")) ||
		!ft_strncmp(name, ".strtab", ft_strlen(".strtab")))
		return 'a';

	else if (!ft_strncmp(name, ".comment", ft_strlen(".comment")) || 
		!ft_strncmp(name, ".ident", ft_strlen(".ident")) ||
		!ft_strncmp(name, ".gnu_debug", ft_strlen(".gnu_debug")) ||
		!ft_strncmp(name, ".copyright", ft_strlen(".copyright")) ||
		!ft_strncmp(name, ".SUNW", ft_strlen(".SUNW")))
		return 'n';

	else if (!ft_strncmp(name, ".debug_", ft_strlen(".debug_")))
		return 'N';

	else if (!ft_strncmp(name, ".gnu.hash", ft_strlen(".gnu.hash")) ||
		!ft_strncmp(name, ".SUNW_version", ft_strlen(".SUNW_version")) ||
		!ft_strncmp(name, ".rela.plt", ft_strlen(".rela.plt")) ||
		!ft_strncmp(name, ".rel.plt", ft_strlen(".rel.plt")) ||
		!ft_strncmp(name, ".dynstr", ft_strlen(".dynstr")) ||
		!ft_strncmp(name, ".gnu.version_r", ft_strlen(".gnu.version_r")) ||
		!ft_strncmp(name, ".rela.got", ft_strlen(".rela.got")) ||
		!ft_strncmp(name, ".rodata", ft_strlen(".rodata")) ||
		!ft_strncmp(name, ".rela.bss", ft_strlen(".rela.bss")))
	{
		c = 'R';
		if (local == STB_LOCAL)
			c = 'r';
		return c;
	}
	return ch;
}

char char_Symbol_64(t_data *data, t_sym *symbol)
{
	unsigned int c, bind, type;
	uint64_t sh_flags;
	uint32_t sh_type;
	uint16_t st_shndx;
	uint16_t e_shnum;

	c = '?';
	bind = ELF64_ST_BIND(symbol->sym_64->st_info);
	type = ELF64_ST_TYPE(symbol->sym_64->st_info);
	st_shndx = symbol->sym_64->st_shndx;
	e_shnum = data->header_64->e_shnum;

	if (bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (bind == STB_WEAK && type == STT_OBJECT) 
	{
		c = 'V';
		if (st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (bind == STB_WEAK)
	{
		c = 'W';
		if (st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (st_shndx == SHN_UNDEF)
		c = 'U';
	else if (st_shndx == SHN_COMMON)
		c = 'C';
	else if (st_shndx == SHN_ABS)
		c = 'A';
	else if (st_shndx < e_shnum)
	{
		sh_type = data->section_64[st_shndx].sh_type;
		sh_flags = data->section_64[st_shndx].sh_flags;
		if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
			c = 'D';
		else if (sh_type == SHT_NOBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
			c = 'B';
		else if ((sh_type == SHT_PROGBITS && (sh_flags == (SHF_ALLOC | SHF_EXECINSTR) || 
				sh_flags == (SHF_EXECINSTR | SHF_ALLOC | SHF_WRITE))) || sh_type == SHT_MIPS_SYMBOL_LIB)
			c = 'T';
		else if (sh_type == SHT_GROUP)
			c = 'N';
		else if (sh_type == SHT_DYNAMIC || sh_type == SHT_FINI_ARRAY || sh_type == SHT_INIT_ARRAY)
			c = 'D';
		else if (((sh_type == SHT_PROGBITS || sh_type == SHT_RELA ||
		    sh_type == SHT_REL || sh_type == SHT_HASH ||
		    sh_type == SHT_GNU_versym || sh_type == SHT_GNU_verdef ||
		    sh_type == SHT_DYNSYM || sh_type == SHT_STRTAB ||
		    sh_type == SHT_NOTE) && sh_flags == SHF_ALLOC) || sh_flags == 18)
		c = 'R';
		else
			c = 'T';
	}
	if (c != '?' && bind == STB_LOCAL)
		c ^= 0x20u;
	c = char_Special_Symbol(symbol->name, c, bind);
	return (c);
}


char char_Symbol_32(t_data *data, t_sym *symbol)
{
	unsigned int c, bind, type;
	uint32_t sh_flags;
	uint32_t sh_type;
	uint16_t st_shndx;
	uint16_t e_shnum;

	c = '?';
	bind = ELF32_ST_BIND(symbol->sym_32->st_info);
	type = ELF32_ST_TYPE(symbol->sym_32->st_info);
	st_shndx = symbol->sym_32->st_shndx;
	e_shnum = data->header_32->e_shnum;

	if (bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (bind == STB_WEAK && type == STT_OBJECT) 
	{
		c = 'V';
		if (st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (bind == STB_WEAK)
	{
		c = 'W';
		if (st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (st_shndx == SHN_UNDEF)
		c = 'U';
	else if (st_shndx == SHN_COMMON)
		c = 'C';
	else if (st_shndx == SHN_ABS)
		c = 'A';
	else if (st_shndx < e_shnum)
	{
		sh_type = data->section_32[st_shndx].sh_type;
		sh_flags = data->section_32[st_shndx].sh_flags;
		if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
			c = 'D';
		else if (sh_type == SHT_NOBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
			c = 'B';
		else if ((sh_type == SHT_PROGBITS && (sh_flags == (SHF_ALLOC | SHF_EXECINSTR) || 
				sh_flags == (SHF_EXECINSTR | SHF_ALLOC | SHF_WRITE))) || sh_type == SHT_MIPS_SYMBOL_LIB)
			c = 'T';
		else if (sh_type == SHT_GROUP)
			c = 'N';
		else if (sh_type == SHT_DYNAMIC || sh_type == SHT_FINI_ARRAY || sh_type == SHT_INIT_ARRAY)
			c = 'D';
		else if (((sh_type == SHT_PROGBITS || sh_type == SHT_RELA ||
		    sh_type == SHT_REL || sh_type == SHT_HASH ||
		    sh_type == SHT_GNU_versym || sh_type == SHT_GNU_verdef ||
		    sh_type == SHT_DYNSYM || sh_type == SHT_STRTAB ||
		    sh_type == SHT_NOTE) && sh_flags == SHF_ALLOC) || sh_flags == 18)
		c = 'R';
		else
			c = 'T';
	}
	if (c != '?' && bind == STB_LOCAL)
		c ^= 0x20u;
	c = char_Special_Symbol(symbol->name, c, bind);
	return (c);
}