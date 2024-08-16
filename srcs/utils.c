#include "nm.h"

int ft_ceil(double x)
{
	return x == (int)x ? (int)x : (int)x + 1;
}

void ft_bzero(void *s, size_t n)
{
	size_t	i;
	i = 0;
	while (n > i)
		((unsigned char *)s)[i++] = 0;
}

void free_data(t_data *data) 
{
	if (data->fd > 0)
	{
		close(data->fd);
		data->fd = 0;
	}
	if (data->data)
		munmap(data->data, data->data_size);
	if (data->sym)
		ft_lstclear(&data->sym, free);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	return (0);
}