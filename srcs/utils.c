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
