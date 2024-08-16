#include "ft_printf.h"

static int	ft_verif(const char *str, int i, va_list args)
{
	if (str[i] == 'c')
		return (ft_putchar_mod(va_arg(args, int)));
	else if (str[i] == 's')
		return (ft_putstr_mod(va_arg(args, char *)));
	else if (str[i] == 'p')
		return (ft_argp(va_arg(args, void *)));
	else if (str[i] == 'd')
		return (ft_putnbr_mod(va_arg(args, int)));
	else if (str[i] == 'i')
		return (ft_putnbr_mod(va_arg(args, int)));
	else if (str[i] == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	else if (str[i] == 'x')
		return (ft_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (str[i] == 'X')
		return (ft_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (str[i] == '%')
		return (ft_pourcentage());
	else if (str[i] > '0' && str[i] < '9')
		return (ft_putchar_mod(va_arg(args, int)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int	i;
	int		nb_args;

	va_start(args, str);
	i = 0;
	nb_args = 0;
	while(str[i])
	{
		if(str[i] == '%' && str[i + 1])
		{
			nb_args += ft_verif(str, i + 1, args);
			i++;
		}
		else
			nb_args += ft_putchar_mod(str[i]);
		if (str[i] == '\0')
			return (nb_args);
		i++;
	}
	va_end(args);
	return (nb_args);
}
