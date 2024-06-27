/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:45:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 09:45:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

static t_node	*list_sorted_merge(t_node *left, t_node *right,
		int (*f)(uintptr_t d1, uintptr_t d2))
{
	t_node	*result;

	result = 0;
	if (!left)
		return (right);
	else if (!right)
		return (left);
	if (f(left->data, right->data))
	{
		result = left;
		result->next = list_sorted_merge(left->next, right, f);
	}
	else
	{
		result = right;
		result->next = list_sorted_merge(left, right->next, f);
	}
	return (result);
}

static void	list_find_middle(t_node *list, t_node **start, t_node **end)
{
	t_node	*fast;
	t_node	*slow;

	slow = list;
	fast = list->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*start = list;
	*end = slow->next;
	slow->next = 0;
}

void	list_sort(t_node **list, int (*f)(uintptr_t d1, uintptr_t d2))
{
	t_node	*head;
	t_node	*a;
	t_node	*b;

	head = *list;
	if (!head || !head->next)
		return ;
	list_find_middle(head, &a, &b);
	list_sort(&a, f);
	list_sort(&b, f);
	*list = list_sorted_merge(a, b, f);
}

void	list_push_back(t_list *self, uintptr_t data)
{
	t_node	*node;

	node = node_create(data);
	list_insert_back(self, node);
}
