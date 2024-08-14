#include "ft_printf.h"

static int	ft_hex_len(unsigned long nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int ft_argp(void *str)
{
	unsigned long test;
	
	test = (unsigned long)str;
	if (!str)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_putnbr_base(test, "0123456789abcdef");
	return (ft_hex_len(test) + 2);
}
