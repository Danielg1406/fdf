/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:35:53 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/04/25 16:35:55 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*current;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		current = f(lst->content);
		temp = ft_lstnew(current);
		if (!temp)
		{
			del(current);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	lst = NULL;
	return (new);
}
	// if (!lst || !f || !del)
	// 	return (NULL);
	// new = ft_lstnew(f(lst->content));
	// if (!new)
	// {
	// 	del(new->content);
	// 	return (NULL);
	// }
	// temp = new;
	// lst = lst->next;
	// while (lst)
	// {
	// 	temp->next = ft_lstnew(f(lst->content));
	// 	if (!temp->next)
	// 	{
	// 		ft_lstclear(&new, del);
	// 		return (NULL);
	// 	}
	// 	temp = temp->next;
	// 	lst = lst->next;
	// }
	// return (new);
