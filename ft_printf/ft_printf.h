#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_pourcentage(void);
int		ft_hex(unsigned int n, char *base);
int		ft_putnbr_mod(int n);
int		ft_putstr_mod(char *s);
int		ft_putchar_mod(char c);
int		ft_putnbr_u(unsigned int n);
int 	ft_argp(void *str);
void	ft_putnbr_base(unsigned long long int nb, char *base);

#endif
