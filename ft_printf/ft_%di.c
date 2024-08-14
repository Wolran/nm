#include "ft_printf.h"

static int	ft_dec_len(int nb)
{
	int				count;
	long long int	nbr;

	count = 0;
	nbr = nb;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_mod(int n)
{
	int	test;

	test = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", (test += 11));
		return (test);
	}
	if (n < 0)
	{
		test = n * -1;
		ft_putchar_mod('-');
	}
	else
		test = n;
	if (test > 9)
		ft_putnbr_mod(test / 10);
	ft_putchar_mod('0' + (test % 10));
	return (ft_dec_len(n));
}

