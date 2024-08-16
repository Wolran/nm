#include "ft_printf.h"

int	ft_putstr_mod(char *s)
{
	int	i;
	
	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_putchar_mod(s[i]);
		i++;	
	}
	return (i);
}
