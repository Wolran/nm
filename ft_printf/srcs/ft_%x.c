#include "ft_printf.h"

static int	ft_taille(unsigned long long int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		nbr = nbr / 16;
		len++;
	}
	return (len);
}

int	ft_hex(unsigned int n, char *base)
{
	int			point;
	int			count;
	int			len;
	char		*strnbr;

	if (n == 0)
	{
		count = write (1, "0", 1);
		return (count);
	}
	len = ft_taille(n);
	strnbr = malloc(sizeof(char) * len + 1);
	if (!strnbr)
		return (0);
	strnbr[len] = '\0';
	while (len--)
	{
		point = n % 16;
		strnbr[len] = base[point];
		n /= 16;
	}
	count = ft_putstr_mod(strnbr);
	free(strnbr);
	return (count);
}
