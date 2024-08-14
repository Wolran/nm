#include "nm.h"

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->data);
	free(lst);
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

t_list *ft_lstnew(void *data)
{
	t_list	*lst;

	lst = malloc(sizeof(*lst));
	if (lst == NULL)
		return (NULL);
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

t_list *ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}


void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_back;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_back = ft_lstlast(*lst);
	lst_back->next = new;
}

void ft_lstsort(t_list **lst, int (*cmp)(void *, void *))
{
	t_list	*tmp;
	t_list	*tmp2;
	void	*data;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (cmp(tmp->data, tmp2->data) > 0)
			{
				data = tmp->data;
				tmp->data = tmp2->data;
				tmp2->data = data;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_list *ft_lstat(t_list *begin_list, unsigned int nbr)
{
	for (unsigned int i = 0; i < nbr; i++)
	{
		if (!begin_list)
			return (0);
		begin_list = begin_list->next;
	}
	return (begin_list);
}

int ft_lstsize(t_list *lst)
{
	int i = 0;
	for (; lst; i++)
		lst = lst->next;
	return (i);
}