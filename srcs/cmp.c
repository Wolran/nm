#include "nm.h"

static int	_ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static int	_ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c ^= 0x20u);
	return (c);
}

int comp_Val(void *a, void *b)
{
	t_sym *first_sym = a;
	t_sym *sec_sym = b;
	uint16_t va, vb;
	if (first_sym->sym_64 && sec_sym->sym_64)
	{
		va = first_sym->sym_64->st_value;
		vb = sec_sym->sym_64->st_value;
	} else {
		va = first_sym->sym_32->st_value;
		vb = sec_sym->sym_32->st_value;
	}
	return (va - vb);
}

int comp_Sym(void *a, void *b)
{
	t_sym *first_sym = a;
	t_sym *sec_sym = b;
	const char *s1 = first_sym->name;
	const char *s2 = sec_sym->name;
	if (s1 == NULL || s2 == NULL)
		return (0);
	for (;*s1 && *s2; s1++, s2++)
	{
		while (*s1 && !_ft_isalnum(*s1))
			s1++;
		while (*s2 && !_ft_isalnum(*s2))
			s2++;
		if (_ft_tolower(*s1) != _ft_tolower(*s2))
			return ((unsigned char) _ft_tolower(*s1) - (unsigned char) _ft_tolower(*s2));
	}
	if (*s1 == *s2)
	{
		if (first_sym->symbol == 'W' && sec_sym->symbol == 'D') return 1;
		else if (first_sym->symbol == 't' && sec_sym->symbol == 'T') return 1;
		else if (first_sym->symbol == 'T' && sec_sym->symbol == 'W') return 1;
		else if (first_sym->symbol == 'D' && sec_sym->symbol == 'W') return -1;
		else if (first_sym->symbol == 'T' && sec_sym->symbol == 't') return -1;
		else if (first_sym->symbol == 'W' && sec_sym->symbol == 'T') return -1;
		return (comp_Val(a, b));
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
