#include "../includes/delaunay.h"

t_list	*lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}

void	lstadd_front(t_list **lst, t_list *new_item)
{
	if (lst && new_item)
	{
		new_item->next = *lst;
		*lst = new_item;
	}
}

int	lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_list	*lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_list **lst, t_list *new_item)
{
	if (*lst)
		(lstlast(*lst))->next = new_item;
	else
		*lst = new_item;
}

void	lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(del)(lst->content);
		free(lst);
	}
}

void	lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (lst && del)
	{
		while (*lst)
		{
			nxt = (*lst)->next;
			lstdelone(*lst, del);
			*lst = nxt;
		}
		*lst = 0;
	}
}

void	lstiter(t_list *lst, void (*f)(void *))
{
	if (lst)
	{
		while (lst)
		{
			(f)(lst->content);
			lst = lst->next;
		}
	}
}

t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_list_first;

	if (!lst || !f)
		return (0);
	new_list = lstnew((f)(lst->content));
	new_list_first = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = lstnew((f)(lst->content));
		if (!new_list->next)
		{
			if (del)
				lstclear(&new_list_first, del);
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = 0;
	return (new_list_first);
}
