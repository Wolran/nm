#include "ft_printf.h"

static int	ft_len_m(unsigned long long int n)
{
	size_t count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count ++;
	}
	return (count);
}

int	ft_putnbr_u(unsigned int n)
{
	unsigned long long int nb;
	
	nb = n;
	if (nb > 9)
	{
		ft_putnbr_u(nb / 10);
		ft_putnbr_u(nb % 10);
	}
	else
		ft_putchar_mod(nb + 48);
	return (ft_len_m(n));
}
