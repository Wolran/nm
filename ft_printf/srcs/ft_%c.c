#include "ft_printf.h"

int	ft_putchar_mod(char c)
{
	write(1, &c, 1);
	return (1);
}
